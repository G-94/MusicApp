/*

-------------------------------------------------------------------------



-------------------------------------------------------------------------

*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace User_Data {

class FileManager final : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(const QString& save_path, QObject* parent = nullptr);

    void download(const QUrl& url);
    void remove(const QString& file_name);

private:

    QString save_path_;
    QNetworkAccessManager* manager_;

signals:

    void downloadFinished();
    void downloadError(const QString& msg);
    void removeFinished();
    void removeError(const QString& msg);

};

}

#endif // FILEMANAGER_H