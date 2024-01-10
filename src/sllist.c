#include "../headers/datatypes/sllist.h"

sllist_base sllist_create(palloc_pagetable* sllptable, palloc_pagetable* itemptable){
    return (sllist_base){
        .head=NONE,
        .sllist_ptable=sllptable,
        .value_ptable=itemptable
    };
}

void sllist_prepend(sllist_base* sllist, void* val){
    struct sllist_node* new = palloc_alloc((palloc_pagetable*)sllist->sllist_ptable);
    new->next=(struct sllist_node*)sllist->head;
    new->val=val;
    sllist->head=new;
}

void sllist_remove(sllist_base* sllist, usize item){
    if (sllist->head == NONE) goto sllremend;
    struct sllist_node* curr = sllist->head;
    struct sllist_node* prev = sllist->head;
    for(usize i=0;i<item && curr->next != NONE;i++, prev=curr, curr=curr->next);
    if (item==0)sllist->head=curr->next;
    else prev->next = curr->next;
    palloc_free((palloc_pagetable*)sllist->value_ptable, curr->val);
    palloc_free((palloc_pagetable*)sllist->sllist_ptable,curr);

    sllremend:
    return;
}

void* sllist_get(sllist_base* sllist, usize item){
    void* out=NONE;
    struct sllist_node* curr = sllist->head;
    if(curr == NONE) goto sllgetend;
    for(usize i=0;i<item && curr->next != NONE;i++,curr=curr->next);
    out=curr->val;
    sllgetend:
    return out;
}

void* sllist_pop(sllist_base* sllist){
    void* ptr=NONE;
    if(sllist->head == NONE) goto sllpopend;
    ptr=sllist->head->val;
    struct sllist_node* node=sllist->head;
    sllist->head=node->next;
    palloc_free((palloc_pagetable*)sllist->sllist_ptable, node);

    sllpopend:
    return ptr;
}

usize sllist_len(sllist_base* sllist){
    usize len=0;
    for (struct sllist_node* curr = sllist->head; curr != NONE; curr=curr->next, len++);
    return len;
}

void sllist_destroy(sllist_base* sllist){
    for (;sllist->head!=NONE;sllist_remove(sllist, 0));
}