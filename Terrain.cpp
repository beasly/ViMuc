#include "Terrain.h"
#include "ofMain.h"
#include <math.h>

Terrain::Terrain() {

}

void Terrain::setup() {
  frames = 0;
  meshResolution = 128;
  dist = 300;
  begin.set(18, 3, 194);
  end.set(38, 172, 22);
  indexLow = 0;
  indexHigh = 0;
  setColors(begin, end);
  gridSurfaceSetup();
  setPeeks();
  setBands(meshResolution);
  setFilter(1.25f);
  setSmoothingFactor(0.975f);
  cam.setDistance(dist);
  cam.enableMouseInput();
  ofBackground(0, 0, 0);
}

void Terrain::gridSurfaceSetup() {
  colorPalette[0] = ofColor(255, 0, 0);
  colorPalette[1] = ofColor(255, 0, 171);
  colorPalette[2] = ofColor(239, 0, 255);
  colorPalette[3] = ofColor(51, 0, 255);
  colorPalette[4] = ofColor(51, 0, 255);
  colorPalette[5] = ofColor(0, 213, 255);
  colorPalette[6] = ofColor(0, 255, 199);
  colorPalette[7] = ofColor(17, 255, 0);
  colorPalette[8] = ofColor(222, 255, 0);
  colorPalette[9] = ofColor(222, 145, 0);
  colorPalette[10] = ofColor(0, 0, 0);
  
  ofFloatColor c = color_array[0];
  for (int j = 0; j < meshResolution * meshResolution; j++) {
    gridMesh.addColor(c);
  }
  
  for (int row = 1; row <= meshResolution; row++) {
    for (int column = 1; column <= meshResolution; column++) {
      
      gridMesh.addVertex(ofPoint(row * 2, 0.0f, column  * 2));
    }
  }
  
  int maxIndexValue = meshResolution * (meshResolution - 1) - 1;
  
  for (int i = 0; i < maxIndexValue; i++) {
    float sideValue = (i + 1) % meshResolution;
    if (sideValue ==  0) continue;
    gridMesh.addTriangle(i, i + 1, meshResolution + i);
    gridMesh.addTriangle(meshResolution + i, meshResolution + i + 1, i + 1);
	}
}

void Terrain::draw() {
  
  cam.begin();
  ofPushMatrix();
  updateHeights();
  ofRotateY(-90);
  ofTranslate(-(meshResolution ), -20, -(meshResolution ));
  
  if (drawMode)
    gridMesh.draw();
  else
    gridMesh.drawWireframe();
  
  ofPopMatrix();
  cam.end();
}


void Terrain::update() {
  super::update();
  
  if (frames % 2 == 0) { 
    movePeeks();
  }
  
  frames++;
  if (frames > 1000)
    frames = 0; 
}



void Terrain::setPeeks() {
  int count = 0;
  for (int row = 0; row < meshResolution * 2; row++) {
    peeks.push_back(count);
    count++;
  }
  std::sort(peeks.begin(), peeks.end());
}


void Terrain::movePeeks() { 
  int count = 0;
  for (int i = (meshResolution * meshResolution) - 1; i >= 0; i--) {
    ofVec3f v_follower = gridMesh.getVertex(i);
    ofVec3f v_origin = gridMesh.getVertex(i - meshResolution);
    
    //Vertikal
    ofFloatColor c_follower = gridMesh.getColor(i);
    ofFloatColor c_origin = gridMesh.getColor(i - meshResolution);
    
    // Copy Color and Vertex
    v_follower.y = v_origin.y;
    c_follower = c_origin;
    
    // Set Color and Vertex
    gridMesh.setVertex(i, v_follower);
    gridMesh.setColor(i, c_follower);
    
  }
}

void Terrain::updateHeights() {
  
  ofVec3f vector;
  int range = 0;
  float modulation = 0;
  float * fft_values = getFFTSmooth(); 
  float * fft_plain = getFFTPlain();
  
  for (int i = 0; i < getBands(); i++) {
    modulation = 2 * fft_values[i] * pow((i + 1.0), 6/4);
    for (int j = range; j < (peeks.size() / getBands()) + range; j++) { 
      vector = gridMesh.getVertex(peeks[j]);
      vector.y = (modulation / 4 > (meshResolution - 1) ? (meshResolution / 4 - 1) : modulation);
      gridMesh.setVertex(peeks[j], vector);
    }
    range+=(peeks.size() / getBands());
    setHorizontalColor();
  }
}

void Terrain::setColors(ofColor start, ofColor end) {
  
  int steps = meshResolution / 4;
  float n = 0;
  unsigned char r, g, b;
  
  for(int i = 1; i <= steps; i++ )
  {
    n = (float) i / (float) (steps-1);
    r = (float) start.r  * (1.0f-n) + (float) end.r * n;
    g = (float) start.g * (1.0f-n) + (float) end.g * n;
    b = (float) start.b * (1.0f-n) + (float) end.b * n;
    ofColor t(r,g,b);
    color_array[i - 1] = t;
    
  }
}

void Terrain::setHorizontalColor() { 
  
  for (int i = 0; i < peeks.size(); i++) {
    ofVec3f v = gridMesh.getVertex(i);
    ofFloatColor c = color_array[(int) v.y];
    gridMesh.setColor(i, c);
  }
}


void Terrain::keyPressed(int key) {
  switch(key) {
    case 'u':
      dist += 10;
      cam.setDistance(dist);
      break;
    case 'j':
      dist -= 10;
      cam.setDistance(dist);
      break;
    case 'h':
      drawMode =  true;
      break;
    case 'k':
      drawMode =  false;
      break;
    case 'z':
      indexLow += 1; 
      switchLowerColor(indexLow);
      break;
    case 'i':
      indexHigh += 1;
      switchUpperColor(indexHigh);
      break;
  }
}

void Terrain::switchLowerColor(int i) {
  if (i > 10)
    indexLow = 0;
  begin.set(colorPalette[i]); 
  setColors(begin, end);
}

void Terrain::switchUpperColor(int i) {
  if (i > 10)
    indexHigh = 0;
  end.set(colorPalette[i]); 
  setColors(begin, end);
}

