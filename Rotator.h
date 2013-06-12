#pragma once

#include "ofMain.h"

class Rotator {
  public:
    Rotator();

  private:
    float *modulators;
    void modulatedRotation();
    void defaultRotation();
};
