#include "headers/palloc.h"
#include "headers/simplemath.h"
#include "headers/string.h"
#include "headers/datatypes/sllist.h"
#include <stdio.h>

int main(){
    byte buff[K(256)];
    palloc_pagetable str_ptable = palloc_create_table(buff, K(256), std_str_size);

    usize num = str_ston((byte*)"255",dec); // expected output 255
    printf("%lu\n",num);
}