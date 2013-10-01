#pragma once
#include "ofMain.h"
#include <algorithm>
#include <math.h>
#include "Scene.h"

#define _USE_MATH_DEFINES

class Terrain : public Scene {

private:
  typedef Scene super;
  
  ofEasyCam cam;
  ofVboMesh gridMesh;
  ofColor begin;
  ofColor end;
  ofColor colorPalette[11];
  ofColor color_array[200];
  
  int frames;
  int meshResolution;
  int dist; 
  int indexLow;
  int indexHigh;
  bool drawMode; 
  vector<int> peeks;
  
  void setColors(ofColor start, ofColor end);
  void gridSurfaceSetup();
  void updateHeights();
  void setPeeks();
  void switchLowerColor(int i);
  void switchUpperColor(int i);  
  void movePeeks();
  void setHorizontalColor();

public:
  Terrain();
  void keyPressed(int key);
  void update();
  void setup();
  void draw();

};
