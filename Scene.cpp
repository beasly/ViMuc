#include <stdlib.h>
#include <stdio.h>

#include "Scene.h"
#include "Rotator.h"

Scene::Scene() {
  this->nBands = 10;

  fftPlain = new float[128];
  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }

  Rotator * rotator = new Rotator();
}

void Scene::setup() {}

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
