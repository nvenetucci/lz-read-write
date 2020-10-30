# lz-read-write
Simple bit reader and writer as one might see in LZ or LZW compression algorithms.

### Setup
Build with makefile:
```
make
```

### Bit Writer (Encoder) - *lzwrite*
Use:
```
./lzwrite <input file> <output file>
```
#### How it works?
The program reads in a binary or ASCII file. As an example, suppose the input file contains 4 bytes:
```
abc\n
```
In hexadecimal:
```
61 62 63 0a
```
And in binary:
```
01100001 01100010 01100011 00001010
```
For every byte (8-bits) in the file, the program writes it out as 9-bits, padding the front of each byte with one 0 bit:
```
001100001 001100010 001100011 000001010
```
Since files can only be written in bytes, the program must account for realigning the bits:
```
00110000 10011000 10001100 01100000 1010
```
This may leave us with an unfilled byte, which the program will then need to pad (on the right) before writing to file:
```
00110000 10011000 10001100 01100000 10100000
```
We can't directly view the binary bits within a file, but we can use the program *od* to display its contents:
```
od –t x1 <output file>
```
The output file should contain the following in hexadecimal:
```
30 98 8c 60 a0
```