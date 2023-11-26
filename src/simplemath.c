#include "../headers/simplemath.h"

usize m_len(usize num, enum numtype type){
    usize len = 0;
    for (;num!=0;num-=num%type,num/=type,len++);
    return len;
}

usize m_power(usize num, usize n){
    usize ret=1;
    for (usize i=0;i<n;ret*=num,i++);
    return ret;
}