#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bobtheresercher.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

const int NORTH = 0;
const int SOUTH = 1;
const int EAST = 2;
const int WEST = 3;

const double CROSSOVER_RATE = 0.7;
const double MUTATE_RATE = 0.001;
const int POPULATION_SIZE = 140;
const int NUMBER_BITS = 70;
const int NUMBER_BITS_PER_GENE = 2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, std::vector<std::vector<char>>);
    ~MainWindow();

    void renderMap();

    void moveBob(int);
    void resetBob();

    int currentBob_x;
    int currentBob_y;

    int target_x;
    int target_y;

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<BobTheResercher> resercher;

    int timerId;

    int start_x;
    int start_y;

    int MAP_WIDTH_X;
    int MAP_HEIGHT_Y;

    std::vector<std::vector<char>> labMap;
    std::vector<std::vector<char>> initialMap;

    QImage wallImage;
    QImage exitImage;
    QImage bobImage;
    QImage freeSpaceImage;
    QImage visitedImage;

    void getCoordinates(int &x, int &y, char symbol);

    void timerEvent(QTimerEvent);

    void setMap(std::vector<std::vector<char>> map);
};
#endif // MAINWINDOW_H
