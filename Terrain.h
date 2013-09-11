#pragma once

#include "ofMain.h"
#include <algorithm>

class Terrain {
  

private:
  int nBands;
  float *fftSmooth;
 ofVboMesh gridMesh;
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
  

  

};