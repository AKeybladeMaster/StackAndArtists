#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Universal vs Emi Artists");
    w.showMainWindow();
    w.show();
    return a.exec();
}
