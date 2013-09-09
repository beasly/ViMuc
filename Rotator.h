#pragma once

#include "ofMain.h"

class Rotator {
  public:
    Rotator();

    void modulatedRotation(float deep, float mid, float high);
    void defaultRotation();
    void rotate() const;

  private:
    bool right;
    float angles[3] = {};
};
