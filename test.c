#include <stdio.h>
#include "./headers/string.h"
#include "headers/datatypes/sllist.h"
#include "headers/palloc.h"

int main(){
    byte strbuff[K(128)];
    palloc_pagetable strptable=palloc_create_table(strbuff, K(128), std_str_size);
    byte sllbuff[K(128)];
    palloc_pagetable sllptable=palloc_create_table(sllbuff, K(128), std_sllist_nodesize);

    byte* str=(byte*)"Hello World I AM GROOT";

    sllist_base spl = str_split(&strptable,&sllptable,str,(byte*)" ");

    for(;spl.head!=0;sllist_remove(&spl, 0)) printf("<%s>\n",(char*)sllist_get(&spl, 0));
}