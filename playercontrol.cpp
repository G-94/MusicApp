#include "playercontrol.h"

PlayerControl::PlayerControl(User_Data::UserDataManager* manager, QObject *parent) :
    QObject(parent), player_(new MusicPlayer::Player(this)), manager_(manager)
{}