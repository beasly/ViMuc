#include <stdlib.h>

#include "ofMain.h"
#include "Blox.h"

Blox::Blox() {
  this->nBands = 10;
  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }
}

void Blox::update() {
  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    cout << sizeof(fftSmooth) << " " << i << endl;
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }
}

void Blox::draw() {
  float width = (float)45;
  ofTranslate(-(nBands * width) / 2, 0, 0);

  for (int i = 0; i < nBands; i++) {
    float modu = 2 * fftSmooth[i] * pow((i + 1.0), 6/4);

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

void Blox::setBands(int bands) {
  this->nBands = bands;
}
