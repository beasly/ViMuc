#include <stdlib.h>
#include <stdio.h>

#include "Blox.h"

Blox::Blox() {}

void Blox::draw() {
  float width = (float)45;
  ofTranslate(-(getBands() * width) / 2, 0, 0);

  for (int i = 0; i < getBands(); i++) {
    float modu = 2 * getFFTSmooth()[i] * pow((i + 1.0), 6/4);

    ofTranslate(50, 0, 0);
    ofSphere(100 * modu);

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
