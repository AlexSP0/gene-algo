
#include "bobtheresercher.h"
#include "mainwindow.h"

#include <QApplication>
#include <bobtheresercher.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<std::vector<char>> m = {{'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w','w','w','w','w','w','w','w','w','w'},
                                        {'w', ' ', ' ', 'w', 'w', ' ', 'w', ' ', ' ', 'w',' ',' ',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', 'e', ' ', 'w', 'w', ' ', 'w', ' ', ' ', ' ',' ',' ',' ',' ',' ',' ',' ','w','w','w'},
                                        {'w', ' ', ' ', 'w', 'w', ' ', ' ', ' ', ' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', ' ', ' ', ' ', 'w', ' ', ' ', ' ', ' ', ' ',' ',' ','w','w',' ',' ',' ','w',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', ' ', 'w', ' ', 'w',' ',' ','w',' ','w',' ',' ','w',' ','w'},
                                        {'w', ' ', 'w', 'w', 'w', ' ', ' ', ' ', ' ', ' ',' ',' ','w',' ',' ','w',' ','w',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ','w',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'w',' ',' ',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', 'w',' ',' ',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', 'w',' ','b',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', ' ', ' ', ' ', ' ', ' ', 'w', ' ', ' ', 'w',' ',' ',' ',' ',' ',' ',' ',' ',' ','w'},
                                        {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w','w','w','w','w','w','w','w','w','w','w'}};

    MainWindow w(nullptr, m);

    w.show();

    return a.exec();
}
