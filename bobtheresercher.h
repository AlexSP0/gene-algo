#ifndef BOBTHERESERCHER_H
#define BOBTHERESERCHER_H

#include <genome.h>
#include <vector>


class BobTheResercher
{
public:
    int fittestGenome;
    double bestFitnessScore;
    double totalFitnessScore;
    int generationNumber;

    BobTheResercher(double, double, int, int, int);

    std::vector<Genome> populationGenoms;

private:
    int populationSize;
    double crossoverRate;
    double mutationRate;
    int genomeLength;
    int geneLength;

    int currentGenome;

    bool busy;

    void mutate(std::vector<int>);
    void crossover(const std::vector<int>&, const std::vector<int>&,
                   std::vector<int>&, std::vector<int>&);
    Genome& rouletteWheelSelection();

    void createPopulation();

    int getGeneration();
    int getFittest();
};

#endif // BOBTHERESERCHER_H
