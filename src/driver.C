#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include "bitop.h"
#include "bitop-opt.h"
#include "timing.h"
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>

using namespace std;

void (*extract_function)(size_t, size_t, unsigned long *, std::vector<size_t>&);

int main(int argc, char *argv[])
{
    FILE *pFile;
    size_t b, e, m_size;
    std::vector<size_t> m;
    unsigned long *bitvec = NULL;
    unsigned long long cycles = 0, count = 0;

    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " [0] baseline [1] builtin>"<< std::endl;
        exit(0);
    }   

    // Set the function to call based on command line argument
    switch(atoi(argv[1]))
    {
        default:
        case 0:
            extract_function = extract_bits;
            break;
        case 1:
            extract_function = extract_bits_with_builtin;
            break;
        case 2:
            extract_function = extract_bits_with_avx_check;
            break;
    }

    pFile = fopen("extract_bits.bin","rb");
    while( 1 == fread(&b, sizeof(size_t), 1, pFile) )
    {
        assert(fread(&e, sizeof(size_t), 1, pFile) && "Unable to read file");
        size_t l = (e - b + ULONG_BITS - 1) / ULONG_BITS;
        posix_memalign((void **) &bitvec, 32, sizeof(unsigned long long)*l );
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
