#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include "bitop.h"
//#include "bitop-opt.h"
#include "timing.h"

using namespace std;

void (*extract_function)(size_t, size_t, unsigned long *, std::vector<size_t>&);

int main()
{
    FILE *pFile;
    size_t b, e;
    std::vector<size_t> m;
    unsigned long *bitvec = NULL;
    unsigned long long cycles = 0, count = 0;
    const size_t ULONG_BITS = sizeof(unsigned long) * 8;

    // Set the function to call based on command line argument
    extract_function = extract_bits;

    pFile = fopen("extract_bits.bin","rb");
    while( 1 == fread(&b, sizeof(size_t), 1, pFile) )
    {
        assert(fread(&e, sizeof(size_t), 1, pFile) && "Unable to read file");
        size_t l = (e - b + ULONG_BITS - 1) / ULONG_BITS;
        bitvec = (unsigned long*)malloc(sizeof(unsigned long)*l);
        assert(fread(bitvec, sizeof(unsigned long), l, pFile) && "Unable to read file");
        
        reset_and_start_timer();
        extract_function(b, e, bitvec, m);
        cycles += get_elapsed_cycles(); 
        
        count++;
        free(bitvec);
    }

    // Print stats
    std::cout << double(cycles)/count << " cycles/invocation" << std::endl;

    fclose(pFile);
    return 0;
}
