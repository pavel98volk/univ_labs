#include "player.h"
#include<QDebug>

Player::Player(bool isWhite,bool isAI):QObject()
{
this->isAI=isAI;
    this->isWhite=isWhite;
}

Player::~Player()
{
}
