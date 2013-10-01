#include "Planet.h"


void Planet::setRadius(int radius) {
  this->radius = radius;
}

void Planet::setSpeed(ofVec3f speed) {
  this->speed = speed;
}

float Planet::getRadiusOfOrbit() {
  return radiusOfOrbit;
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
  } else {
    return false;
  }
}

void Planet::setPosition(ofVec3f position) {
  this->position = position;
}

void Planet::addRotationAngle(float modu) {
  rotationAngle += rotationSpeed * modu;
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

void Planet::setTexture(ofImage *texture) {
  tex = texture;
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

ofVec3f Planet::getPosition() {
  return position;
}

void Planet::update(float modu) {
  if (isMovable()) {
    addRotationAngle(modu);
  }
}

void Planet::calculateRadiusOfOrbit() {
  radiusOfOrbit = sqrt(pow(position.x, 2) + pow(position.z, 2));
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

void Planet::draw() {
  tex->bind();
  ofSphere(position.x, position.y, position.z, radius);
  tex->unbind();
}