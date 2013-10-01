#include <stdlib.h>

#include <cmath>

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
  setBands(10);
  dist = 800;

  _texturize = &Blox::cosTex;
  r = true;
  g = true;
  b = true;

  cam.setDistance(dist);
  cam.enableMouseInput();

  pointLight.setDiffuseColor(ofColor(0.f, 255.f, 0.f));
  pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));

  material.setShininess(64);
  material.setSpecularColor(ofColor(255.f, 255.f, 255.f));

  createTexture();
}

void Blox::draw() {
  ofEnableNormalizedTexCoords();
  glEnable(GL_DEPTH_TEST);

  /** Initializes a function pointer */
  void (*rota)(float*, bool);
  /** Assign the modulate function to the pointer */
  rota = &rotate;

  int margin = BOX_WIDTH * 75 / 100;
  int rows = 10;

  float *fftSmoothed = getFFTSmooth();
  float *vals = new float[3];

  vals[0] = fftSmoothed[0];
  vals[1] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) / 2];
  vals[2] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) - 1];

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
  }
  material.end();

  cam.end();

  ofDisableNormalizedTexCoords();
  glDisable(GL_DEPTH_TEST);
}

void Blox::keyPressed(int key) {
  switch (key) {
    case 'o':
      dist += (dist >= 2500) ? 0 : 10;
      cam.setDistance(dist);
      break;
    case 'l':
      dist -= 10;
      cam.setDistance(dist);
      break;
    case 'z':
      _texturize = &Blox::logTex;
      createTexture();
      break;
    case 'x':
      _texturize = &Blox::sinTex;
      createTexture();
      break;
    case 'c':
      _texturize = &Blox::cosTex;
      createTexture();
      break;
    case 'v':
      _texturize = &Blox::quadTex;
      createTexture();
      break;
    case 'n':
      _texturize = &Blox::expTex;
      createTexture();
      break;
    case 'm':
      _texturize = &Blox::sqrtTex;
      createTexture();
      break;
    case 'r':
      r = !r;
      createTexture();
      break;
    case 'g':
      g = !g;
      createTexture();
      break;
    case 'b':
      b = !b;
      createTexture();
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
        int colColor = pow((float) (i - BOX_WIDTH / 2), 2);
        int rowColor = pow((float) (j - BOX_WIDTH / 2), 2);
        int bigger = colColor > rowColor ? colColor : rowColor;

        *(colorPixels + position) =
          (unsigned char) (r ? (this->*_texturize)(bigger) : 0);
        *(colorPixels + position + 1) =
          (unsigned char) (g ? (this->*_texturize)(bigger) : 0);
        *(colorPixels + position + 2) =
          (unsigned char) (b ? (this->*_texturize)(bigger) : 0);
      }
    }

    tex.allocate(BOX_WIDTH, BOX_WIDTH, GL_RGB);
    tex.loadData(colorPixels, BOX_WIDTH, BOX_WIDTH, GL_RGB);
}

float Blox::logTex(int n) {
  return log(n) * BOX_WIDTH;
}

float Blox::sinTex(int n) {
  return sin(n) * BOX_WIDTH;
}

float Blox::cosTex(int n) {
  return acosh(n) * BOX_WIDTH;
}

float Blox::quadTex(int n) {
  return n * n;
}

float Blox::expTex(int n) {
  return pow(2.0f, n) / BOX_WIDTH;
}

float Blox::sqrtTex(int n) {
  return sqrt(n) * 10;
}
