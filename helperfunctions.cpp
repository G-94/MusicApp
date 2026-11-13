#include "helperfunctions.h"

quint32 Helper::castTextDurationToInt(const QString &duration) noexcept
{
    QList<QStringView> parts = QStringView(duration).split(':');
    try {
        return parts.at(0).toInt() * 60 + parts.at(1).toInt();
    } catch (...) {
        return 0;
    }
}

QJsonObject Helper::parseJsonStr(const QString &jsonText)
{
    QString cleaned = jsonText;
    cleaned.replace("&quot;", "\"");
    cleaned.replace("&#39;", "'");
    cleaned.replace("&amp;", "&");

    QJsonParseError jsonError{};
    QJsonDocument doc = QJsonDocument::fromJson(cleaned.toUtf8(), &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        //TODO THROW
    }

    if (not doc.isObject()) {
        //TODO THROW
    }

    return doc.object();
}

QString Helper::checkSourceUrl(QString url)
{
    if (not url.startsWith(HTTP_Literals::SOURCE_URL_ADDITIONAL)) {
        url.prepend(HTTP_Literals::SOURCE_URL_ADDITIONAL);
    }
    return url;
}
