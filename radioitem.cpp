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

QJsonObject Radio::RadioItem::toJson()
{
    QJsonObject obj;
    obj["title"] = title_;
    obj["id"] = id_;
    obj["url"] = source_url_;
    obj["imgUrl"] = source_img_url_;
    obj["playedCounter"] = getPlayedCounter();
    return obj;
}

Radio::RadioItem Radio::RadioItem::fromJson(const QJsonObject &obj)
{
    Radio::RadioItem item {
        obj.value("title").toString(),
        obj.value("id").toString(),
        obj.value("url").toString(),
        obj.value("img").toString()
    };

    item.setPlayedCounter(obj.value("playedCounter").toInt());

    return item;
}