#pragma once

#include "ofMain.h"
#include "Blox.h"

class ViMuc : public ofBaseApp {
  public:
    ViMuc() : blocks() {}
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  private:
    Blox blocks;
    bool right;
    ofSoundPlayer test;
    int nBands;
    ofEasyCam cam;
    int angleX;
    int angleY;
    int angleZ;

    void modulatedRotation(float deep, float mid, float high);
    void defaultRotation();
};
