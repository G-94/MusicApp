#ifndef MUSICAPI_H
#define MUSICAPI_H

#include <QObject>

class MusicApi : public QObject
{
    Q_OBJECT
public:
    explicit MusicApi(QObject *parent = nullptr);

signals:
};

#endif // MUSICAPI_H
