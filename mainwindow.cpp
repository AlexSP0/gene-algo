#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <cmath>
#include <QPainter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent, std::vector<std::vector<char>> map)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resercher = std::make_unique<BobTheResercher>(BobTheResercher(CROSSOVER_RATE,
                                                                  MUTATE_RATE,
                                                                  POPULATION_SIZE,
                                                                  NUMBER_BITS,
                                                                  NUMBER_BITS_PER_GENE));

    currentBob = 0;
    currentGen = 0;

    wallImage      = new QImage();
    exitImage      = new QImage();
    bobImage       = new QImage();
    freeSpaceImage = new QImage();
    visitedImage   = new QImage();

    wallImage->load("wall.png");
    exitImage->load("exit.png");
    bobImage->load("bob.png");
    freeSpaceImage->load("freespace.png");
    visitedImage->load("visited.png");

    setMap(map);
    resetBob();

    timerId = startTimer(1);

    repaint();
}

MainWindow::~MainWindow()
{
    delete wallImage;
    delete exitImage;
    delete bobImage;
    delete freeSpaceImage;
    delete visitedImage;

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter qp(this);

    renderMap(&qp);
}

void MainWindow::getCoordinates(int &posX, int &posY, char symbol)
{
    bool isFound = false;

    for (size_t y = 0; y < MAP_HEIGHT_Y; y++)
    {
        for (size_t x = 0; x < MAP_WIDTH_X; x++)
        {
            char current = labMap[y][x];
            if (current == symbol)
            {
                posX    = x;
                posY    = y;
                isFound = true;
                break;
            }
        }
        if (isFound)
        {
            break;
        }
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    processAllGenerations();
}

void MainWindow::renderMap(QPainter *qp)
{
    for (size_t y = 0; y < MAP_HEIGHT_Y; y++)
    {
        for (size_t x = 0; x < MAP_WIDTH_X; x++)
        {
            char current = labMap[y][x];
            QImage *currentImage;

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
            qp->drawImage(x * 10, y * 10, *currentImage);

            setStrings();
        }
    }
}

void MainWindow::setMap(std::vector<std::vector<char>> map)
{
    MAP_HEIGHT_Y = map.size();
    MAP_WIDTH_X  = map[0].size();

    labMap     = map;
    initialMap = map;

    resize(MAP_WIDTH_X * 15 + 250,
           MAP_HEIGHT_Y * 10 + 22 * NUMBER_OF_GENERATIONS + (MAP_HEIGHT_Y * 10 + 15 * 0) + 25);
    this->repaint();

    ui->currentPopulationSize->move(3, MAP_HEIGHT_Y * 10 + 15 * 0);
    ui->currentGeneration->move(3, MAP_HEIGHT_Y * 10 + 15 * 1);
    ui->currentBobMoving->move(3, MAP_HEIGHT_Y * 10 + 15 * 2);
    ui->bestFitnesInGeneration->move(3, MAP_HEIGHT_Y * 10 + 15 * 3);
    ui->TotalfitnessInThisGeneration->move(3, MAP_HEIGHT_Y * 10 + 15 * 4);

    ui->resultsTable->move(0, MAP_HEIGHT_Y * 10 + 15 * 0);
    ui->resultsTable->setColumnCount(5);
    ui->resultsTable->setFixedHeight(MAP_HEIGHT_Y * 10 + 22 * NUMBER_OF_GENERATIONS);
    ui->resultsTable->setFixedWidth(MAP_WIDTH_X * 15 + 250);

    QStringList headers;
    headers << "Generation"
            << "Population"
            << "Current Bob"
            << "Best Fitness"
            << "Total fitness";
    ui->resultsTable->setHorizontalHeaderLabels(headers);
    ui->resultsTable->insertRow(resercher->generationNumber);

    this->repaint();
}

void MainWindow::setStrings()
{
    ui->resultsTable->setItem(resercher->generationNumber,
                              0,
                              new QTableWidgetItem(
                                  currentGenerationString.arg(resercher->generationNumber)));
    ui->resultsTable->setItem(resercher->generationNumber,
                              1,
                              new QTableWidgetItem(
                                  currentPopulationSizeString.arg(resercher->getPopulationSize())));
    ui->resultsTable->setItem(resercher->generationNumber,
                              2,
                              new QTableWidgetItem(currentBobNumberString.arg(currentBob)));
    ui->resultsTable->setItem(resercher->generationNumber,
                              3,
                              new QTableWidgetItem(
                                  bestFitnessString.arg(resercher->bestFitnessScore)));
    ui->resultsTable->setItem(resercher->generationNumber,
                              4,
                              new QTableWidgetItem(totalFitnessOfGenerationString.arg(
                                  resercher->totalFitnessScore)));
}

void MainWindow::moveBob(int direction)
{
    if (direction == NORTH && (currentBob_y - 1) >= 0 && (currentBob_y - 1) < labMap.size())
    {
        if (labMap[currentBob_y - 1][currentBob_x] == ' ')
        {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_y--;
            labMap[currentBob_y][currentBob_x] = 'b';
            return;
        }
    }
    if (direction == SOUTH && (currentBob_y + 1) >= 0 && (currentBob_y + 1) < labMap.size())
    {
        if (labMap[currentBob_y + 1][currentBob_x] == ' ')
        {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_y++;
            labMap[currentBob_y][currentBob_x] = 'b';
            return;
        }
    }
    if (direction == EAST && (currentBob_x + 1) >= 0 && (currentBob_x + 1) < labMap[0].size())
    {
        if (labMap[currentBob_y][currentBob_x + 1] == ' ')
        {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_x++;
            labMap[currentBob_y][currentBob_x] = 'b';
            return;
        }
    }
    if (direction == WEST && (currentBob_x - 1) >= 0 && (currentBob_x - 1) < labMap[0].size())
    {
        if (labMap[currentBob_y][currentBob_x - 1] == ' ')
        {
            labMap[currentBob_y][currentBob_x] = 'v';
            currentBob_x--;
            labMap[currentBob_y][currentBob_x] = 'b';
            return;
        }
    }
}

void MainWindow::resetBob()
{
    labMap = initialMap;

    int x, y;
    getCoordinates(x, y, 'b');
    start_x      = x;
    start_y      = y;
    currentBob_x = x;
    currentBob_y = y;

    getCoordinates(x, y, 'e');
    target_x = x;
    target_y = y;

    repaint();
}

void MainWindow::processNextGen()
{
    Genome currentBobGenome = resercher.get()->populationGenoms[currentBob];

    if (currentGen < currentBobGenome.bits.size() / NUMBER_BITS_PER_GENE)
    {
        std::vector<int> directions = convertBitsToDecimal(currentBobGenome.bits,
                                                           NUMBER_BITS_PER_GENE);
        moveBob(directions[currentGen]);
        repaint();
        currentGen++;
    }
    else
    {
        double currentFitness                                 = calculateFitness();
        resercher.get()->populationGenoms[currentBob].fitness = currentFitness;
        resercher.get()->totalFitnessScore = resercher.get()->totalFitnessScore + currentFitness;

        if (resercher.get()->bestFitnessScore < currentFitness)
        {
            resercher.get()->bestFitnessScore = currentFitness;
        }

        currentGen = 0;
        currentBob++;
        resetBob();
    }
}

void MainWindow::processAllGenerations()
{
    if (resercher->generationNumber < NUMBER_OF_GENERATIONS)
    {
        if (currentBob < resercher.get()->populationGenoms.size())
        {
            processNextGen();
        }
        else
        {
            int newPopulationSize = resercher->getPopulationSize()
                                    - resercher->getPopulationSize() * REDUCTION_RATIO;
            resercher->breedNewGeneration(newPopulationSize);
            ui->resultsTable->insertRow(resercher->generationNumber);
            currentBob = 0;
            resetBob();
        }
    }
}

double MainWindow::calculateFitness()
{
    int diffX = abs(currentBob_x - target_x);
    int diffY = abs(currentBob_y - target_y);
    return 1 / (double) (diffX + diffY + 1);
}

int MainWindow::convertBinaryToDecimal(int bin)
{
    int decimalNumber = 0, i = 0, remainder;
    while (bin != 0)
    {
        remainder = bin % 10;
        bin /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }
    return decimalNumber;
}

std::vector<int> MainWindow::convertBitsToDecimal(const std::vector<int> bits, int geneLen)
{
    //COnverts bits to string genes
    std::vector<QString> genesStrings;
    for (size_t i = 0; i < bits.size() / geneLen; i++)
    {
        QString currentLocus;
        for (size_t j = 0; j < geneLen; j++)
        {
            QString str = QString::number(bits[i * geneLen + j]);
            currentLocus.append(str);
        }
        genesStrings.push_back(currentLocus);
    }

    //Convert genes to binary integer
    std::vector<int> intBinaryGens;
    for (size_t i = 0; i < genesStrings.size(); i++)
    {
        intBinaryGens.push_back(genesStrings[i].toInt());
    }

    //Convert binary integer to decimal integer
    std::vector<int> intDecimalGenes;
    for (size_t i = 0; i < intBinaryGens.size(); i++)
    {
        intDecimalGenes.push_back(convertBinaryToDecimal(intBinaryGens[i]));
    }
    return intDecimalGenes;
}
