#include "userdataloader.h"

QJsonObject User_Data::UserDataLoader::load(const QString &path)
{
    QFile file(path);
    if (not file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "error on openning file " << path;
        return {};
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if(err.error != QJsonParseError::NoError) {
        qDebug() << "error on parse data " << path;
        return {};
    }

    if (not doc.isObject()) {
        qDebug() << "error json doc not an object";
        return {};
    }

    return doc.object();
}

bool User_Data::UserDataLoader::save(const QString &path, const QJsonObject& data)
{
    QSaveFile file(path);
    if (not file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error on openning file " << path;
        return {};
    }

    const QJsonDocument doc(data);
    const QByteArray json_data = doc.toJson(QJsonDocument::Indented);

    if (file.write(json_data) != json_data.size()) {
        qDebug() << "error on writen file" << file.errorString();
        file.cancelWriting();
        return false;
    }

    if(not file.commit()) {
        qDebug() << "error on commit file" << file.errorString();
        return false;
    }

    return true;
}

