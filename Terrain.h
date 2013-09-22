#pragma once

#include "ofMain.h"
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
#include "Scene.h"


using namespace std;

class Terrain : public Scene{


private:
  typedef Scene super;
  
  
  int lowest_height;
  int highest_height;
  int move_row;
  int move_count;
  int frames;
  
  
  
  //int nBands;
  //float *fftSmooth;
  ofVboMesh gridMesh;
  ofLight light;
  
  int framecounter;



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

 float highest;
 float lowest;
  
  ofColor color_array[200];
  void update_colors();

public:

  // ofMesh gridMesh;
  Terrain();
  //void update();
  void draw();
  void update();
  void setBands(int bands);
  void gridSurfaceSetup();
  void set_sinus_heights();
  void debug_vertex();

  void set_colors();
  void getheight();

  void module_terrain();

   void debug_fft();
   void show_fft();

  ofColor HSL2RGB(double h, double s, double l);
  void HSLtoRGB_Subfunction(unsigned int& c, const float& temp1, const float& temp2, const float& temp3);
  void set_vertical_color();
  
  vector<ofColor> rainbow_vector;
  void make_rainbow();
  
  void move_peeks();


};
