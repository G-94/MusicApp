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

#include <QString>
#include <QJsonObject>

#include "musicitem.h"

namespace Artists {

class ArtistItem : MusicItem::MusicItem
{

public:
    explicit ArtistItem(QString name, QString id);

    QString getName() const noexcept;
    QString getId() const noexcept;

    QJsonObject toJson() const override;
    static Artists::ArtistItem fromJson(const QJsonObject& obj);

private:

    QString name_;
    QString id_;

};

}

#endif // ARTISTITEM_H