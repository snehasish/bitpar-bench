#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *pFile;
    size_t b, e, m_size;
    std::vector<size_t> m;
    unsigned long *bitvec = NULL;
    unsigned long long cycles = 0, count = 0;
    const size_t ULONG_BITS = sizeof(unsigned long) * 8;
    // Analyses 
    std::map<int,unsigned long long> bitvec_vals; 
    unsigned long long sum = 0;
    
    pFile = fopen("extract_bits.bin","rb");
    while( 1 == fread(&b, sizeof(size_t), 1, pFile) )
    {
        assert(fread(&e, sizeof(size_t), 1, pFile) && "Unable to read file");
        size_t l = (e - b + ULONG_BITS - 1) / ULONG_BITS;
        bitvec = (unsigned long*)malloc(sizeof(unsigned long)*l);
        assert(fread(bitvec, sizeof(unsigned long), l, pFile) && "Unable to read file");

        for(unsigned i = 0; i < l; i++)
        {
            int x = __builtin_popcount(bitvec[i]);
            sum +=1;
            if(bitvec_vals.count(x) == 0)
                bitvec_vals.insert(std::make_pair(x,1));
            else
                bitvec_vals[x]++;
        }
        
        count++;
        free(bitvec);
    }

    
    for(std::map<int,unsigned long long>::iterator it = bitvec_vals.begin(); it != bitvec_vals.end(); it++)
        std::cout << it->first << " : " << it->second << " : " << double(it->second)/sum*100 << std::endl;

    fclose(pFile);
    return 0;
}
