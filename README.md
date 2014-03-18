printdisk
=========

Simple tool for printing string-containing sectors in a binary disk image


purpose
=========

Given a binary input file, this program:

      * reads it in, 128 bytes (here, one line) at a time
      * replaces non-printable characters in each line with spaces
      * prints the line plus an offset in decimal if and only if the line contains 8 or more contiguous letters
      *	prints a blank line between non-contiguous printed lines 

This is useful if you want to visualize printable content in a binary file and filter out likely junk.
Each line is 128 bytes long so as to fit on a reasonable xterm without wrapping, while being a multiple of the common 512 byte sector size.

build
=========

gcc -Wall -O3 -o printdisk printdisk.c


run
=========

./printdisk my-disk-image > outfile

Then open outfile with a text editor to view strings.


bugs
=========

	* minimal testing (I am satisfied that it works for my purpose)
	* lack of configurability

