#ifndef BOBTHERESERCHER_H
#define BOBTHERESERCHER_H

#include <bobsmap.h>
#include <genome.h>
#include <vector>


class BobTheResercher
{
public:
    BobTheResercher(double, double, int, int, int, Ui::MainWindow *w);
    void run();

private:
    std::vector<Genome> populationGenoms;
    int populationSize;
    double crossoverRate;
    double mutationRate;
    int genomeLength;
    int geneLength;
    int fittestGenome;    double bestFitnessScore;
    double totalFitnessScore;
    int generationNumber;

    int currentGenome;


    std::unique_ptr<BobsMap> bobsMap;

    bool busy;

    void mutate(std::vector<int>);
    void crossover(const std::vector<int>&, const std::vector<int>&,
                   std::vector<int>&, std::vector<int>&);
    Genome& rouletteWheelSelection();

    void updateFitnessScore(int);
    std::vector<int> decode(const std::vector<int> bits);
    int BitToInt(const std::vector<int> &v);
    void createPopulation();
    void epoch();

    int getGeneration();
    int getFittest();
    bool isBusy();
    void stop();
};

#endif // BOBTHERESERCHER_H
