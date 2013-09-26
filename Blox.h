#pragma once

#include "ofMain.h"
#include "Scene.h"

#define BOX_WIDTH (45)

class Blox : public Scene {
  public:
    Blox();

    void draw();
    void setup();
    void keyPressed(int key);

  private:
    void createTexture();
    void drawCoords(int x, int y, int z);

    ofEasyCam cam;
    int dist;
    ofTexture tex;
    unsigned char *colorPixels;
    vector<float *> modu_history;
};
