#ifndef __Planet_H_
#define __Planet_H_

#include <iostream>
#include "ofBaseTypes.h"
#include "ofBaseApp.h"
#include "ofVec3f.h"
#include "ofMain.h"

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
  void addRotationAngle(float modu);
  float getRadiusOfOrbit();
  void calculateRadiusOfOrbit();
  void setTexture(ofImage *texture);
  void update(float modu);
  void draw();

  private:
  ofVec3f speed;
  ofVec3f position;
  int radius;
  ofVec3f positionOfSun;
  float radiusOfOrbit;
  bool movable;
  float rotationAngle;
  float rotationSpeed;
  ofImage *tex;
};


#endif //__Planet_H_
