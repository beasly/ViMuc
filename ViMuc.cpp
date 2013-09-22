#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "ViMuc.h"
#include "Scene.h"
#include "Blox.h"
#include "Galaxy.h"

void ViMuc::setup() {
  ofSetVerticalSync(true);
  glEnable(GL_DEPTH_TEST);
  ofEnableSmoothing();

//  scene = new Blox();
  scene = new Galaxy();

  dist = 800;
  cam.setDistance(dist);
  cam.enableMouseInput();

  srand(time(NULL));

  test.loadSound("skank.mp3");
  test.setVolume(0.75f);

  scene->setup();
}

void ViMuc::update() {
  scene->update();
}

void ViMuc::draw() {
  cam.begin();

  scene->draw();

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
    case 'o':
      dist += 10;
      cam.setDistance(dist);
      break;
    case 'l':
      dist -= 10;
      cam.setDistance(dist);
      break;
  }
  scene->keyPressed(key);
}

void ViMuc::keyReleased(int key) {
  scene->keyReleased(key);
}

void ViMuc::mouseMoved(int x, int y) {
  scene->mouseMoved(x, y);
}

void ViMuc::mouseDragged(int x, int y, int button) {
  scene->mouseDragged(x, y, button);
}

void ViMuc::mousePressed(int x, int y, int button) {
  scene->mousePressed(x, y, button);
}

void ViMuc::mouseReleased(int x, int y, int button) {
  scene->mouseReleased(x, y, button);
}

void ViMuc::windowResized(int w, int h) {
  scene->windowResized(w, h);
}

void ViMuc::gotMessage(ofMessage msg) {
  scene->gotMessage(msg);
}

void ViMuc::dragEvent(ofDragInfo dragInfo) {
  scene->dragEvent(dragInfo);
}
