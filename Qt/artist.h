#ifndef ARTIST_H
#define ARTIST_H
#include <QString>
#include <QLabel>

class Artist
{
public:
    Artist();

    Artist(QString link, QString name);

    QString getLink() const;
    QString getName() const;
    QLabel *createArtistHyperLink();

private:
    QString link_;
    QString name_;
};

#endif // ARTIST_H
