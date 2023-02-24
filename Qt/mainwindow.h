#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "artist.h"
#include <QMainWindow>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString downloadFile(const QString &urlString);

    void showMainWindow();

    QList<Artist> parseResult(QString downloadedFile);

    void loadArtists();

    QChartView *createPieGraph(QList<Artist> artists);

    QChartView *createVsGraph();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
