#pragma once

#include "ofMain.h"
#include "Scene.h"

class Blox : public Scene {
  public:
    Blox();

    void draw();

  private:
    ofTexture tex;
    unsigned char *colorPixels;
};
