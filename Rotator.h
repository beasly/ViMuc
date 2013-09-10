#pragma once

#include <vector>

#include "ofMain.h"

class Rotator {
  public:
    Rotator();

    /**
     * The customModulatedRotation method needs a pointer to a function as
     * argument. The dereferenced function gets an array of 3 elements as
     * first and a bool value switching the direction as second argument.
     * For an example @see the Blox scene implementation!
     */
    void customModulatedRotation(void (*modu)(float*, bool), float *vals);
    void modulatedRotation(float deep, float mid, float high);
    void defaultRotation();
    void rotate() const;

  private:
    bool right;
    float angles[3];
};
