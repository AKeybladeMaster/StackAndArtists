#include "mainwindow.h"
#include "artist.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QtCharts>

QList<Artist> universalArtists, emiArtists;
QWidget *mainWidget;
QGridLayout *mainLayout;

// parte compare
//QBarSeries *series;
//QBarCategoryAxis *barStatAxis;
//QChart *chart;
//QChartView *chartView;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::downloadFile(const QString &urlString)
{
    QNetworkAccessManager manager;
    QNetworkRequest request(urlString);
    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error in" << reply -> url() << ":" << reply -> errorString();
        return QString();
    }

    QString downloadedFile = reply->readAll();
    reply -> deleteLater();

    return downloadedFile;
}

QList<Artist> MainWindow::parseResult(QString downloadedFile) {

    QList<Artist> tmpArtists;

    QStringList lines = downloadedFile.split("\n");

    for (const QString &line : lines) {
            int separatorIndex = line.indexOf(" ");
            if (separatorIndex == -1) {
                continue;
            }

            QString link = line.left(separatorIndex).replace("\"", "");
            if (!link.startsWith("http") && (link != ""))
                link = "https://en.wikipedia.org" + link;

            QString artistName = line.mid(separatorIndex + 1).replace("_", " ");
            if (artistName.contains("&amp"))
                artistName = artistName.replace("&amp", "&");

            Artist artist(link, QString::fromUtf8(artistName.toLatin1().constData()));

            tmpArtists.append(artist);
        }
    return tmpArtists;
}

void MainWindow::loadArtists() {
    QString universalFile = downloadFile("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt");
    QString emiFile = downloadFile("http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt");

    universalArtists = parseResult(universalFile);
    emiArtists = parseResult(emiFile);
}


void MainWindow::showMainWindow() {

    mainWidget = new QWidget;
    mainLayout = new QGridLayout;

    if (universalArtists.isEmpty() && emiArtists.isEmpty())
        loadArtists();

    QTableWidget *universalTable = new QTableWidget(universalArtists.size(), 1);
    QTableWidget *emiTable = new QTableWidget(emiArtists.size(), 1);

    universalTable -> setHorizontalHeaderLabels(QStringList() << "Name");
    universalTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    emiTable -> setHorizontalHeaderLabels(QStringList() << "Name");
    emiTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < universalArtists.size(); i++) {
        Artist uniArtist = universalArtists.at(i);

        QLabel *res = uniArtist.createArtistHyperLink();
        res -> setAlignment(Qt::AlignCenter);

        universalTable -> setCellWidget(i, 0, res);
    }

    for (int i = 0; i < emiArtists.size(); i++) {
        Artist emiArtist = emiArtists.at(i);

        QLabel *res = emiArtist.createArtistHyperLink();
        res -> setAlignment(Qt::AlignCenter);

        emiTable -> setCellWidget(i, 0, res);
    }

    QLabel *uniTitle = new QLabel("Universal Artists");
    QLabel *emiTitle = new QLabel("Emi Artists");

    mainLayout -> setContentsMargins(20, 20, 20, 20);
    mainLayout -> addWidget(uniTitle, 0, 0);
    mainLayout -> addWidget(emiTitle, 0, 2);
    mainLayout -> addWidget(universalTable, 1, 0);
    mainLayout -> addWidget(emiTable, 1, 2);
    mainLayout -> addWidget(createPieGraph(universalArtists), 2, 0);
    mainLayout -> addWidget(createPieGraph(emiArtists), 2, 2);
    mainLayout -> addWidget(createVsGraph(), 1, 1);

    mainWidget -> setLayout(mainLayout);
    this -> setCentralWidget(mainWidget);
}

QChartView *MainWindow::createPieGraph(QList<Artist> artists) {

    QMap<QString, int> artistCount;
    QStringList colorNames = QColor::colorNames();
    QPieSeries *series = new QPieSeries();


    for (int i = 0; i < artists.size(); i++) {
        QString firstChar = artists.at(i).getName().left(1);
        if (!artistCount.contains(firstChar)) {
            artistCount[firstChar] = 1;
        } else {
            artistCount[firstChar]++;
        }
    }

    for (int i = 0; i < artistCount.size(); i++) {
        QColor color(colorNames[i % colorNames.size()]);
        QPieSlice *slice = series -> append(artistCount.keys().at(i), artistCount.values().at(i));
        slice -> setBrush(QBrush(color));
//        slice -> setLabel(QString::number(artistCount.values().at(i)));
        slice -> setLabelVisible(true);
        slice -> value();
    }

    QChart *chart = new QChart();

    chart -> addSeries(series);
    chart -> setAnimationOptions(QChart::SeriesAnimations);
    chart -> setTitle("Numero di artisti per ogni lettera");
    series -> setLabelsVisible(true);
    QFont font = chart -> titleFont();
    font.setBold(true);
    font.setPointSize(16);
    chart -> setTitleFont(font);
    chart -> legend() -> setAlignment(Qt::AlignRight);
    chart -> legend() -> setBackgroundVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView -> setRenderHint(QPainter::Antialiasing);
//    chartView -> setRubberBand(QChartView::RectangleRubberBand);

    return chartView;
}

QChartView *MainWindow::createVsGraph() {

    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();

    QBarCategoryAxis *barEtiquetteAxis = new QBarCategoryAxis();
    QStringList barEtiquettes;
    barEtiquettes << "Universal" << "Emi";
    barEtiquetteAxis -> append(barEtiquettes);

    QBarCategoryAxis *barEtiquetteAxis2 = new QBarCategoryAxis();
    QStringList barNumbers;
    barNumbers << "200" << "400" << "600" << "800" << "1000";
    barEtiquetteAxis2 -> append(barNumbers);

    chart -> setAxisX(barEtiquetteAxis, series);
    chart -> setAxisY(barEtiquetteAxis2, series);
    chart -> setAnimationOptions(QChart::SeriesAnimations);
    chart -> setTitle("Numero di artisti per etichetta");

    QBarSet *universalBar = new QBarSet("Universal artists");
    *universalBar << universalArtists.size();
    series -> append(universalBar);

    QBarSet *emiBar = new QBarSet("Emi artists");
    *emiBar << emiArtists.size();
    series -> append(emiBar);

    chart -> addSeries(series);

    QChartView *chartView = new QChartView(chart);

    chartView -> setRenderHint(QPainter::Antialiasing);

    return chartView;
}
