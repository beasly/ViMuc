#include <cmath>

#include "ViMuc.h"

void ViMuc::setup() {
  ofSetVerticalSync(true);
  glEnable(GL_DEPTH_TEST);
  ofEnableSmoothing();

  cam.setDistance(600);
  cam.enableMouseInput();

  test.loadSound("stout.mp3");
  test.setVolume(0.75f);

  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }

  nBands = 8;
}

void ViMuc::update() {
  ofBackground(0, 0, 255);
  ofSoundUpdate();

  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }
}

void ViMuc::draw() {

  cam.begin();
  ofRotateX(ofRadToDeg(.5));

  float width = (float)90;
  ofTranslate(-(nBands * width + 180) / 2, 0, 0);

  for (int i = 0; i < nBands; i++) {
    float modu = fftSmooth[i] * pow((i + 1), 6/4);

    ofTranslate(100, 0, 0);

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

  cam.end();
}

void ViMuc::keyPressed(int key) {
  switch(key) {
    case 'q':
      test.play();
      break;
    case 'w':
      test.stop();
      break;
  }

}

void ViMuc::keyReleased(int key) {

}

void ViMuc::mouseMoved(int x, int y) {

}

void ViMuc::mouseDragged(int x, int y, int button) {

}

void ViMuc::mousePressed(int x, int y, int button) {

}

void ViMuc::mouseReleased(int x, int y, int button) {

}

void ViMuc::windowResized(int w, int h) {

}

void ViMuc::gotMessage(ofMessage msg) {

}

void ViMuc::dragEvent(ofDragInfo dragInfo) {

}
