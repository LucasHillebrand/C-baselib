#include "../headers/palloc.h"

palloc_pagetable palloc_create_table(void* buffstart, usize buffsize, usize pagesize){
    if (pagesize < sizeof(usize))
        pagesize=sizeof(usize);
    
    buffsize-=buffsize%pagesize;

    palloc_pagetable out = {
        buffstart,
        buffsize,
        pagesize,
        0
    };

    for (usize i=0; i<buffsize;i+=pagesize){
        *((void**)(buffstart+i))=out.head;
        out.head=(void*)(buffstart+i);
    }

    return out;
}

void* palloc_alloc(palloc_pagetable* ptable){
    void* ptr = ptable->head;
    if (ptr == 0)
        goto alloc_exit;
    ptable->head=*(void**)ptr;

    for (byte i=0;i<sizeof(usize);i++)
        *(byte*)(ptr+i)=0;


    alloc_exit: // if an error happens jump to this position
    return ptr;
}

void palloc_free(palloc_pagetable* ptable, void* ptr){
    if (!(((ptr-ptable->start) % ptable->pagesize) == 0)) // checking if the ptr is part of the ptable
        goto free_exit;
    for (usize i=0;i<ptable->pagesize;i++)
        *(byte*)(ptr+i)=0;
    
    *(void**)(ptr)=ptable->head;
    ptable->head=ptr;

    free_exit:
    return;
}