/*

-------------------------------------------------------------------------

    MusicItem parent class for music items
        what can store played counters

-------------------------------------------------------------------------

*/

#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QJsonObject>

namespace MusicItem {

class MusicItem
{
public:
    MusicItem() = default;

    int getPlayedCounter() const noexcept;
    void setPlayedCounter(int new_val) noexcept;
    void incrPlayedCounter() noexcept;

    virtual QJsonObject toJson() const = 0;

private:

    // played counter
    int played_counter_ = 0;

};

}

#endif // MUSICITEM_H