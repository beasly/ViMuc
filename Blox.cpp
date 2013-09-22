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
  setBands(10);
  ofEnableNormalizedTexCoords();
}

void Blox::draw() {
  /** Initialiez a function pointer */
  void (*rota)(float*, bool);
  /** Assign the modulate function to the pointer */
  rota = &rotate;

  float *fftSmoothed = getFFTSmooth();

  float *vals = new float[3];

  vals[0] = fftSmoothed[0];
  vals[1] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) / 2];
  vals[2] = fftSmoothed[sizeof(fftSmoothed) / sizeof(*fftSmoothed) - 1];

  /** Pass the modu function pointer to the customModulatedRotation method */
  rotator.customModulatedRotation(rota, vals);
  rotator.rotate();

  float width = (float) 45;
  ofTranslate(-(getBands() * width) / 2, 0, 0);

  for (int i = 0; i < getBands(); i++) {
    float modu = 2 * fftSmoothed[i] * pow((i + 1.0), 6/4);

  colorPixels = (unsigned char*) malloc(sizeof(*colorPixels) *
          (pow(width, 2) * (modu + 1) * 3 + 3));

    tex.allocate(width, modu * width, GL_RGB);
    for (int i = 1; i <= width; i++) {
      for (int j = 1; j <= width * modu; j++) {
        *(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3) =
          (unsigned char) (i * i);
        *(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3 + 1) =
          (unsigned char) (0);
        *(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3 + 2) =
          (unsigned char) (0);
      }
    }
    //for (int i = 1; i <= width; i++) {
      //for (int j = 1; j <= width * modu; j++) {
        //*(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3) =
          //(unsigned char) (0);
        //*(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3 + 1) =
          //(unsigned char) (0);
        //*(colorPixels + ((j - 1) * (int) width + (i - 1)) * 3 + 2) =
          //(unsigned char) (tan(j * i));
      //}
    //}
    //for (int i = 0; i < width; i++) {
      //for (int j = 0; j < width * modu; j++) {
        //*(colorPixels + (j * (int) width + i) * 3) =
          //(unsigned char) (pow(i, j));
        //*(colorPixels + (j * (int) width + i) * 3 + 1) =
          //(unsigned char) (pow(j, j));
        //*(colorPixels + (j * (int) width + i) * 3 + 2) =
          //(unsigned char) (pow(i, i));
      //}
    //}
    //for (int i = 0; i < width; i++) {
      //for (int j = 0; j < width * modu; j++) {
        //*(colorPixels + (j * (int) width + i) * 3) =
          //(unsigned char) ((j + 1) * (i + 1));
        //*(colorPixels + (j * (int) width + i) * 3 + 1) =
          //(unsigned char) ((j + 2) * (i + 2));
        //*(colorPixels + (j * (int) width + i) * 3 + 2) =
          //(unsigned char) ((j + 3) * (i + 3));
      //}
    //}
    //for (int i = 0; i < width; i++) {
      //random_grey = (i % 3 == 0) ? rand() % 255 : random_grey;
      //for (int j = 0; j < width * modu; j++) {
        //*(colorPixels + (j * (int) width + i) * 3) =
          //(unsigned char) random_grey;
        //*(colorPixels + (j * (int) width + i) * 3 + 1) =
          //(unsigned char) random_grey;
        //*(colorPixels + (j * (int) width + i) * 3 + 2) =
          //(unsigned char) random_grey;
      //}
    //}

    tex.loadData(colorPixels, width, modu * width, GL_RGB);

    ofTranslate(50, 0, 0);

    ofPushMatrix();

    ofScale(0.6, modu, 1);
    tex.bind();
    ofBox(width);
    tex.unbind();

    ofPopMatrix();

    free((void *) colorPixels);
  }
}
