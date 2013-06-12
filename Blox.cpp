#include <stdlib.h>

#include "ofMain.h"
#include "Blox.h"


Blox::Blox(ofSoundPlayer& soundPlayer, int nBands) {
  this->nBands = nBands;
}

void Blox::update() {
  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }
}

void Blox::draw() {
  cout << "draw" << endl;
  float width = (float)45;
  ofTranslate(-(nBands * width) / 2, 0, 0);
  cout << "3" << endl;

  for (int i = 0; i < nBands; i++) {
    float modu = 2 * fftSmooth[i] * pow((i + 1), 6/4);

    ofTranslate(50, 0, 0);

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

