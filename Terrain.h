#pragma once

#include "ofMain.h"
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
#include "Scene.h"


class Terrain : public Scene{


private:
  typedef Scene super;
  
  //Sauber
  

  
  //Wichte Attribute
  
  ofEasyCam cam; // camera
  int dist; // camera distance
  bool drawMode; // grid or draw
  int speed; // speed
 
  
  
  
  
  
  int lowest_height;
  int highest_height;
  int move_row;
  int move_count;
  int frames;
  
  
  
  //int nBands;
  //float *fftSmooth;
  ofVboMesh gridMesh;
  ofLight light;
  ofLight light_left;
  
  int framecounter;



  float modu;

  void updateHeights();
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

  Terrain();
  
  //Überschriebene Methoden
  void keyPressed(int key);
  void update();
  void setup();
  void draw();

  
  
  
  
  
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
  void smoothTerrain();
  
  ofVec3f get_bezier(float t, ofVec3f point_a, ofVec3f point_b, ofVec3f point_c, ofVec3f point_d);
  void set_horizontal_color();
  vector<vector<float> > smoothTerrain(int passes, vector<vector<float> > height_data);
  
  void startSmoothing();
  vector<vector<float> > makeHeightData(); 
  void updateHeightData(vector<vector<float> > height_data);
  vector<vector<float> > initializeHeightMap(int meshResolution);
  void test_smooth();
  float cat_mull(float point1_y, float point2_y, float point3_y, float point4_y, float time);

};
