/*

-------------------------------------------------------------------------

    RadioItem store radio main data

    title_ - name of radio
    id_ - doesnt used but maybe will be need in future
    souce_url_ - stores url to radio stream resource
    source_img_url - doesnt used but maybe imges will be need in future

-------------------------------------------------------------------------

*/

#ifndef RADIOITEM_H
#define RADIOITEM_H

#include <QString>
#include <QJsonObject>

#include "helperfunctions.h"
#include "musicitem.h"

namespace Radio {

class RadioItem : MusicItem::MusicItem
{
public:
    explicit RadioItem(QString title, QString id, QString source_url, QString source_img_url);

    QString getTitle() const noexcept;
    QString getId() const noexcept;
    QString getSourceUrl() const noexcept;
    QString getSourceImgUrl() const noexcept;

    QJsonObject toJson() const override;
    static Radio::RadioItem fromJson(const QJsonObject& obj);

private:

    QString title_;
    QString id_;
    QString source_url_;
    QString source_img_url_;

};

}

#endif // RADIOITEM_H