#include <cassert>
#include "bitop-opt.h"
#include <iostream>
#include <immintrin.h>

void extract_bits_with_builtin(size_t b, size_t e, unsigned long *bitvec, vector<size_t> &m)
{
    assert( b<=e );
    // extraction of the 1 bits from the bit vector
    size_t l = (e - b + ULONG_BITS - 1) / ULONG_BITS;
    size_t bp = b;
    for( size_t i=0; i<l; i++, bp+=ULONG_BITS ) 
    {
        unsigned long n = bitvec[i];
        while(__builtin_expect(n,0))
        {
            unsigned long idx = __builtin_ffsl(n);
            unsigned long a = (idx - 1);
            n &= ~((unsigned long)1 << a);
            m.push_back(bp+a);
        }
    }
}


void extract_bits_with_avx_check(size_t b, size_t e, unsigned long *bitvec, vector<size_t> &m)
{
    assert( b<=e );
    // extraction of the 1 bits from the bit vector
    size_t l = (e - b + ULONG_BITS - 1) / ULONG_BITS;
    size_t bp = b;

    packed x;
    for( size_t i=0; i<l; i+=4, bp+=4*ULONG_BITS ) 
    {
        __m256i *addr = (__m256i *)(bitvec+i);
        x.avx_val =_mm256_load_si256(addr);

        if(x.ulong[0] || x.ulong[1] || x.ulong[2] || x.ulong[3])
        {
            unsigned long n = x.ulong[0]; 
            while(n)
            {
                    unsigned long idx = __builtin_ffsl(n);
                    unsigned long a = (idx - 1);
                    m.push_back(bp+a);
                    n &= ~((unsigned long)1 << a);
            }     
            n = x.ulong[1]; 
            while(n)
            {
                    unsigned long idx = __builtin_ffsl(n);
                    unsigned long a = (idx - 1);
                    m.push_back(bp+a);
                    n &= ~((unsigned long)1 << a);
            }
            
            n = x.ulong[2]; 
            while(n)
            {
                    unsigned long idx = __builtin_ffsl(n);
                    unsigned long a = (idx - 1);
                    m.push_back(bp+a);
                    n &= ~((unsigned long)1 << a);
            }
            
            n = x.ulong[3]; 
            while(n)
            {
                    unsigned long idx = __builtin_ffsl(n);
                    unsigned long a = (idx - 1);
                    m.push_back(bp+a);
                    n &= ~((unsigned long)1 << a);
            }  
        } 
    }
}



