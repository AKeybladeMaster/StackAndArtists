#include "artist.h"

/**
 * @brief empty constructor (allocate)
 */
Artist::Artist() {}

/**
 * @brief default constructor
 */
Artist::Artist(QString link, QString name) : link_(link), name_(name) {}

QString Artist::getLink() const {
    return link_;
}

QString Artist::getName() const {
    return name_;
}

QLabel *Artist::createArtistHyperLink() {
    QLabel *label = new QLabel;
    label -> setText("<a href='" + link_ + "'>" + name_ + "</a>");
    if (link_ == "")
        label -> setStyleSheet("QLabel {color: red; font-weight: bold; }");
    else
        label -> setStyleSheet("QLabel {font-weight: bold; }");

    label -> setOpenExternalLinks(true);
    return label;
}
