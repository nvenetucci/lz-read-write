# lz-read-write
Simple bit reader and writer as one might see in LZ or LZW compression algorithms.

### Setup
Build with makefile:
```bash
$ make
```

### Bit Writer (Encoder) - *lzwrite*
Usage:
```bash
$ ./lzwrite <input file> <output file>
```
#### How it works?
The program reads in either a binary or ASCII file. As an example, suppose the input file contains 4 bytes:
```
abc\n
```
Which translates to:
```bash
61 62 63 0a # in hexadecimal

# or

01100001 01100010 01100011 00001010 # in binary
```
For every byte (8 bits) in the file, the program writes it out as 9 bits, padding the front of each byte with one 0 bit:
```bash
001100001 001100010 001100011 000001010

# Since files can only be written in bytes (8 bits at a time),
# the program must account for realigning the bits

00110000 10011000 10001100 01100000 1010

# This may leave us with an unfilled byte, which the program will
# then need to pad (on the right) before writing to the file

00110000 10011000 10001100 01100000 10100000
```
We can't directly view the binary bits within a file, but we can use the program *od* to display its contents:
```bash
$ od –t x1 <output file>
```
The output file should contain the following in hexadecimal:
```
30 98 8c 60 a0
```

### Bit Reader (Decoder) - *lzread*
Usage:
```bash
$ ./lzread <input file> <output file>
```
#### How it works?
The program reads in a binary file. Operating more or less identically to *lzwrite*, except this time the aim is to reverse the compression. Conceptually, the program reads in the file 9 bits at a time, printing out the 9-bit value in decimal, followed by a carriage return. In effect, the program is reading from an LZW compressed file, and handing off the value to the decompressor for processing.

Using the ouput file from the previous *lzwrite* example:
```
30 98 8c 60 a0
```
Provided as input to *lzread*, will produce the following output file:
```
97
98
99
10
```
Note: values can range from 0 to 511 with 9 bits.