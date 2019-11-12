#include "mainwindow.h"
#include "authentication.h"
#include "quotestats.h"
#include "quotestatus.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();

    if(w.STOPAPP){
        return 0;
    }


    return a.exec();
}
