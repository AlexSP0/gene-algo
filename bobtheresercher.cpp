#include "bobtheresercher.h"
#include "QRandomGenerator"


BobTheResercher::BobTheResercher(double crossRate, double mutateRate, int popSize, int numBits, int geneLen)
{
    populationSize = popSize;
    crossoverRate = crossRate; //Частота кроссовера
    mutationRate = mutateRate; //Частота мутаций
    genomeLength = numBits; //Клоичество бит в геноме
    geneLength = geneLen; //Количество бит в одном гене
    fittestGenome = 0.0;
    bestFitnessScore = 0.0;
    totalFitnessScore = 0.0;
    generationNumber = 0;
    busy = false;

    currentGenome = 0;

    createPopulation();
}

void BobTheResercher::mutate(std::vector<int> bits)
{
    for(size_t currentBit = 0; currentBit < bits.size(); currentBit++) {
        float random = static_cast<float> (QRandomGenerator::global()->generateDouble());
        if(random < mutationRate) {
            bits[currentBit] = !bits[currentBit];
        }
    }
}

void BobTheResercher::crossover(const std::vector<int> &mum, const std::vector<int> &dad,
                                std::vector<int> &baby, std::vector<int> &baby2)
{
    float random = static_cast<float> (QRandomGenerator::global()->generateDouble());
    if(random > crossoverRate || mum == dad) {
        baby = mum;
        baby2 = dad;
        return;
    }
    int crossoverPosition = QRandomGenerator::global()->bounded(0, genomeLength - 1);

    for(size_t i = 0; i < crossoverPosition; i++) {
        baby.push_back(mum[i]);
        baby2.push_back(dad[i]);
    }

    for(size_t i = crossoverPosition; i < mum.size(); i++) {
        baby.push_back(dad[i]);
        baby2.push_back(mum[i]);
    }

}

Genome &BobTheResercher::rouletteWheelSelection()
{
    double slice = QRandomGenerator::global()->bounded(0,totalFitnessScore);
    double total = 0;
    int selectedGenome = 0;
    for(size_t i; i < populationSize; i++) {
        total = total + populationGenoms[i].fitness;
        if(total > slice) {
            selectedGenome = i;
            break;
        }
    }
    return populationGenoms[selectedGenome];
}

void BobTheResercher::createPopulation()
{
    populationGenoms.clear();
    for(size_t i = 0; i < populationSize; i++) {
        Genome newGenome = Genome(genomeLength);
        populationGenoms.push_back(newGenome);
    }
}

//void BobTheResercher::epoch()
//{
//    updateFitnessScore(currentGenome);
//    std::vector<Genome> newGeneration;

//    for(size_t i = 0; i < populationSize; i++) {
//        Genome dad = rouletteWheelSelection();
//        Genome mum = rouletteWheelSelection();

//        Genome baby1;
//        Genome baby2;

//        crossover(mum.bits, dad.bits, baby1.bits, baby2.bits);

//        mutate(baby1.bits);
//        mutate(baby2.bits);

//        newGeneration.push_back(baby1);
//        newGeneration.push_back(baby2);
//    }
//}

int BobTheResercher::getGeneration()
{
    return generationNumber;
}

int BobTheResercher::getFittest()
{
    return fittestGenome;
}

