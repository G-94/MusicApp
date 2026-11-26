/*

-------------------------------------------------------------------------

    GenreItem class store genre data

    title_ to store genre name
    id_ to store resource genre id
        what used to find genre songs list

-------------------------------------------------------------------------

*/

#ifndef GENREITEM_H
#define GENREITEM_H

#include <QString>
#include <QJsonObject>

#include "musicitem.h"

namespace Genre {

class GenreItem final : public MusicItem::MusicItem
{
public:
    GenreItem(QString title, QString id);

    QString getTitle() const noexcept;
    QString getId() const noexcept;

    QJsonObject toJson() const override;
    static Genre::GenreItem fromJson(const QJsonObject& obj);

private:

    QString title_;
    QString id_;
};

}

#endif // GENREITEM_H