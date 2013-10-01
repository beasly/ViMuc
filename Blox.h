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
    void drawCoords(int x, int y, int z) const;
    float logTex(int n);
    float sinTex(int n);
    float cosTex(int n);
    float quadTex(int n);
    float expTex(int n);
    float sqrtTex(int n);

    typedef float (Blox::*texturize)(int);
    texturize _texturize;

    ofEasyCam cam;
    int dist;
    ofTexture tex;
    unsigned char *colorPixels;

    /** Texturize flags */
    bool r, g, b;

    ofLight pointLight;
    ofMaterial material;
};
