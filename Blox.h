#pragma once

#include "ofMain.h"
#include "Scene.h"

class Blox : public Scene {
  public:
    Blox();

    void draw();
    void setup();
    void keyPressed(int key);

  private:
    ofEasyCam cam;
    int dist;
    ofTexture tex;
    unsigned char *colorPixels;
};
