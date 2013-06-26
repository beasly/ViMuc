#include "Galaxy.h"
#include <sys/timeb.h>
#include "ofSoundPlayer.h"
#include "ofGraphics.h"

Galaxy::Galaxy() {
  setBands(128);
  planetAmount = getBands();
  lastPhyicsAnimationTime = 0;
  rotationDegree = 0;
}


void Galaxy::setup() {
  for (int i = 0; i < planetAmount; i++) {
    Planet planet;
    if (i == 0) {
      planet.setMovable(false);
      planet.setRadius(15);
      ofVec3f position;
      position.set(0, 0, 0);
      planet.setPosition(position);
    } else {
      planet.setMovable(true);
      planet.setRadius(irand(3, 10));
      ofVec3f position;
      position.set(irand(-100, 100),
        irand(-100, 100), irand(-100, 100));
      planet.setPosition(position);
      planet.setPositionOfSun(planets.at(0).getPosition());
      planet.setDistanceToSun(irand(5, 50));
    }
    planets.push_back(planet);
    cout << planets.size() << endl;
  }
}


void Galaxy::update() {
  Scene::update();
  timeb tb;
  ftime(&tb);
  updatePhysics(tb.millitm);
}


void Galaxy::updatePhysics(time_t animationTime) {
  double deltaTime = animationTime - lastPhyicsAnimationTime;
  deltaTime /= 1000;
  if (deltaTime < -9) {
    deltaTime += 10;
  }
  if (deltaTime < 0) {
    deltaTime += 1;
  }
  updateForces(deltaTime);
  updatePosition(deltaTime);
  lastPhyicsAnimationTime = animationTime;
}

void Galaxy::updateForces(double deltaTime) {
  for (size_t i = 0; i < planets.size(); i++) {
    Planet planet = planets[i];
    ofVec3f overallForce;
    for (size_t j = 0; j < planets.size(); j++) {
      Planet otherPlanet = planets[j];
      if (planet != otherPlanet) {
        ofVec3f distanceVector = planet.getPosition() - (otherPlanet.getPosition());
        double distance = distanceVector.length();
        double minimumDistance = otherPlanet.getRadius() + planet.getRadius() + 100;
        if (distance != 0) {
          if (distance < minimumDistance) {
            ofVec3f force = distanceVector.getScaled(-(distance - minimumDistance) * 100. / (distance * distance));
            overallForce + force;
          }
          // calculate the force as reverse proportional to the distance square scaled by the field strength
          ofVec3f force =
            distanceVector.getScaled(-10 * planet.getRadius() * otherPlanet.getRadius() / (distance *
              distance * distance));
          overallForce + force;
        }
      }
    }
    ofVec3f center(planets.at(0).getPosition());
    overallForce + center - planet.getPosition().scale(0.9);
    // acc = forceVektor/mass
    ofVec3f acceleration = overallForce.getScaled(1.0 / planet.getRadius());
    // dV
    ofVec3f deltaSpeed = acceleration.getScaled(deltaTime);
    if (deltaSpeed.length() > 50) {
      deltaSpeed.rescale(50);
    }
    // v += dV
    planet.setSpeed(planet.getSpeed() + deltaSpeed);
    planet.setSpeed(planet.getSpeed().getScaled(0.9));
    planets.at(i) = planet;
  }
}

void Galaxy::updatePosition(double deltaTime) {

  for (size_t i = 0; i < planets.size(); i++) {
    Planet planet = planets[i];
    if (planet.isMovable()) {
      // dX
      ofVec3f deltaPos = planet.getSpeed().getScaled(deltaTime);
      // x += dX
      planet.setPosition(planet.getPosition() + deltaPos);
      if (i != 0) {
        locateToSun(planet);
        rotatePlanet(planet);
      }
//      cout <<"Planet "<< i <<  planet.getPosition() << endl;
      planets.at(i) = planet;
    }
  }
  if (rotationDegree == 360) {
    rotationDegree = 0;
  }
  rotationDegree++;
}

void Galaxy::rotatePlanet(Planet planet) {
  ofRotate(rotationDegree, 1, 1, 1);
}


void Galaxy::locateToSun(Planet planet) {
  if (abs(planet.getPosition().length() - planet.getPositionOfSun().length()) < planet.getDistanceToSun()) {
    planet.getPosition().rescale(planet.getDistanceToSun());
  }
}

void Galaxy::draw() {
  ofBuffer();
  ofSetColor(22, 123, 51);
  for (size_t i = 0; i < planetAmount; i++) {
    Planet planet = planets.at(i);
    ofPushMatrix();
    ofFill();
    ofRotate(2);
    float modu = 2 * getFFTSmooth()[i] * pow((i + 1.0), 6/4);

    if (i == 0) {
      ofSphere(planet.getPosition().x, planet.getPosition().y,
        planet.getPosition().z,
        planet.getRadius());
    } else {
      if (planet.getPosition().x - planet.getPositionOfSun().x > 0) {
        ofTranslate(modu, 0, 0);
      } else {
        ofTranslate(-modu, 0, 0);
      }
      if (planet.getPosition().y - planet.getPositionOfSun().y > 0) {
        ofTranslate(0, modu, 0);
      } else {
        ofTranslate(0, -modu, 0);
      }
      if (planet.getPosition().z - planet.getPositionOfSun().z > 0) {
        ofTranslate(0, 0, modu);
      }else {
        ofTranslate(0, 0, -modu);

      }
      ofSphere(planet.getPosition().x, planet.getPosition().y,
        planet.getPosition().z,
        planet.getRadius());
    }
    modulatedRotation(1, 1, 1);

    cout << planet.getPosition() << planet.getRadius() << endl;
    ofPopMatrix();
  }
}


int Galaxy::irand(int min, int max) const {
  return (int) (((double) rand() / ((double) RAND_MAX + 1.0)) * (max - min + 1) + min);
}

