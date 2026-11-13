#ifndef MUSICAPITESTS_H
#define MUSICAPITESTS_H

#include <QObject>
#include <QtTest/QTest>

#include "musicapi.h"

namespace testApi {

class MusicApiTests : public QObject
{
    Q_OBJECT
private slots:
    void testSimpleQuery();
    void testQueryWithSpaces();
};

}

#endif // MUSICAPITESTS_H
