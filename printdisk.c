#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>


#define IOVECS 16
#define IOLEN 128

int main(int argc, char **argv)
{

    int infile;

    infile = open(argv[1], O_RDONLY);

    if (infile == -1) {
	perror(argv[1]);
	return -1;
    }

    int i;
    struct iovec iov[IOVECS];

    for (i = 0; i < IOVECS; i++) {
	char *buf;
	buf = calloc(IOLEN + 2, 1);
	if (!buf) {
	    perror("Allocating Buffers");
	    return -1;
	}
	iov[i].iov_base = buf;
	iov[i].iov_len = IOLEN;
    }


    ssize_t ret;
    int j, k, contig, maxcontig;
    long long offset = 0;
    int flag = 0;
    char *smallbuf;
    while ((ret = readv(infile, iov, IOVECS))) {

	if (ret == -1) {
	    perror("Reading Disk Image");
	    return -1;
	}

	for (j = 0; j < IOVECS; j++) {

	    contig = 0;
	    maxcontig = 0;

	    smallbuf = iov[j].iov_base;
	    for (k = 0; k < IOLEN; k++) {

		if (!isalpha(*smallbuf)) {
		    if (!isprint(*smallbuf)) {
			*smallbuf = ' ';
		    }
		    if (contig > maxcontig) {
			maxcontig = contig;
		    }
		    contig = 0;
		} else {
		    contig++;
		}
		smallbuf++;
	    }

	    if ((maxcontig > 7) || (contig > 7)) {
		printf("%012lld           %s\n", offset,
		       (char *) iov[j].iov_base);
		flag = 1;
	    } else {
		if (flag) {
		    printf("\n");
		    flag = 0;
		}
	    }

	    offset += IOLEN;
	}


    }


    close(infile);
    return 0;
}
