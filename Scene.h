#pragma once

#include "ofMain.h"

class Scene : public ofBaseApp {
  public:
    Scene();

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

    float* getFFTSmooth() const;
    float* getFFTPlain() const;
    void modulatedRotation(float deep, float mid, float high);
    void defaultRotation();
    void setBands(int bands);
    int getBands() const;

  private:
    int nBands;

    bool right;
    int angleX;
    int angleY;
    int angleZ;

    float *fftSmooth;
    float *fftPlain;
};
