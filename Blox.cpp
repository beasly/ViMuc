#include <stdlib.h>
#include <stdio.h>

#include <vector>

#include "Blox.h"

Blox::Blox() {}

/**
 * This is the function I want to use as modulator for the rotation of my
 * scene. It recieves the vals array of 3 values (deep, mid and high) and the
 * direction.
 * It modifies these values directly, because the context in wich it is de-
 * referenced and called is a method of the Rotator class.
 * This behaviour is dangerous, so don't do stupid things with it.
 */
void rotate(float* vals, bool right) {
  vals[0] += !(right) ? vals[0] * 1 : -(vals[0] * 1);
  vals[1] += !(right) ? vals[1] * 2 : -(vals[1] * 2);
  vals[2] += !(right) ? vals[2] * 4 : -(vals[2] * 4);

  right = vals[0] < 0.25 ? !right : right;
}

void Blox::setup() {
  ofEnableNormalizedTexCoords();
  glEnable(GL_DEPTH_TEST);
  ofSetSmoothLighting(true);

  setBands(10);
  dist = 800;

  cam.setDistance(dist);
  cam.enableMouseInput();

  pointLight.setDiffuseColor(ofColor(0.f, 255.f, 0.f));
  pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
  //pointLight.setPosition(0, 0, 300);

  material.setShininess(64);
  material.setSpecularColor(ofColor(255.f, 255.f, 255.f));

  createTexture();
}

void Blox::draw() {
  /** Initializes a function pointer */
  void (*rota)(float*, bool);
  /** Assign the modulate function to the pointer */
  rota = &rotate;

  int margin = BOX_WIDTH * 75 / 100;
  int rows = 10;

  //drawCoords(0, 0, 0);

  float *fftSmoothed = getFFTSmooth();
  float *vals = new float[3];

  /** DEBUG: CHANGE ME BEFORE COMMIT */
  for (int i = 0; i < getBands(); i++) {
    printf("%2.8f ", fftSmoothed[i]);
  }
  puts("\n");

  vals[0] = fftSmoothed[0];
  vals[1] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) / 2];
  vals[2] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) - 1];

  modu_history.push_back(fftSmoothed);

  ofEnableLighting();
  pointLight.enable();

  cam.begin();

  /** Draw sky sphere */
  ofPushMatrix();
    ofNoFill();
    ofSphere(2500);
    ofFill();
  ofPopMatrix();

  /* Pass the modu function pointer to the customModulatedRotation method */
  rotator.customModulatedRotation(rota, vals);
  rotator.rotate();

  material.begin();
  ofTranslate(-((getBands() * margin + margin) / 2), 0,
      -(rows * margin + margin));
  for (int j = 0; j < rows; j++) {
    ofPushMatrix();
    for (int i = 0; i < getBands(); i++) {
      float modu = 2 * fftSmoothed[i] * pow((i + 1.0), 6 / 4);

      ofTranslate(margin, 0, 0);
      ofPushMatrix();
        ofScale(0.6, modu, 1);
        tex.bind();
        ofBox(BOX_WIDTH);
        tex.unbind();
      ofPopMatrix();
    }
    ofPopMatrix();
    ofTranslate(0, 0, margin * 2);
    //ofTranslate( 0, -(getBands() * (BOX_WIDTH)), 0);
  }
  material.end();

  ofDisableLighting();

  cam.end();

}

void Blox::keyPressed(int key) {
  switch(key) {
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

void Blox::drawCoords(int x, int y, int z) const {
  ofPushMatrix();
    ofTranslate(x, y, z);

    ofPushMatrix();
      ofSetColor(255, 0, 0);
      ofScale(10000, 1, 1);
      ofBox(1);
    ofPopMatrix();

    ofPushMatrix();
      ofSetColor(0, 255, 0);
      ofScale(1, 10000, 1);
      ofBox(1);
    ofPopMatrix();

    ofPushMatrix();
      ofSetColor(0, 0, 255);
      ofScale(1, 1, 10000);
      ofBox(1);
    ofPopMatrix();

  ofPopMatrix();
}

void Blox::createTexture() {
    colorPixels = (unsigned char*) malloc(sizeof(*colorPixels) *
       (int) (BOX_WIDTH * BOX_WIDTH + BOX_WIDTH) * 3 + 2);

    for (int i = 0; i < BOX_WIDTH; i++) {
      for (int j = 0; j < BOX_WIDTH; j++) {
        int position = (j * (int) BOX_WIDTH + i) * 3;
        int colColor = pow(i - BOX_WIDTH / 2, 2);
        int rowColor = pow(j - BOX_WIDTH / 2, 2);
        int bigger = colColor > rowColor ? colColor : rowColor;

        *(colorPixels + position) = (unsigned char) (0);
        *(colorPixels + position + 1) = (unsigned char) (0);
        *(colorPixels + position + 2) = (unsigned char) (log(bigger) * 100);
      }
    }

    tex.allocate(BOX_WIDTH, BOX_WIDTH, GL_RGB);
    tex.loadData(colorPixels, BOX_WIDTH, BOX_WIDTH, GL_RGB);
}

void Blox::mouseMoved(int x, int y) {
  //pointLight.setPosition(x, y, 900);
}
