#include "Galaxy.h"

Galaxy::Galaxy() {
  setBands(15);
  setFilter(1.25);
}

void Galaxy::setup() {
  skyBox.load();
  skyBox.load();
  cam.setPosition(0, 130, 760);
  cam.setTarget(ofVec3f(0, 0, 0));
  cam.enableMouseInput();

  ofEnableNormalizedTexCoords();

  for (int i = 0; i <= getBands(); i++) {

    Planet *planet = new Planet;
    ofImage *texture = new ofImage;
    char *path = (char *) malloc(sizeof(*path) * 128);
    ofVec3f position;

    if (i == 0) {
      snprintf(path, sizeof(*path) * 128, "./textures/texture0.tif");
      texture->loadImage(path);
      planet->setTexture(texture);

      planet->setMovable(false);
      planet->setRadius(sunRadius);
      position.set(0, 0, 0);
    } else {
      snprintf(path, sizeof(*path) * 128, "./textures/texture%d.tif", i % 9 + 1);
      texture->loadImage(path);
      planet->setTexture(texture);

      planet->setMovable(true);
      planet->setRadius(irand(10, 20));
      planet->setRotationAngle(ofRandom(360));
      planet->setRotationSpeed((float) rand() / RAND_MAX + 0.01);
      planet->setPositionOfSun(galaxyList.at(0)->getPosition());
      position.set(ofRandom(60 + 40 * i, 80 + 40 * i), ofRandom(-10, 10), 0);
    }

    planet->setPosition(position);
    galaxyList.push_back(planet);
  }
}


void Galaxy::update() {
  super::update();
  for (size_t i = 1; i < galaxyList.size(); i++) {
    Planet *planet = galaxyList.at(i);
    if (planet->isMovable() && playing) {
      float modu = getFFTSmooth()[i - 1] * 3;
      if (modu < 0.25) {
        modu = 0.25;
      }
      galaxyList.at(i)->update(modu);
    } else {
      galaxyList.at(i)->update(0.25);
    }
  }
}

void Galaxy::draw() {
  cam.begin();

  float *vals = new float [3];
  vals[0] = getFFTSmooth()[0];
  vals[1] = getFFTSmooth()[3];
  vals[2] = getFFTSmooth()[7];
  ofPushMatrix();
  rotator.modulatedRotation(vals[0] / 3.5, vals[1] / 3.5, vals[2] / 3.5);
  rotator.rotate();
  skyBox.draw();
  ofPopMatrix();

  for (size_t i = 0; i < galaxyList.size(); i++) {
    Planet *planet = galaxyList.at(i);
    ofPushMatrix();
    glEnable(GL_DEPTH_TEST);
    ofRotate(planet->getRotationAngle(), 0.0f, 1.0f, 0.0f);
    ofFill();
    planet->draw();
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
  }
  cam.end();
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
    case '0':
      cam.setPosition(0, 130, 760);
      cam.setTarget(ofVec3f(0, 0, 0));
      break;
    case '+':
      if (cam.getPosition().z + 10 > 400) {
        cam.setPosition(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z - 10);
      }
      break;
    case '-':
      if (cam.getPosition().z - 10 < 790) {
        cam.setPosition(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z + 10);
      }
      break;
    default:
      break;
  }
}
