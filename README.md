# < baselib >
baselibary

## Build:

- Linux

        make build

    > there should be now an folder called baselib, in this folder is everything you need

# basetypes.h

< This module implements the most basic types and macros >

- ## added types:

    < This adds simpler ways to write types >

    type | C defenition
    ---|---
    usize | unsigned long
    uint | unsigned int 
    ushort | unsigned short
    byte | unsigned char

- ## added constants
    type | value
    ---|---
    NONE | 0

- ## added macros

    < these add simpler ways to calculate the space you want to use >

    macro | example | result
    ---|---|---
    K | K(1) | 1024**1
    M | M(1) | 1024**2
    G | G(1) | 1024**3
    T | T(1) | 1024**4

# simplemath.h
< implements the most basic math functions and types >

- types

    type | C defenition
    ---|---
    numtype | enum {dec, hex, bin}

- functions
    function | Arguments | return
    ---|---|---
    m_len | number **\|** numtype | usize
    m_power | base **\|** operant | usize

# palloc.h

< This implements a static Page allocator table >

---

- ## functiontable:

    function | Arguments | return
    ---|---|---
    palloc_create_table | *ptr to free space* **\|** *size of free space* **\|** *pagesize*| palloc_pagetable
    palloc_alloc | *ptr to the pagetable* | void*
    palloc_free | *ptr to page*

- ## example for how to use the page allocator:

    > Creating a buffer with the size of *256 KB* for the pagetable >> free space to use

        byte buff[K(256)];

    ---
    > creating the pagetable with the previos created buffer to use with the pagesize of *128 bytes*


        palloc_pagetable ptable = palloc_create_table(buff, K(256), 128);
    ---
    > allocating a page from page allocator


        byte* page = palloc_alloc(&ptable);

    > *Optional:* checking if i got an page (but you should have gotten a page)

        if (page == 0);

    > if the statement above is **true** then the pagetable is fully in use and this page is not usable
    ---
    > Freeing a used page

        palloc_free(page)
    ---

normally this is used in other modules like **string.h**

# string.h
< a module to work with strings >


- ## Functiontable:
    Function | Arguments | return | sidenote
    ---|---|---|---
    str_len | string | usize
    str_cmp | string a **\|** string b | byte (bool => 0 false, 1 true)
    str_ston | string **\|** numtype | usize | convert a string to a number
    str_ntos | palloc_pagetable* **\|** number **\|** numtype | byte* | convert a number to string
    stringf | palloc_pagetable* **\|** formatstring **\|** void*[] | byte* | supportet keys are %% and %s
    str_cut | palloc_pagetable* **\|** string **\|** startpos **\|** length | byte*
    str_startswith | string **\|** startpos **\|** searchstr | byte (bool => 0 false, 1 true)

- ## Example
    > before we beginn we need an pagetable for the strings

        byte buff[K(256)];
        palloc_pagetable str_ptable = palloc_create_table(buff, K(256), std_str_size);
    ---
    > convert a string to a number

        usize num = str_ston((byte*)"255",dec); // expected output 255
        num = str_ston((byte*)"FF", hex); // expected output 255
        num = str_ston((byte*)"11111111", bin); // expected output 255
    ---
    > convert a number to string

        byte* ntos(&str_ptable, 255, dec); // expected output "255"
        byte* ntos(&str_ptable, 255, hex); // expected output "FF"
        byte* ntos(&str_ptable, 255, bin); // expected output "11111111"
    ---
    > format a string

        byte* str = stringf(&str_ptable, "%s World\n", (void*[]){"Hello"}); // expected output "Hello World\n"
    ---
    > compare two strings

        byte same = str_cmp((byte*)"Hello", (byte*)"Hello"); // expected output 1 (true)
        same = str_cmp((byte*)"Hello",(byte*)"World"); // expected output 0 (false)

    ---
    > get the length of an string

        usize len = str_len((byte*)"Hello"); // expected output 5
    
    ---
    > cutting a string

        byte* str = str_cut(&str_ptable, (byte*)"string", 1, 4); // expected output "trin"
    
    > cut just the beginning

        byte* str = str_cut(&str_ptable, (byte*)"string", 1, NONE); // expected output "tring"

    ---
    > checking if a string startswith a specific string at a speciic position

        byte bool = str_startswith((byte*)"String", 0, "String"); // expected output 1
        byte bool = str_startswith((byte*)"String", 0, "string"); // expected output 0
        byte bool = str_startswith((byte*)"String", 1, "tri"); // expected output 1