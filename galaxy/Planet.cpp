#include "Planet.h"


void Planet::setRadius(int radius) {
  this->radius = radius;
}

void Planet::setSpeed(ofVec3f speed) {
  this->speed = speed;
}

bool Planet::isMovable() {
  return movable;
}

bool Planet::operator !=(Planet otherPlanet) const {
  if (speed.x != otherPlanet.getSpeed().x || speed.y != otherPlanet.getSpeed().y || speed.z
     != otherPlanet.getSpeed().z) {
    return true;
  } else if (position.x != otherPlanet.getPosition().x || position.y != otherPlanet.getPosition().y ||
    position.z != otherPlanet.getPosition().z) {
    return true;
  } else if (radius != otherPlanet.getRadius()) {
    return true;
  } else if (distanceToSun != otherPlanet.getDistanceToSun()) {
    return true;
  }else{
    return false;
  }
}

int Planet::getDistanceToSun() {
  return distanceToSun;
}

void Planet::setPosition(ofVec3f position) {
  this->position = position;
}

void Planet::setPositionOfSun(ofVec3f position) {
  positionOfSun = position;
}

ofVec3f Planet::getPositionOfSun() {
  return positionOfSun;
}

Planet::Planet() {
}

ofVec3f Planet::getSpeed() {
  return speed;
}

int Planet::getRadius() {
  return radius;
}

void Planet::setDistanceToSun(int distance) {
  distanceToSun = distance;
}

ofVec3f Planet::getPosition() {
  return position;
}

void Planet::setMovable(bool movable) {
  this->movable = movable;
}