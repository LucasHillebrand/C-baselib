#ifndef basetypes_h
#define basetypes_h

#define sysarch sizeof(long)*8;

#define K(s) 1024*s
#define M(s) K(1024)*s
#define G(s) M(1024)*s
#define T(s) G(1024)*s

#define NONE 0

typedef unsigned long usize;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char byte;

#endif