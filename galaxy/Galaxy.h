//
// Created by kevingoy on 19.06.13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Galaxy_H_
#define __Galaxy_H_

#include <iostream>
#include <vector>
#include "ofBaseApp.h"
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
  void updatePhysics(time_t animationTime);
  void updateForces(double deltaTime);
  void updatePosition(double deltaTime);

  private:
  int planetAmount;
  vector<Planet> galaxyList;
  time_t lastPhyicsAnimationTime;
};


#endif //__Galaxy_H_
