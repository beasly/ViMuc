#include <stdlib.h>
#include <cmath>

#include "ofMain.h"
#include "Rotator.h"

Rotator::Rotator() {
  right = true;
  fill_n(angles, 3, 0);
}

void Rotator::customModulatedRotation(void (*modu)(float*, bool),
    float *vals) {

  modu(vals, right);

  angles[0] += !(right) ? vals[0] : -(vals[0]);
  angles[1] += !(right) ? vals[1] : -(vals[1]);
  angles[2] += !(right) ? vals[2] : -(vals[2]);

  checkFullRotation();
}

void Rotator::modulatedRotation(float deep, float mid, float high) {
  angles[0] += !(right) ? deep * 5 : -(deep * 5);
  angles[1] += !(right) ? mid * 7 : -(mid * 7);
  angles[2] += !(right) ? high * 10 : -(high * 10);

  right = deep < 0.25 ? !right : right;

  checkFullRotation();
}

void Rotator::checkFullRotation() {
  angles[0] = (abs(angles[0]) == 360) ? 0 : angles[0];
  angles[1] = (abs(angles[1]) == 360) ? 0 : angles[1];
  angles[2] = (abs(angles[2]) == 360) ? 0 : angles[2];
}

void Rotator::rotate() const {
  ofRotateX((float)angles[0] / 1);
  ofRotateY((float)angles[1] / 1);
  ofRotateZ((float)angles[2] / 1);
}

