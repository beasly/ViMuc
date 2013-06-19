#pragma once

#include "ofMain.h"

class Scene : public ofBaseApp {
  public:
    Scene();

    void setup();
    void update();
    void draw();

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
