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
  dist = 800;
  cam.setDistance(dist);
  cam.enableMouseInput();
}

void Blox::draw() {
  cam.begin();
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
       (int) (width * width + width) * 3 + 2);

    for (int i = 0; i <= width; i++) {
      for (int j = 0; j <= width; j++) {
        if (i == 0 && j == 0) {
          //cout << endl << endl << endl;
        }
        int iterator = (j * (int) width + i) * 3;

        int col_color = (i / 2) % (int) width / 2;
        int row_color = (j / 2) % (int) width / 2;

        //cout << i / 2 << "%" << width / 2 << " = " << col_color
          //<< " " << j / 2 << "%" << width / 2 << " = " << row_color << endl;

        *(colorPixels + iterator) = (unsigned char) (i * j);
        *(colorPixels + iterator + 1) = (unsigned char) (0);
        *(colorPixels + iterator + 2) = (unsigned char) (0);
      }
    }

    tex.allocate(width, width, GL_RGB);
    tex.loadData(colorPixels, width, width, GL_RGB);

    ofTranslate(50, 0, 0);

    ofPushMatrix();

    ofScale(0.6, modu, 1);
    tex.bind();
    ofBox(width);
    tex.unbind();

    ofPopMatrix();

  }
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
