/*

-------------------------------------------------------------------------

    ArtistItem class store main artists data

    name_ to store artist name
    id_ to store resource artist id
        what used to find artists songs list

-------------------------------------------------------------------------

*/

#ifndef ARTISTITEM_H
#define ARTISTITEM_H

#include <QObject>
#include <QString>

namespace Artists {

class ArtistItem
{

public:
    explicit ArtistItem(QString name, QString id);

    QString getName() const noexcept;
    QString getId() const noexcept;

private:

    QString name_;
    QString id_;

signals:
};

}

#endif // ARTISTITEM_H