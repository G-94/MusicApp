/*

-------------------------------------------------------------------------

    RadioItem store radio main data

    name_ - name of radio
    id_ - doesnt used but maybe will be need in future
    souce_url_ - stores url to radio stream resource
    source_img_url - doesnt used but maybe imges will be need in future

-------------------------------------------------------------------------

*/

#ifndef RADIOITEM_H
#define RADIOITEM_H

#include <QString>

#include "helperfunctions.h"

namespace Radio {

class RadioItem
{
public:
    explicit RadioItem(QString name, QString id, QString source_url, QString source_img_url);

    QString getName() const noexcept;
    QString getId() const noexcept;
    QString getSourceUrl() const noexcept;
    QString getSourceImgUrl() const noexcept;

private:

    QString name_;
    QString id_;
    QString source_url_;
    QString source_img_url_;

};

}

#endif // RADIOITEM_H
