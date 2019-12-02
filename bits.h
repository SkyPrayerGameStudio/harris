#pragma once
/*
	harris - a strategy game
	Copyright (C) 2012-2015 Edward Cree

	licensed under GPLv3+ - see top of harris.c for details
	
	bits: misc. functions, mostly for string buffers
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "types.h"

#define min(a,b)		((a)<(b)?(a):(b))
#define max(a,b)		((a)>(b)?(a):(b))
#define clamp(v,a,b)	((v)=((v)<(a))?(a):(((v)<(b))?(v):(b)))
#define transfer(v,f,t)	do { t+=min(v,f); f-=min(v,f); } while(0)

char *fgetl(FILE *); // gets a line of string data; returns a malloc-like pointer
char *slurp(FILE *); // gets a file of string data; returns a malloc-like pointer
string sslurp(FILE *fp); // gets a file of string data possibly containing NULs; return contains a malloc-like pointer
string init_string(void); // initialises a string buffer in heap
string null_string(void); // returns a null string (no allocation)
string make_string(const char *str); // initialises a string buffer in heap, with initial contents copied from str
void append_char(string *s, char c); // adds a character to a string buffer in heap (and realloc()s if needed)
void append_str(string *s, const char *str); // adds a cstring to a string buffer in heap (and realloc()s if needed)
void append_string(string *s, const string t); // adds a string to a string buffer in heap (and realloc()s if needed)
void free_string(string *s); // frees a string (is just free(s->buf); really)

void pacid(acid id, char buf[9]); // print an a/c id as hex
int gacid(const char from[8], acid *buf); // parse an a/c id from hex
void pcmid(cmid id, char buf[17]); // similar but for c/m ids
int gcmid(const char from[16], cmid *buf);

#ifdef WINDOWS /* doesn't have strndup, we need to implement one */
char *strndup(const char *s, size_t size);
#endif

#define container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof((arr)[0]))
