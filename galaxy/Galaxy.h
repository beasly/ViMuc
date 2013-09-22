#ifndef __Galaxy_H_
#define __Galaxy_H_
#define sunRadius (50)

#include <iostream>
#include <vector>
#include "Planet.h"
#include "ofxSkyBox.h"
#include "Scene.h"

using namespace std;

class Galaxy : public Scene {
  public:
  Galaxy();

  void update();

  void draw();

  void setup();

  int irand(int min, int max) const;

  void keyPressed(int key);


  private:
  int planetAmount;
  vector<Planet *> galaxyList;
  bool playing;
  ofxSkyBox skyBox;

};


#endif //__Galaxy_H_
