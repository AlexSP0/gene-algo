#ifndef BOBSMAP_H
#define BOBSMAP_H

#include <mainwindow.h>
#include <vector>

namespace Ui
{
class MainWindow;
}


class BobsMap
{
public:
    BobsMap(Ui::MainWindow*);

    double testRoute(const std::vector<int> bits, int geneLen);

private:

    Ui::MainWindow *map;

//    int convertDecimalToBinary(int n);
    int convertBinaryToDecimal(int bin);

    std::vector<int> convertBitsToDecimal(const std::vector<int> bits, int geneLen);
};

#endif // BOBSMAP_H
