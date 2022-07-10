#include "bobsmap.h"
#include <cmath>

BobsMap::BobsMap(Ui::MainWindow *win)
{
    map = win;
}

double BobsMap::testRoute(const std::vector<int> bits, int geneLen)
{
    //Converts bits to genes
    std::vector<int> directions = convertBitsToDecimal(bits, geneLen);

    map->resetBob();

    for(size_t i = 0; i < directions.size(); i++) {
        map->moveBob(directions[i]);
    }

    int diffX = abs(map->currentBob_x - map->target_x);
    int diffY = abs(map->currentBob_y - map->target_y);
    return 1 / (double) (diffX + diffY + 1);

}

int BobsMap::convertBinaryToDecimal(int bin)
{
    int decimalNumber = 0, i = 0, remainder;
    while (bin!=0)
    {
        remainder = bin % 10; bin /= 10;
        decimalNumber += remainder*pow(2,i); ++i;
    }
    return decimalNumber;
}

std::vector<int> BobsMap::convertBitsToDecimal(const std::vector<int> bits, int geneLen) {

    //COnverts bits to string genes
    std::vector<QString> genesStrings;
    for(size_t i = 0; i < bits.size()/geneLen; i++) {
        QString currentLocus;
        for(size_t j = 0; j < geneLen; j++) {
           QString str = QString::number(bits[i * geneLen + j]);
            currentLocus.append(str);
        }
        genesStrings.push_back(currentLocus);
    }

    //Convert genes to binary integer
    std::vector<int> intBinaryGens;
    for(size_t i = 0; i < genesStrings.size(); i++) {
        intBinaryGens.push_back(genesStrings[i].toInt());
    }

    //Convert binary integer to decimal integer
    std::vector<int> intDecimalGenes;
    for(size_t i = 0; i < intBinaryGens.size(); i++){
        intDecimalGenes.push_back(convertBinaryToDecimal(intBinaryGens[i]));
    }
    return intDecimalGenes;
}
//int BobsMap::convertDecimalToBinary(int n)
//{
//    int binaryNumber = 0;
//    int remainder, i = 1, step = 1;
//    while (n!=0)
//    {
//        remainder = n%2;
//        n /= 2;
//        binaryNumber += remainder*i; i *= 10;
//    }
//    return binaryNumber;
//}
