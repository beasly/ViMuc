#ifndef __Particle_H_
#define __Particle_H_

#include <iostream>
#include "ofVec3f.h"

class Planet {
  public:
  Planet();
  ofVec3f getSpeed();
  void setSpeed(ofVec3f speed);
  int getDistanceToSun();
  void setDistanceToSun(int distance);
  ofVec3f getPosition();
  void setPosition(ofVec3f position);
  ofVec3f getPositionOfSun();
  void setPositionOfSun(ofVec3f position);
  bool isMovable();
  int getRadius();
  void setRadius(int radius);
  bool operator!=(Planet otherPlanet)const;
  void setMovable(bool movable);


  private:
  ofVec3f speed;
  ofVec3f position;
  int radius;
  int distanceToSun;
  ofVec3f positionOfSun;
  bool movable;


};


#endif //__Particle_H_
