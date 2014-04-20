#include <cassert>
#include "bitop.h"
#include <iostream>

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
            m.push_back(bp+a);
            n &= ~((unsigned long)1 << a);
        }
    }
}


