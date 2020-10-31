all: lzread lzwrite

lzread: lzread.c
	cc -o lzread lzread.c

lzwrite: lzwrite.c
	cc -o lzwrite lzwrite.c
