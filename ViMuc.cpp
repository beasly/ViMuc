#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "ViMuc.h"

void ViMuc::setup() {
  ofSetVerticalSync(true);
  glEnable(GL_DEPTH_TEST);
  ofEnableSmoothing();

  cam.setDistance(600);
  cam.enableMouseInput();

  right = true;

  angleX = 0;
  angleY = 0;
  angleZ = 0;

  srand(time(NULL));

  test.loadSound("begin.mp3");
  test.setVolume(0.75f);

  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }

  nBands = 10;
}

void ViMuc::update() {
  ofBackground(0, 0, 50);
  ofSoundUpdate();

  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }
}

void ViMuc::draw() {
  cam.begin();
  //ofRotateX(ofRadToDeg(.5));

  defaultRotation();
  modulatedRotation(fftSmooth[1], fftSmooth[5], fftSmooth[8]);

  float width = (float)45;
  ofTranslate(-(nBands * width) / 2, 0, 0);

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

  cam.end();
}

void ViMuc::modulatedRotation(float deep, float mid, float high) {
  angleX += !(right) ? deep * 5 : -(deep * 5);
  angleY += !(right) ? mid * 7 : -(mid * 7);
  angleZ += !(right) ? high * 10 : -(high * 10);
  right = deep < 0.1 ? !right : right;
}

void ViMuc::defaultRotation() {
  angleX = (abs(angleX) == 360) ? 0 : angleX;
  angleY = (abs(angleY) == 360) ? 0 : angleY;
  angleZ = (abs(angleZ) == 360) ? 0 : angleZ;

  ofRotateX((float)angleX / 1);
  ofRotateY((float)angleY / 1);
  ofRotateZ((float)angleZ / 1);
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
