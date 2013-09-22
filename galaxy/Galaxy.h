#ifndef __Galaxy_H_
#define __Galaxy_H_
#define sunRadius (40)

#include <iostream>
#include <vector>
#include "Planet.h"
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
//  ofxSkyBox skyBox;

};


#endif //__Galaxy_H_
