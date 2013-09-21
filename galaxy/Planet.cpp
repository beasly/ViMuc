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
  } else{
    return false;
  }
}


void Planet::setPosition(ofVec3f position) {
  this->position = position;
}

void Planet::addRotationAngle() {
  rotationAngle += rotationSpeed*0.25;
  if (rotationAngle > 360) {
    rotationAngle -= 360;
  }
}

void Planet::setPositionOfSun(ofVec3f position) {
  positionOfSun = position;
}

float Planet::getRotationAngle() {
  return rotationAngle;
}

int Planet::getGalaxyIndex() {
  return galaxyIndex;
}

int Planet::getPlanetIndex() {
  return planetIndex;
}

ofVec3f Planet::getPositionOfSun() {
  return positionOfSun;
}

void Planet::setPlanetIndex(int planetIndex) {
  this->planetIndex = planetIndex;
}

Planet::Planet() {
}

ofVec3f Planet::getSpeed() {
  return speed;
}

int Planet::getRadius() {
  return radius;
}

ofVec3f Planet::getPosition() {
  return position;
}

void Planet::setGalaxyIndex(int galaxyIndex) {
  this->galaxyIndex = galaxyIndex;
}

void Planet::setRotationAngle(float rotationAngle) {
  this->rotationAngle = rotationAngle;
}

void Planet::setRotationSpeed(float rotationSpeed) {
  this->rotationSpeed = rotationSpeed;
}

void Planet::setMovable(bool movable) {
  this->movable = movable;
}