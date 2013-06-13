#pragma once

#include "ofMain.h"

class Blox {
  public:
    Blox();

    void update();
    void draw();

    void setBands(int bands);

  private:
    int nBands;
    float *fftSmooth;
};
