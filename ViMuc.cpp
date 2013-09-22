#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "ViMuc.h"
#include "Scene.h"
#include "Blox.h"

void ViMuc::setup() {
  ofSetVerticalSync(true);
  glEnable(GL_DEPTH_TEST);
  ofEnableSmoothing();

  scene = new Blox();

  dist = 600;
  cam.setDistance(dist);
  cam.enableMouseInput();

  srand(time(NULL));

  test.loadSound("begin.mp3");
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
}

void ViMuc::keyReleased(int key) { }

void ViMuc::mouseMoved(int x, int y) { }

void ViMuc::mouseDragged(int x, int y, int button) { }

void ViMuc::mousePressed(int x, int y, int button) { }

void ViMuc::mouseReleased(int x, int y, int button) { }

void ViMuc::windowResized(int w, int h) { }

void ViMuc::gotMessage(ofMessage msg) { }

void ViMuc::dragEvent(ofDragInfo dragInfo) { }
