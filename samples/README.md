# Sample Files

Files to help verify the functionality of our *lzwrite* and *lzread* programs.

* **.un** files are "uncompressed"
* **.lz** files are "compressed"
* **.lz.decomp** files are "decompressed"

### How to use?
Using *od* to verify:
```bash
$ ./lzwrite samples/ex1.un output.lz

$ od -t x1 output.lz
0000000 30 98 8c 60 a0
0000005

$ od -t x1 samples/ex1.lz
0000000 30 98 8c 60 a0
0000005

# Verify the two are identical
```
Or simply use *diff* to verify:
```bash
$ ./lzwrite samples/ex1.un output.lz

$ diff -s output.lz samples/ex1.lz
Files output.lz and samples/ex1.lz are identical
```
All together:
```bash
# Encode
$ ./lzwrite samples/ex3.un output.lz

$ diff -s output.lz samples/ex3.lz
Files output.lz and samples/ex3.lz are identical

# Decode
$ ./lzread output.lz output.lz.decomp

$ diff -s output.lz.decomp samples/ex3.lz.decomp
Files output.lz.decomp and samples/ex3.lz.decomp are identical
```
