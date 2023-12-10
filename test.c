#include <stdio.h>
#include "./headers/string.h"
#include "headers/palloc.h"

int main(){
    byte buff[K(128)];
    palloc_pagetable ptable=palloc_create_table(buff, K(128), std_str_size);

    printf("cut: >%s<\n",str_cut(&ptable,(byte*)"String", 1, 4));
}