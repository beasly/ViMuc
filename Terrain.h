#pragma once

#include "ofMain.h"
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

class Terrain {


private:
  int nBands;
  float *fftSmooth;
  ofVboMesh gridMesh;
  ofLight light;



  float modu;

  void test();
  int gridRows;
  int gridColumns;
  vector<vector<vector<float> > > gridPoints;
  int meshResolution;
  vector<int> peeks;
  vector<int> testvector;
  void setPeeks();
  void test_heights();
  void setBandHeight(float modu, float range);



public:

  // ofMesh gridMesh;
  Terrain();
  void update();
  void draw();
  void setBands(int bands);
  void gridSurfaceSetup();
  void set_sinus_heights();
  void debug_vertex();

  void set_colors();
  void getheight();




};
