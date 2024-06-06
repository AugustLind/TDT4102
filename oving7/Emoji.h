#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
// Abstrakt klasse. Arvende konkrete klasser må implementere funksjonen draw()
// som tegner former i vinduet de skal bli vist i.
class Emoji{
public:
    virtual void draw(AnimationWindow&) = 0;
    virtual ~Emoji(){}; //destruktør
};

class Face : public Emoji{
protected:
    Point c;
    int r;
public:
    Face(Point c, int r) : c{c}, r{r} {}
    void draw(AnimationWindow& win) override;
};


class EmptyFace : public Face{
protected:
    int radius;
public:
    EmptyFace(Point c, int r, int radiusEye) : Face{c, r}{;
            radius = radiusEye;
    };
    void draw(AnimationWindow& win) override;
};

class SmillingFace : public EmptyFace{
protected:
    int startDegree;
    int endDegree;
public:
    SmillingFace(Point c, int r, int radius, int startDeg, int endDeg) : EmptyFace{c, r, radius}{
            startDegree = startDeg;
            endDegree = endDeg;
    }
    void draw(AnimationWindow& win) override;
};

class SadFace : public SmillingFace{
public: 
    void draw(AnimationWindow& win) override;
    SadFace(Point c, int r, int radius, int startDegree, int endDegree) : SmillingFace{c, r, radius, startDegree, endDegree} {}
};

class AngryFace : public SadFace{
public: 
    void draw(AnimationWindow& win) override;
    AngryFace(Point c, int r, int radius, int startDegree, int endDegree) : SadFace{c, r, radius, startDegree, endDegree} {}
};

class SuprisedFace : public EmptyFace{
public:
    SuprisedFace(Point c, int r, int radius) : EmptyFace{c, r, radius}{}
    void draw(AnimationWindow& win) override;
};

class ScaredFace : public SuprisedFace{
public: 
    void draw(AnimationWindow& win) override;
    ScaredFace(Point c, int r, int radius) : SuprisedFace{c, r, radius} {}
};