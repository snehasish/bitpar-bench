#include <stdlib.h>
#include <vector>
#include <immintrin.h>
using std::vector;

#ifndef ULONG_BITS
#define ULONG_BITS 64 
#endif

typedef union packed { __m256i avx_val; unsigned long ulong[4]; } packed;

void extract_bits_with_builtin(size_t b, size_t e, unsigned long *bitvec, vector<size_t> &m);
void extract_bits_with_avx_check(size_t b, size_t e, unsigned long *bitvec, vector<size_t> &m);

