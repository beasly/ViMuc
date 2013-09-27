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
    void mouseMoved(int x, int y);

  private:
    void createTexture();
    void drawCoords(int x, int y, int z) const;

    ofEasyCam cam;
    int dist;
    ofTexture tex;
    unsigned char *colorPixels;
    vector<float *> modu_history;

    ofLight pointLight;
    ofMaterial material;
};
