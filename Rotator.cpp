#include <stdlib.h>

#include "ofMain.h"
#include "Rotator.h"

Rotator::Rotator() {
  float * angles;
  bool right = true;
}

void Rotator::modulatedRotation(float deep, float mid, float high) {
  angles[0] += !(right) ? deep * 5 : -(deep * 4);
  angles[1] += !(right) ? mid * 7 : -(mid * 9);
  angles[2] += !(right) ? high * 10 : -(high * 19);

  right = deep < 0.25 ? !right : right;
}

void Rotator::defaultRotation() {
  angles[0] = (abs(angleX) == 360) ? 0 : angleX;
  angles[1] = (abs(angleY) == 360) ? 0 : angleY;
  angles[2] = (abs(angleZ) == 360) ? 0 : angleZ;

  ofRotateX((float)angleX / 1);
  ofRotateY((float)angleY / 1);
  ofRotateZ((float)angleZ / 1);
}

