#include <stdlib.h>
#include <stdio.h>

#include "Blox.h"

Blox::Blox() {}

/**
 * This is the function I want to use as modulator for the rotation of my
 * scene. It recieves the vals array of 3 values (deep, mid and high) and the
 * direction.
 * It modifies these values directly, because the context in wich it is de-
 * referenced and called is a method of the Rotator class.
 * This behaviour is dangerous, so don't do stupid things with it.
 */
void modulate(float* vals, bool right) {
  vals[0] += !(right) ? vals[0] * 1 : -(vals[0] * 1);
  vals[1] += !(right) ? vals[1] * 2 : -(vals[1] * 2);
  vals[2] += !(right) ? vals[2] * 4 : -(vals[2] * 4);

  right = vals[0] < 0.25 ? !right : right;
}

void Blox::draw() {
  /** Initialiez a function pointer */
  void (*modu)(float*, bool);
  /** Assign the modulate function to the pointer */
  modu = &modulate;

  float *vals = new float[3];

  vals[0] = getFFTSmooth()[0];
  vals[1] = getFFTSmooth()[3];
  vals[2] = getFFTSmooth()[7];

  /** Pass the modu function pointer to the customModulatedRotation method */
  rotator.customModulatedRotation(modu, vals);
  rotator.rotate();

  float width = (float)45;
  ofTranslate(-(getBands() * width) / 2, 0, 0);

  for (int i = 0; i < getBands(); i++) {
    float modu = 2 * getFFTSmooth()[i] * pow((i + 1.0), 6/4);

    ofTranslate(50, 0, 0);
    //ofSphere(100 * modu);

    ofPushMatrix();
    ofSetColor(255, 0, 0);
    ofFill();
    ofScale(0.6, modu, 1);
    ofBox(width);
    ofSetColor(0);
    ofNoFill();
    ofBox(width);
    ofPopMatrix();
  }
}
