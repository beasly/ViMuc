#include <stdlib.h>
#include <cmath>

#include "ofMain.h"
#include "Rotator.h"

Rotator::Rotator() {
  right = true;
}

void Rotator::modulatedRotation(float deep, float mid, float high) {
  angles[0] += !(right) ? deep * 5 : -(deep * 4);
  angles[1] += !(right) ? mid * 7 : -(mid * 9);
  angles[2] += !(right) ? high * 10 : -(high * 19);

  right = deep < 0.25 ? !right : right;
}

void Rotator::defaultRotation() {
  angles[0] = (abs(angles[0]) == 360) ? 0 : angles[0];
  angles[1] = (abs(angles[1]) == 360) ? 0 : angles[1];
  angles[2] = (abs(angles[2]) == 360) ? 0 : angles[2];
}

void Rotator::rotate() const {
  ofRotateX((float)angles[0] / 1);
  ofRotateY((float)angles[1] / 1);
  ofRotateZ((float)angles[2] / 1);
}

