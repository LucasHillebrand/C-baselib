#ifndef sllist_h
#define sllist_h

#include "../palloc.h"
#include "../basetypes.h"

#define std_sllist_nodesize sizeof(struct sllist_node)

typedef struct {
    struct sllist_node* head;
    const palloc_pagetable* sllist_ptable;
    const palloc_pagetable* value_ptable;
} sllist_base;

struct sllist_node {
    void* next;
    void* val;
};

sllist_base sllist_create(palloc_pagetable* sllptable, palloc_pagetable* itemptable);
void sllist_prepend(sllist_base* sllist, void* val);
void sllist_remove(sllist_base* sllist, usize item);
void* sllist_pop(sllist_base* sllist);
void* sllist_get(sllist_base* sllist, usize item);
usize sllist_len(sllist_base* sllist);
void sllist_destroy(sllist_base* sllist);

#endif