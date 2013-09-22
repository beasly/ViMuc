#include "Galaxy.h"

Galaxy::Galaxy() {
  Scene::Scene();
  setBands(14);
  planetAmount = getBands();
}


void Galaxy::setup() {
//  skyBox.load();

  ofBackground(255, 255, 255);
  ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
  ofEnableNormalizedTexCoords();

  for (int i = 0; i < planetAmount + 1; i++) {
    Planet *planet = new Planet;
    planet->setMovable(false);
    planet->setRadius(sunRadius);
    ofImage *texture = new ofImage;
    char *path = (char *) malloc(sizeof(*path) * 128);
//    snprintf(path, sizeof(path) * 128, "./textures/texture%d.tif", i);
    snprintf(path, sizeof(path) * 128, "./textures/texture%d.tif", i % 10);
    texture->loadImage(path);
    planet->setTexture(texture);
    ofVec3f position;
    if (i == 0) {
      position.set(0, 0, 0);
    } else {
      planet->setMovable(true);
      planet->setRadius(irand(5, 15));
      planet->setRotationAngle(ofRandom(360));
      planet->setRotationSpeed((float) rand() / RAND_MAX + 0.01);
      planet->setPositionOfSun(galaxyList.at(0)->getPosition());
      bool validOrbit = false;
      while (!validOrbit) {
        float x = ofRandom(400);
        float z = ofRandom(400);
        position.set(x, ofRandom(-10, 10),
          z);
        planet->setPosition(position);
        planet->calculateRadiusOfOrbit();
        if (planet->getRadiusOfOrbit() > planet->getRadius() + sunRadius) {
          if (galaxyList.size() == 1) {
            validOrbit = true;
          } else {
            int testedPlanets = 1;
            for (size_t indexOfPlanet = 1; indexOfPlanet < galaxyList.size();
                 indexOfPlanet++) {
              Planet *otherPlanet = galaxyList.at(indexOfPlanet);
              float positiveDangerZone = otherPlanet->getRadiusOfOrbit() +
                otherPlanet->getRadius();
              float negativeDangerZone = otherPlanet->getRadiusOfOrbit() -
                otherPlanet->getRadius();
              float positiveZone = planet->getRadiusOfOrbit() +
                planet->getRadius();
              float negativZone = planet->getRadiusOfOrbit() -
                planet->getRadius();
              if (positiveDangerZone > negativZone &&
                negativeDangerZone < positiveZone) {
                indexOfPlanet = galaxyList.size();
              }
              testedPlanets++;
            }
            if (testedPlanets == galaxyList.size()) {
              validOrbit = true;
            }
          }
        }
      }
    }
    galaxyList.push_back(planet);
  }

}


void Galaxy::update() {
  Scene::update();
  for (size_t i = 1; i < galaxyList.size(); i++) {
    Planet *planet = galaxyList.at(i);
    if (planet->isMovable() && playing) {
      float modu = getFFTSmooth()[i - 1];
      cout << modu << " " << i << " " << getFFTSmooth()[i - 1] << endl;
      galaxyList.at(i)->update(modu * 2);
    } else {
      galaxyList.at(i)->update(0.25);
    }
  }
}

void Galaxy::draw() {
  ofBuffer();

  for (size_t i = 0; i < galaxyList.size(); i++) {
    Planet *planet = galaxyList.at(i);
    ofPushMatrix();
    ofRotate(planet->getRotationAngle(), 0.0f, 1.0f, 0.0f);
    planet->draw();
  }
  ofPopMatrix();
}


int Galaxy::irand(int min, int max) const {
  return (int) (((double) rand() / ((double) RAND_MAX + 1.0)) * (max - min + 1) + min);
}

void Galaxy::keyPressed(int key) {
  switch (key) {
    case 'q':
      playing = true;
      break;
    case 'w':
      playing = false;
      break;
    default:
      break;
  }
}


