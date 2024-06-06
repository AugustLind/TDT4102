#include "Emoji.h"

void Face::draw(AnimationWindow& win) {
    win.draw_circle(c, r, Color::yellow);
}

void EmptyFace::draw(AnimationWindow& win){
    Face::draw(win);

    Point leftEye {c.x - r/3, c.y - r/3};
    Point rightEye {c.x + r/3, c.y - r/3};

    win.draw_circle(leftEye,radius,Color::black);
    win.draw_circle(rightEye,radius,Color::black);
}

void SmillingFace::draw(AnimationWindow& win){
    EmptyFace::draw(win);
    
    int width = r - 3*radius;
    Point centerPoint {c.x, c.y + radius/2};
    int height = r/2;

    win.draw_arc(centerPoint,width,height,startDegree,endDegree,Color::black);
}

void SadFace::draw(AnimationWindow& win){
    EmptyFace::draw(win);

    int width = r - 3*radius;
    Point centerPoint {c.x, c.y + radius*3};
    int height = -r/3;

    win.draw_arc(centerPoint,width,height,endDegree,startDegree,Color::black);
}

void AngryFace::draw(AnimationWindow& win){
    SadFace::draw(win);

    /*Venstre bryn*/
    Point leftBottomL {c.x - r/3 - radius,  c.y - r/3 - radius*3/2};
    Point leftTopL {c.x - r/3 - radius/2,  c.y - r/3 - radius*2};
    Point rightTopL {c.x - r/3+ radius*3/2,  c.y - r/3 - radius};
    Point rightBottomL {c.x - r/3+ radius,  c.y - r/3 - radius/2};

    /*Hoyre bryn*/
    Point rightBottomR {c.x + r/3 + radius,  c.y - r/3 - radius*3/2}; 
    Point rightTopR {c.x + r/3 + radius/2,  c.y - r/3 - radius*2}; 
    Point leftTopR {c.x + r/3 - radius*3/2,  c.y - r/3 - radius}; 
    Point leftBottomR {c.x + r/3 - radius,  c.y - r/3 - radius/2}; 

    win.draw_quad(leftBottomL,leftTopL,rightTopL,rightBottomL,Color::black);
    win.draw_quad(rightBottomR,rightTopR,leftTopR, leftBottomR,Color::black);

}

void SuprisedFace::draw(AnimationWindow& win){
    EmptyFace::draw(win);
    int radiusM = radius*2;
    Point center {c.x, c.y+radiusM};
    win.draw_circle(center, radiusM, Color::black);
}

void ScaredFace::draw(AnimationWindow& win){
    SuprisedFace::draw(win);

    /*Venstre bryn*/
    Point rightBottomL {c.x - r/3 + radius,  c.y - r/3 - radius*3/2}; 
    Point rightTopL {c.x - r/3 + radius/2,  c.y - r/3 - radius*2}; 
    Point leftTopL {c.x - r/3 - radius*3/2,  c.y - r/3 - radius}; 
    Point leftBottomL {c.x - r/3 - radius,  c.y - r/3 - radius/2}; 
    /*Hoyre bryn*/
    Point leftBottomR {c.x + r/3 - radius,  c.y - r/3 - radius*3/2};
    Point leftTopR {c.x + r/3 - radius/2,  c.y - r/3 - radius*2};
    Point rightTopR {c.x + r/3+ radius*3/2,  c.y - r/3 - radius};
    Point rightBottomR {c.x + r/3+ radius,  c.y - r/3 - radius/2};


    win.draw_quad(leftBottomL,leftTopL,rightTopL,rightBottomL,Color::black);
    win.draw_quad(rightBottomR,rightTopR,leftTopR, leftBottomR,Color::black);



}
