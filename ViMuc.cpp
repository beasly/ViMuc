#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "ViMuc.h"
#include "Blox.h"

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

  test.loadSound("1-02 Cabaret.mp3");
  test.setVolume(0.75f);

  blocks.setBands(10);
}

void ViMuc::update() {
  ofBackground(0, 0, 50);
  ofSoundUpdate();

  blocks.update();
}

void ViMuc::draw() {
  cam.begin();

  //defaultRotation();
  //modulatedRotation(fftSmooth[1], fftSmooth[5], fftSmooth[8]);

  blocks.draw();

  cam.end();
}

void ViMuc::modulatedRotation(float deep, float mid, float high) {
  angleX += !(right) ? deep * 5 : -(deep * 4);
  angleY += !(right) ? mid * 7 : -(mid * 9);
  angleZ += !(right) ? high * 10 : -(high * 19);

  right = deep < 0.25 ? !right : right;
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
