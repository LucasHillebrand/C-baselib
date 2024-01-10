#include "../headers/string.h"

usize str_len(const byte* str){
    usize len=0;
    for (;str[len]>0;len++);
    return len;
}

byte str_cmp(const byte* a, const byte* b){
    byte eval=0;
    if (str_len(a) != str_len(b))
        goto cmp_end;
    usize strlen=str_len(a);
    for (usize i=0;i<strlen;i++)
        if (a[i]!=b[i])
            goto cmp_end;
    
    eval=1;

    cmp_end:
    return eval;
}


usize str_ston(const byte* str, enum numtype type){
    usize out=0;
    usize n=0;
    switch (type) {
    case dec:
        for (usize i=str_len(str)-1;(i>>(sizeof(usize)*8-1)&1)==0;i--){
            switch (str[i]){
            case '0':
                n++;
                break;
            case '1':
                out+=1*m_power(type, n);
                n++;
                break;
            case '2':
                out+=2*m_power(type, n);
                n++;
                break;
            case '3':
                out+=3*m_power(type, n);
                n++;
                break;
            case '4':
                out+=4*m_power(type, n);
                n++;
                break;
            case '5':
                out+=5*m_power(type, n);
                n++;
                break;
            case '6':
                out+=6*m_power(type, n);
                n++;
                break;
            case '7':
                out+=7*m_power(type, n);
                n++;
                break;
            case '8':
                out+=8*m_power(type, n);
                n++;
                break;
            case '9':
                out+=9*m_power(type, n);
                n++;
                break;
            
            }
        }
        break;
    case hex:
        for (usize i=str_len(str)-1;(i>>(sizeof(usize)*8-1)&1)==0;i--){
            switch (str[i]){
            case '0':
                n++;
                break;
            case '1':
                out+=1*m_power(type, n);
                n++;
                break;
            case '2':
                out+=2*m_power(type, n);
                n++;
                break;
            case '3':
                out+=3*m_power(type, n);
                n++;
                break;
            case '4':
                out+=4*m_power(type, n);
                n++;
                break;
            case '5':
                out+=5*m_power(type, n);
                n++;
                break;
            case '6':
                out+=6*m_power(type, n);
                n++;
                break;
            case '7':
                out+=7*m_power(type, n);
                n++;
                break;
            case '8':
                out+=8*m_power(type, n);
                n++;
                break;
            case '9':
                out+=9*m_power(type, n);
                n++;
                break;
            case 'A':
            case 'a':
                out+=10*m_power(type, n);
                n++;
                break;
            case 'B':
            case 'b':
                out+=11*m_power(type, n);
                n++;
                break;
            case 'C':
            case 'c':
                out+=12*m_power(type, n);
                n++;
                break;
            case 'D':
            case 'd':
                out+=13*m_power(type, n);
                n++;
                break;
            case 'E':
            case 'e':
                out+=14*m_power(type, n);
                n++;
                break;
            case 'F':
            case 'f':
                out+=15*m_power(type, n);
                n++;
                break;
            
            }
        }
        break;
    case bin:
        for (usize i=str_len(str)-1;(i>>(sizeof(usize)*8-1)&1)==0;i--){
            switch (str[i]){
            case '0':
                n++;
                break;
            case '1':
                out+=m_power(type, n);
                n++;
                break;
            }
        }
        break;
    }
    return out;
}

byte* str_ntos(palloc_pagetable* ptable, usize num, enum numtype type){
    byte* str=palloc_alloc(ptable);
    usize strptr=m_len(num,type)-1;
    if (str==0)
        goto ntos_end;

    if (strptr>ptable->pagesize-2)
        strptr=ptable->pagesize-2;

    for (;num>0 && (strptr >> (sizeof(usize)-1) & 1) == 0;num-=num%type,num/=type,strptr--){
        switch (num%type){
        case 0:
            str[strptr]='0';
            break;
        case 1:
            str[strptr]='1';
            break;
        case 2:
            str[strptr]='2';
            break;
        case 3:
            str[strptr]='3';
            break;
        case 4:
            str[strptr]='4';
            break;
        case 5:
            str[strptr]='5';
            break;
        case 6:
            str[strptr]='6';
            break;
        case 7:
            str[strptr]='7';
            break;
        case 8:
            str[strptr]='8';
            break;
        case 9:
            str[strptr]='9';
            break;
        case 10:
            str[strptr]='A';
            break;
        case 11:
            str[strptr]='B';
            break;
        case 12:
            str[strptr]='C';
            break;
        case 13:
            str[strptr]='D';
            break;
        case 14:
            str[strptr]='E';
            break;
        case 15:
            str[strptr]='F';
            break;
        }
    }

    ntos_end:
    return str;
}


byte* stringf(palloc_pagetable* ptable, const char* format, void* args[]){ // support for %%, %s
    usize argptr=0;
    usize fptr=0;
    usize flen=str_len((byte*)format);
    byte* str=palloc_alloc(ptable); 
    if (str==0)
        goto stringf_end;


    for (usize i=0;fptr<flen && i<ptable->pagesize-1;fptr++){
        switch(format[fptr]){
        case '%':
            fptr+=1;
            switch (format[fptr]){
            case '%':
                str[i]='%';
                i++;
                break;
            case 's':
                if (args[argptr] == 0)
                    goto stringf_end;
                for (usize j=0;j<str_len(args[argptr]) && i<ptable->pagesize-1;j++,i++)
                    str[i]=((byte*)args[argptr])[j];
                argptr++;
                break;
            }
            break;
        default:
            str[i]=format[fptr];
            i++;
            break;
        }
    }

    stringf_end:
    return str;
}

byte* str_cut(palloc_pagetable* ptable, byte* string, usize start, usize len){
    byte* str = palloc_alloc(ptable);
    if (str == 0)
        goto cut_end;

    usize inlen=str_len(string);
    if (len == NONE)
        len=inlen;
    for (usize i = 0;i+start < inlen && i+start < len+start && i < ptable->pagesize-1;i++)
        str[i]=string[i+start];

    cut_end:
    return str;
}

byte str_startswith(byte* org,usize start, char* search){
    usize searchlen = str_len((byte*)search);
    usize orglen = str_len(org);

    byte found=0;

    if (orglen-start < searchlen)
        goto startswith_end;

    for (usize i=0;i<searchlen && i+start < orglen;i++)
        if(org[i+start] != search[i])
            goto startswith_end;
    
    found=1;

    startswith_end:
    return found;
}

sllist_base str_split(palloc_pagetable* str_ptable, palloc_pagetable* sll_ptable, byte* str, byte* keystr){
    sllist_base splstr={NONE, sll_ptable, str_ptable};
    struct sllist_node* currnode=NONE;

    currnode=palloc_alloc(sll_ptable);
    currnode->val=palloc_alloc(str_ptable);
    splstr.head=currnode;

    usize keylen = str_len(keystr);
    usize strlen = str_len(str);
    usize j=0;
    for (usize i=0;i<strlen;i++,j++){
        if (str_startswith(str, i, (char*)keystr) == 1) {
            i+=(keylen-1);
            currnode->next=palloc_alloc(sll_ptable);
            currnode=currnode->next;
            currnode->val=palloc_alloc(str_ptable);
            j=-1;
        }else{
            if (j<str_ptable->pagesize-1) *((byte*)((currnode->val)+j))=str[i];
        }
    }

    return splstr;
}