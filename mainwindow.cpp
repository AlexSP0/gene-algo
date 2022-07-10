#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>


MainWindow::MainWindow(QWidget *parent, std::vector<std::vector<char>> map)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resercher = std::make_unique<BobTheResercher>(BobTheResercher(CROSSOVER_RATE, MUTATE_RATE, POPULATION_SIZE, NUMBER_BITS, NUMBER_BITS_PER_GENE, this));

    setMap(map);

    wallImage.load("wall.png");
    exitImage.load("exit.png");
    bobImage.load("bob.png");
    freeSpaceImage.load("freespace.png");
    visitedImage.load("visited.png");

    timerId = startTimer(1000);

    renderMap();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    renderMap();
}

void MainWindow::getCoordinates(int &posX, int &posY, char symbol)
{
    bool isFound = false;

    for (size_t y = 0; y < MAP_HEIGHT_Y; y++)
    {
        for (size_t x = 0; x < MAP_WIDTH_X; x++)
        {
            char current = labMap[y][x];
            if(current == symbol) {
                posX = x;
                posY = y;
                isFound = true;
                break;
            }
        }
        if(isFound) {
            break;
        }
    }
}

void MainWindow::timerEvent(QTimerEvent event)
{
    resercher.get()->run();
}

void MainWindow::renderMap()
{
    QPainter qp(this);

    for (size_t y = 0; y < MAP_HEIGHT_Y; y++)
    {
        for (size_t x = 0; x < MAP_WIDTH_X; x++)
        {
            char current = labMap[y][x];
            QImage currentImage;

            switch (current)
            {
            case 'w':
                currentImage = wallImage;
                break;
            case 'e':
                currentImage = exitImage;
                break;
            case 'b':
                currentImage = bobImage;
                break;
            case ' ':
                currentImage = freeSpaceImage;
                break;
            case 'v':
                currentImage = visitedImage;
                break;
            }
            qp.drawImage(x * 10, y * 10, currentImage);
        }
    }
}

void MainWindow::setMap(std::vector<std::vector<char>> map)
{
    MAP_HEIGHT_Y = map.size();
    MAP_WIDTH_X  = map[0].size();

    resize(MAP_WIDTH_X * 10, MAP_HEIGHT_Y * 10);

    this->repaint();

    labMap = map;
    initialMap = map;

    renderMap();
}

void MainWindow::moveBob(int direction)
{
    if(direction == NORTH && (currentBob_y-1) >= 0 && (currentBob_y-1) < labMap.size())   {
        if(labMap[currentBob_y-1][currentBob_x] == ' ') {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_y--;
            labMap[currentBob_y][currentBob_x] = 'b';
            renderMap();

            return;
        }
    }
    if(direction == SOUTH && (currentBob_y+1) >= 0 && (currentBob_y+1) < labMap.size())   {
        if(labMap[currentBob_y+1][currentBob_x] == ' ') {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_y++;
            labMap[currentBob_y][currentBob_x] = 'b';
            renderMap();
        }
    }
    if(direction == EAST && (currentBob_x+1) >= 0 && (currentBob_x+1) < labMap[0].size())   {
        if(labMap[currentBob_y][currentBob_x+1] == ' ') {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_x++;
            labMap[currentBob_y][currentBob_x] = 'b';
            renderMap();
        }
    }
    if(direction == WEST && (currentBob_x-1) >= 0 && (currentBob_x-1) < labMap[0].size())   {
        if(labMap[currentBob_y][currentBob_x-1] == ' ') {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_x--;
            labMap[currentBob_y][currentBob_x] = 'b';
            renderMap();
        }
    }
}

void MainWindow::resetBob()
{
    int x, y;
    getCoordinates(x,y, 'b');
    start_x = x;
    start_y = y;
    currentBob_x = x;
    currentBob_y = y;

    getCoordinates(x,y, 'e');
    target_x = x;
    target_y = y;

    labMap = initialMap;
    renderMap();

}
