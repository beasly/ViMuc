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
  this->nBands = 10;

  fftPlain = new float[128];
  fftSmooth = new float[128];
  fill_n(fftSmooth, sizeof(fftSmooth), 0);
  fill_n(fftPlain, sizeof(fftSmooth), 0);

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
