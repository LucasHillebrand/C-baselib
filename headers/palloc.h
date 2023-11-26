#ifndef palloc_h
#define palloc_h

#include "./basetypes.h"

typedef struct { // size = 64 bytes 
    const void* start;
    const usize size;
    const usize pagesize;
    void* head;
} palloc_pagetable;

palloc_pagetable palloc_create_table(void* buffstart, usize buffsize, usize pagesize);
void* palloc_alloc(palloc_pagetable* ptable);
void palloc_free(palloc_pagetable* ptable, void* ptr);

#endif