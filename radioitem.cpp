#include "radioitem.h"

Radio::RadioItem::RadioItem(QString name, QString id,
        QString source_url, QString source_img_url) :
    name_(std::move(name)), id_(std::move(Helper::getOnlyNumericFromStr(id))),
    source_url_(std::move(source_url)), source_img_url_(std::move(source_img_url))
{}

QString Radio::RadioItem::getName() const noexcept
{
    return name_;
}

QString Radio::RadioItem::getId() const noexcept
{
    return id_;
}

QString Radio::RadioItem::getSourceUrl() const noexcept
{
    return source_url_;
}

QString Radio::RadioItem::getSourceImgUrl() const noexcept
{
    return source_img_url_;
}