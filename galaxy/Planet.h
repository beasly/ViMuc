#ifndef __Particle_H_
#define __Particle_H_

#include <iostream>
#include "ofVec3f.h"

class Planet {
  public:
  Planet();
  ofVec3f getSpeed();
  void setSpeed(ofVec3f speed);
  ofVec3f getPosition();
  void setPosition(ofVec3f position);
  ofVec3f getPositionOfSun();
  void setPositionOfSun(ofVec3f position);
  bool isMovable();
  int getRadius();
  void setRadius(int radius);
  bool operator!=(Planet otherPlanet)const;
  void setMovable(bool movable);
  void setRotationSpeed(float rotationSpeed);
  float getRotationAngle();
  void setRotationAngle(float rotationAngle);
  void addRotationAngle();
  void setPlanetIndex(int planetIndex);
  int getPlanetIndex();
  void setGalaxyIndex(int galaxyIndex);
  int getGalaxyIndex();

  private:
  ofVec3f speed;
  ofVec3f position;
  int radius;
  ofVec3f positionOfSun;
  bool movable;
  float rotationAngle;
  float rotationSpeed;
  int planetIndex;
  int galaxyIndex;
};


#endif //__Particle_H_
