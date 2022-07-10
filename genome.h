#ifndef GENOME_H
#define GENOME_H

#include <vector>



class Genome
{
public:
    Genome();
    Genome(const int);

    std::vector<int> bits;
    double fitness;

};

#endif // GENOME_H
