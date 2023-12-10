#ifndef string_h
#define string_h

#include "./palloc.h"
#include "./simplemath.h"
#include "basetypes.h"

#define std_str_size 128

usize str_len(const byte* str);
byte str_cmp(const byte* a, const byte* b);

usize str_ston(const byte* str, enum numtype type);
byte* str_ntos(palloc_pagetable* ptable, usize num, enum numtype type);

byte* stringf(palloc_pagetable* ptable, const char* format, void* args[]); // support for %%, %s

byte* str_cut(palloc_pagetable* ptable, byte* string, usize start, usize len);
byte str_startswith(byte* org, usize start, char* search);

/*
struct spl_str {
    const byte* orgstr;
    const char separator;
    byte* curr;
};

void str_cut(byte* str, usize start, usize end);
void str_next(struct spl_str* spl);
struct spl_str str_genspl(palloc_pagetable* ptable, byte* str, char separator);
*/

#endif