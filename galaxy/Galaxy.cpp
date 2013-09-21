#include "Galaxy.h"
#include <sys/timeb.h>
#include "ofSoundPlayer.h"
#include "ofGraphics.h"

Galaxy::Galaxy() {
  Scene::Scene();
  setBands(40);
  planetAmount = getBands();
  for (int i = 0; i < 4; i++) {
    galaxyList.push_back(vector<Planet>());
  }
  lastPhyicsAnimationTime = 0;
}


void Galaxy::setup() {
  for (int i = 0; i < planetAmount + 1; i++) {
    Planet planet;
    if (i < 4) {
      planet.setMovable(false);
      planet.setRadius(15);
      ofVec3f position;
      if (i == 0) {
        position.set(0, 0, 0);
      } //else if (i == 1) {
//        position.set(497, -394, 0);
//      } else if (i == 2) {
//        position.set(-452, 224, 0);
//      } else if (i == 3) {
//        position.set(-200, 200, 0);
//      }
      planet.setPosition(position);
      planet.setGalaxyIndex(i);
      galaxyList[i].push_back(planet);
    } else {
      planet.setMovable(true);
      planet.setRadius(irand(3, 10));
      ofVec3f position;
      planet.setRotationAngle(0);
      planet.setRotationSpeed(irand(1, 6));
      planet.setPlanetIndex(i - 4);
      //sun index
      planet.setGalaxyIndex(0);
      planet.setPositionOfSun(galaxyList[planet.getGalaxyIndex()].at(0).getPosition());
      position.set(irand((int) (planet.getPositionOfSun().x - 400),
        (int) (planet.getPositionOfSun().x + 400)),
        irand((int) (planet.getPositionOfSun().y - 400),
          (int) (planet.getPositionOfSun().y + 400)), irand((int) (planet.getPositionOfSun().z - 400),
          (int) (planet.getPositionOfSun().z + 400)));
      planet.setPosition(position);
      galaxyList[planet.getGalaxyIndex()].push_back(planet);
    }
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
//  updateForces(deltaTime);
  updatePosition(deltaTime);
  lastPhyicsAnimationTime = animationTime;
}

//void Galaxy::updateForces(double deltaTime) {
//  for (size_t galaxySize = 0; galaxySize < galaxyList.size(); galaxySize++) {
//    for (size_t i = 0; i < galaxyList.at(galaxySize).size(); i++) {
//      Planet planet = galaxyList.at(galaxySize).at(i);
//      ofVec3f overallForce;
//      for (size_t j = 0; j < galaxyList.at(galaxySize).size(); j++) {
//        Planet otherPlanet = galaxyList.at(galaxySize).at(j);
//        if (planet != otherPlanet) {
//          ofVec3f distanceVector = planet.getPosition() - (otherPlanet.getPosition());
//          double distance = distanceVector.length();
//          double minimumDistance = otherPlanet.getRadius() + planet.getRadius() + 100;
//          if (distance != 0) {
//            if (distance < minimumDistance) {
//              ofVec3f force = distanceVector.getScaled(-(distance - minimumDistance) * 100. / (distance * distance));
//              overallForce + force;
//            }
//            // calculate the force as reverse proportional to the distance square scaled by the field strength
//            ofVec3f force =
//              distanceVector.getScaled(-10 * planet.getRadius() * otherPlanet.getRadius() / (distance *
//                distance * distance));
//            overallForce + force;
//          }
//        }
//      }
//      ofVec3f center(galaxyList.at(galaxySize).at(0).getPosition());
//      overallForce + center - planet.getPosition().scale(0.9);
//      // acc = forceVektor/mass
//      ofVec3f acceleration = overallForce.getScaled(1.0 / planet.getRadius());
//      // dV
//      ofVec3f deltaSpeed = acceleration.getScaled(deltaTime);
//      if (deltaSpeed.length() > 50) {
//        deltaSpeed.rescale(50);
//      }
//      // v += dV
//      planet.setSpeed(planet.getSpeed() + deltaSpeed);
//      planet.setSpeed(planet.getSpeed().getScaled(0.9));
//      galaxyList.at(galaxySize).at(i) = planet;
//    }
//  }
//}

void Galaxy::updatePosition(double deltaTime) {
  for (size_t galaxySize = 0; galaxySize < galaxyList.size(); galaxySize++) {
    for (size_t i = 0; i < galaxyList.at(galaxySize).size(); i++) {
      Planet planet = galaxyList.at(galaxySize).at(i);
      cout << planet.getPosition() << endl;
      if (planet.isMovable()) {
        planet.addRotationAngle();
        // dX
        ofVec3f deltaPos = planet.getSpeed().getScaled(deltaTime);
        // x += dX
        planet.setPosition(planet.getPosition() + deltaPos);
        galaxyList.at(galaxySize).at(i) = planet;
      }
    }
  }
}


void Galaxy::draw() {
  ofBuffer();
  ofSetColor(22, 123, 51);
  for (size_t galaxySize = 0; galaxySize < galaxyList.size(); galaxySize++) {
    for (size_t i = 0; i < galaxyList.at(galaxySize).size(); i++) {
      Planet planet = galaxyList.at(galaxySize).at(i);
      ofPushMatrix();
      ofFill();
      float modu = 10 * getFFTSmooth()[planet.getPlanetIndex()] *
        pow((i + 1.0), 6 / 4);

      if (i == 0) {
        ofSphere(planet.getPosition().x, planet.getPosition().y,
          planet.getPosition().z,
          planet.getRadius());
      } else {
        ofRotate(planet.getRotationAngle(), 1.0f, 1.0f, 0.0f);
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
        } else {
          ofTranslate(0, 0, -modu);
        }
        ofSphere(planet.getPosition().x, planet.getPosition().y,
          planet.getPosition().z,
          planet.getRadius());
      }
      ofPopMatrix();
    }
  }
}


int Galaxy::irand(int min, int max) const {
  return (int) (((double) rand() / ((double) RAND_MAX + 1.0)) * (max - min + 1) + min);
}

