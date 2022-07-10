#include "genome.h"
#include "QRandomGenerator"

Genome::Genome()
{
    fitness = 0;
}

Genome::Genome(const int numBits)
{
    for(size_t i = 0; i < numBits; i++) {
        int gen = QRandomGenerator::global()->bounded(100);
        if(gen < 50) {
            bits.push_back(0);
        } else {
            bits.push_back(1);
        }

    }
    fitness = 0;
}
