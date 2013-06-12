#pragma once

#include "ofMain.h"

class Blox {
  public:
    Blox(ofSoundPlayer& soundPlayer, int nBands);

    void update();
    void draw();

  private:
    int nBands;
    ofSoundPlayer soundPlayer;
    float *fftSmooth;
};
