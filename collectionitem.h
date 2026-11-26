/*

-------------------------------------------------------------------------

    AlbumItem store albums main data

    title_ - name of album
    year_ - store year of album
    id_ - used to find albums songs, get album page

-------------------------------------------------------------------------

*/

#ifndef COLLECTIONITEM_H
#define COLLECTIONITEM_H

#include <QString>
#include <QJsonObject>

#include "musicitem.h"

namespace Collection {

class CollectionItem final : public MusicItem::MusicItem
{
public:
    explicit CollectionItem(QString title, QString id);

    QString getTitle() const noexcept;
    QString getId() const noexcept;

    QJsonObject toJson() const override;
    static Collection::CollectionItem fromJson(const QJsonObject& obj);

private:

    QString title_;
    QString id_;

};

}

#endif // COLLECTIONITEM_H