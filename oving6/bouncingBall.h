#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"


void bouncingBall();

struct Config {
    int upColor;
    int downColor;
    int velocity;
    bool isFast;
    map<int, Color> colorMap;
};

istream &operator>>(std::istream &is, Config &cfg);