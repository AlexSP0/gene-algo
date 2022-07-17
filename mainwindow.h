#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bobtheresercher.h"

#include <QLabel>
#include <QMainWindow>
#include <qboxlayout.h>

class BobTheResercher;

QT_BEGIN_NAMESPACE

namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

const int NORTH = 0;
const int SOUTH = 1;
const int EAST  = 2;
const int WEST  = 3;

const double CROSSOVER_RATE     = 0.7;
const double MUTATE_RATE        = 0.001;
const int POPULATION_SIZE       = 140;
const int NUMBER_BITS           = 100;
const int NUMBER_BITS_PER_GENE  = 2;
const int NUMBER_OF_GENERATIONS = 10; //Количество поколений
const float REDUCTION_RATIO     = 0.05;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, std::vector<std::vector<char>>);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

    void timerEvent(QTimerEvent *);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<BobTheResercher> resercher;

    int timerId;

    int start_x;
    int start_y;

    int MAP_WIDTH_X;
    int MAP_HEIGHT_Y;

    int currentBob; //Текущий Боб, который идет домой
    int currentGen; //Текущий ген Боба, который идет домой

    int currentBob_x;
    int currentBob_y;

    int target_x;
    int target_y;

    QString currentPopulationSizeString    = "%1";
    QString currentGenerationString        = "%1";
    QString currentBobNumberString         = "%1";
    QString bestFitnessString              = "%1";
    QString totalFitnessOfGenerationString = "%1";

    std::vector<std::vector<char>> labMap;
    std::vector<std::vector<char>> initialMap;

    QImage *wallImage;
    QImage *exitImage;
    QImage *bobImage;
    QImage *freeSpaceImage;
    QImage *visitedImage;

    void renderMap(QPainter *);

    void moveBob(int);
    void resetBob();
    void processNextGen();
    void processAllGenerations();

    double calculateFitness();
    int convertBinaryToDecimal(int bin);
    std::vector<int> convertBitsToDecimal(const std::vector<int> bits, int geneLen);
    void getCoordinates(int &x, int &y, char symbol);
    void setMap(std::vector<std::vector<char>> map);
    void setStrings();
};
#endif // MAINWINDOW_H
