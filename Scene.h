#pragma once

#include "ofMain.h"
#include "Rotator.h"

/**
 * The Scene class is the skeleton of every actual scene in the ViMuc
 * application. It provides the OF methods to be overwritten by the individual
 * scenes. Furthermore the scene class provides it's children the FFT data
 * in two arrays. One array has the plain fft data, the other has the smoothed
 * fft values.
 */
class Scene : public ofBaseApp {
  public:
    /**
     * Initializes the scene with a default of 10 bands.
     */
    Scene();

    Rotator rotator;

    /**
     * The setup method is meant to resemble the OF default setup method.
     * The OF default method delegates to this setup method.
     */
    void setup();

    /**
     * The update method is meant to resemble the OF default update method.
     * The OF default method delegates to this update method.
     */
    void update();

    /**
     * The draw method is meant to resemble the OF default draw method.
     * The OF default method delegates to this draw method.
     */
    void draw();

    /**
     * The draw method is meant to resemble the OF default draw method.
     * The OF default method delegates to this draw method.
     */
    void keyPressed(int key);

    /**
     * The draw method is meant to resemble the OF default draw method.
     * The OF default method delegates to this draw method.
     */
    void keyReleased(int key);

    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    float* getFFTSmooth() const;
    float* getFFTPlain() const;
    void setBands(int bands);
    void setFilter(float filter);
    int getBands() const;

  private:
    int nBands;
    float filter;

    float *fftSmooth;
    float *fftPlain;
};
