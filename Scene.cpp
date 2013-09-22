#include <stdlib.h>
#include <stdio.h>

#include "Scene.h"
#include "Rotator.h"

/**
 * The Scene class is the skeleton of every actual scene in the ViMuc
 * application. It provides the OF methods to be overwritten by the individual
 * scenes. Furthermore the scene class provides it's children the FFT data
 * in two arrays. One array has the plain fft data, the other has the smoothed
 * fft values.
 */
Scene::Scene() {
  
  nBands = 10;
  filter = 1;
  smoothingFactor = 0.97f;
  
  fftPlain = new float[128];
  fftSmooth = new float[128];
  fill_n(fftSmooth, sizeof(fftSmooth), 0);
  fill_n(fftPlain, sizeof(fftSmooth), 0);

  Rotator * rotator = new Rotator();
}

void Scene::setup() {}

void Scene::update() {
  ofSoundUpdate();

  int filteredNBands = (int) (filter * nBands);

  float *val = ofSoundGetSpectrum(filteredNBands);

  for (int i = 0; i < nBands; i++) {
    fftPlain[i] = val[i];
    fftSmooth[i] *= smoothingFactor;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
    fftSmooth[i] = fftSmooth[i] > 10 ? 0 : fftSmooth[i];
  }
}

void Scene::draw() {}

void Scene::keyPressed(int key) {}

void Scene::keyReleased(int key) {}

void Scene::mouseMoved(int x, int y) {}

void Scene::mouseDragged(int x, int y, int button) {}

void Scene::mousePressed(int x, int y, int button) {}

void Scene::mouseReleased(int x, int y, int button) {}

void Scene::windowResized(int w, int h) {}

void Scene::gotMessage(ofMessage msg) {}

void Scene::dragEvent(ofDragInfo dragInfo) {}

float* Scene::getFFTSmooth() const {
  return fftSmooth;
}

float* Scene::getFFTPlain() const {
  return fftPlain;
}

void Scene::setBands(int _bands) {
  nBands = _bands;
}

void Scene::setFilter(float _filter) {
  filter = _filter;
}

void Scene::setSmoothingFactor(float _smoothingFactor) {
  smoothingFactor = _smoothingFactor;
}

void Scene::setFilter(float filter) {
  this->filter = filter;
}

int Scene::getBands() const {
  return nBands;
}


