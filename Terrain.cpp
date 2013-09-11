#include "Terrain.h"
#include "ofMain.h"
#include <math.h>

Terrain::Terrain() {
  this->nBands = 10;
  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }
  gridSurfaceSetup();
  setPeeks();
}

void Terrain::gridSurfaceSetup() {
  meshResolution = 16;
  int count = 0;
  int count2 = 0;
  int x = 0;
  int y = 0;
  int z = 0;
  
  for (int row = 0; row < meshResolution; row++) {
    for (int column = 0; column < meshResolution; column++, x++, y++, z++) {
      
        //ofFill();
        gridMesh.addColor(ofColor(0, 0, 0));
        gridMesh.addVertex( ofPoint( row / 4 , 0.0f , column / 4));
      }
    }
  

    
  cout << "Count is " << count << endl;
  cout << "Number of Vertices" << gridMesh.getNumVertices() << endl;
  
  int maxIndexValue = meshResolution*(meshResolution-1)-1;
  
  for (int i = 0; i < maxIndexValue; i++){
    
    float sideValue = (i+1)%meshResolution;
    
    if ( sideValue ==  0) continue;
    gridMesh.addTriangle(                i,                i+1, meshResolution+i );
    
    gridMesh.addTriangle( meshResolution+i, meshResolution+i+1,              i+1 );
	}

  gridMesh.enableTextures();
}

void Terrain::update() {
  float *val = ofSoundGetSpectrum(nBands);
  
  for (int i = 0; i < nBands; i++) {
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  } 
}

void Terrain::draw() {
/*
  ofVec3f vector;
  for (int i = 0; i < nBands; i++) {
        modu = 2 * fftSmooth[i] * pow((i + 1.0), 6/4);
    for (int j = 0; j < peeks.size(); j++) {
      if (j % 6 == 0 ) {
      vector = gridMesh.getVertex(peeks[j]);
      vector.y = 30 * modu;
      gridMesh.setVertex(peeks[j], vector);
      }
    }
  }
 */
  
  test();
  
// ORIGINAL ENDE
  //test();

 // test_heights();
    
  
  ofPushStyle();
  ofTranslate(-(meshResolution / 8), 0, -(meshResolution / 8));
  ofSetColor(255, 255, 255);
  gridMesh.drawWireframe();
  //gridMesh.draw(); 
  ofPopStyle();
}

void Terrain::setBands(int bands) {
  this->nBands = bands;
}

void Terrain::setPeeks() {
  int count = 0;
  for (int row = 0; row < meshResolution; row++) {
    for (int column = 0; column < meshResolution; column++) {
      if ((row % 4 == 0 && row != 0 && row != meshResolution - 1) || (column % 4 == 0 && column != 0 && column != meshResolution - 1)) {
        peeks.push_back(count);
      }
      count++;
    }
    
  }
  std::sort(peeks.begin(), peeks.end());
  cout << "Peeks Size: " << peeks.size() << endl;
}


void Terrain::test_heights() {
  ofVec3f vector;
  int count = 0;
  for (int row = 0; row < meshResolution; row++) {
    for (int column = 0; column < meshResolution; column++) {
      if ((row == meshResolution / 2 && column == meshResolution / 2))      
      {
        testvector.push_back(count);
      }
    count++;
    }
          
  }
    std::sort(testvector.begin(), testvector.end());
  int test = 0;
  for (int j = 0; j < testvector.size(); j++) {
    test = testvector.at(j);
      vector = gridMesh.getVertex(test);
      vector.y = 5;
      gridMesh.setVertex(test, vector);
    
      vector = gridMesh.getVertex(test+1);
      vector.y = 3;
      gridMesh.setVertex(test+1, vector);
    
      vector = gridMesh.getVertex(test+2);
      vector.y = 3;
      gridMesh.setVertex(test+2, vector);

  }
}




void Terrain::test() {

  ofVec3f vector;

  int range = 0;
  float modulation = 0;

    for (int i = 0; i < nBands; i++) {
      
      modulation = 2 * fftSmooth[i] * pow((i + 1.0), 6/4);

      cout << "Modulation is " << modulation * 2 << endl;

      for (int j = range; j < (peeks.size() / nBands) + range; j++) {
        if (j % 24 == 0) {
          vector = gridMesh.getVertex(peeks[j]);
          vector.y = 2 * modulation;
          gridMesh.setVertex(peeks[j], vector);

        }
      }
      range+=(peeks.size() / nBands);
   
    }
 
  
  
}
