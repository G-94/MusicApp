#include "radioitem.h"

Radio::RadioItem::RadioItem(QString title, QString id,
        QString source_url, QString source_img_url) :
    title_(std::move(title)), id_(std::move(Helper::getOnlyNumericFromStr(id))),
    source_url_(std::move(source_url)), source_img_url_(std::move(source_img_url))
{}

QString Radio::RadioItem::getTitle() const noexcept
{
    return title_;
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