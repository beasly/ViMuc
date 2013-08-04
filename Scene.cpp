#include <cmath>
#include <stdlib.h>
#include <stdio.h>

#include "Scene.h"

Scene::Scene() {
  this->nBands = 10;

  fftPlain = new float[128];
  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }
}

void Scene::setup() {
  right = true;

  angleX = 0;
  angleY = 0;
  angleZ = 0;
}

void Scene::update() {
  ofSoundUpdate();

  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    fftPlain[i] = val[i];
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }
}

void Scene::draw() { }

void Scene::keyPressed(int key) { }

void Scene::keyReleased(int key) { }

void Scene::mouseMoved(int x, int y) { }

void Scene::mouseDragged(int x, int y, int button) { }

void Scene::mousePressed(int x, int y, int button) { }

void Scene::mouseReleased(int x, int y, int button) { }

void Scene::windowResized(int w, int h) { }

void Scene::gotMessage(ofMessage msg) { }

void Scene::dragEvent(ofDragInfo dragInfo) { }

float* Scene::getFFTSmooth() const {
  return fftSmooth;
}

float* Scene::getFFTPlain() const {
  return fftPlain;
}

void Scene::setBands(int bands) {
  this->nBands = bands;
}

int Scene::getBands() const {
  return this->nBands;
}

void Scene::modulatedRotation(float deep, float mid, float high) {
  angleX += !(right) ? deep * 5 : -(deep * 4);
  angleY += !(right) ? mid * 7 : -(mid * 9);
  angleZ += !(right) ? high * 10 : -(high * 19);

  right = deep < 0.25 ? !right : right;
}

void Scene::defaultRotation() {
  angleX = (abs(angleX) == 360) ? 0 : angleX;
  angleY = (abs(angleY) == 360) ? 0 : angleY;
  angleZ = (abs(angleZ) == 360) ? 0 : angleZ;

  ofRotateX((float)angleX / 1);
  ofRotateY((float)angleY / 1);
  ofRotateZ((float)angleZ / 1);
}

