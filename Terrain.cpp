#include "Terrain.h"
#include "ofMain.h"
#include <math.h>

Terrain::Terrain() {
  this->nBands = 10;
  fftSmooth = new float[128];
  for (int i = 0; i < 128; i++) {
    fftSmooth[i] = 0;
  }
  meshResolution = 1024;
  gridSurfaceSetup();
  //setPeeks();
  //debug_vertex();
  set_sinus_heights();
  set_colors();
  set_sinus_heights();
  set_sinus_heights();
  //Light
  //light.setPointLight();

  getheight();

}

void Terrain::gridSurfaceSetup() {

  int count = 0;
  int count2 = 0;


  for (int row = 0; row < meshResolution; row++) {
    for (int column = 0; column < meshResolution; column++) {

        gridMesh.addVertex( ofPoint( row * 2 , 0.0f , column * 2 ));
      }
    }
julian.c.fink@googlemail.com
cout << "number of meshresolution " << meshResolution << endl;

  int maxIndexValue = meshResolution*(meshResolution-1)-1;

  for (int i = 0; i < maxIndexValue; i++){

    float sideValue = (i+1)%meshResolution;

    if ( sideValue ==  0) continue;
    gridMesh.addTriangle(                i,                i+1, meshResolution+i );

    gridMesh.addTriangle( meshResolution+i, meshResolution+i+1,              i+1 );
	}
julian.c.fink@googlemail.com
}

void Terrain::update() {
  float *val = ofSoundGetSpectrum(nBands);

  for (int i = 0; i < nBands; i++) {
    fftSmooth[i] *= 0.97f;
    fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
  }

  //Light

//  light.setPosition(cos (ofGetElapsedTimef()) * 200 + 200, 200, sin (ofGetElapsedTimef() * 200));
    light.setPosition(ofVec3f(512, 20, 512));
}

void Terrain::draw() {
  //Light
  //ofEnableLighting();
  //light.enable();


  ofPushStyle();
  ofTranslate(-(meshResolution / 8), 0, -(meshResolution / 8));
  ofSetColor(255, 255, 255);
  //gridMesh.drawWireframe();
  gridMesh.draw();
  test();

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

void Terrain::debug_vertex() {
    for (int row = 0; row < meshResolution  ; row++) {
    for (int column = 0; column < meshResolution ; column++) {
        cout << "Vector number " << row + column << " has coordinates " << gridMesh.getVertex(row * column) << endl;
    }
}
}


void Terrain::set_sinus_heights() {
 cout << "number of vertices " << gridMesh.getNumVertices() << endl;
 for (int i = 0; i < gridMesh.getNumVertices(); i++) {
    ofVec3f vector;
    vector = gridMesh.getVertex(i);
    //vector.y = sin(2 * M_PI * vector.z) * sin ( 2 * M_PI * vector.x);
    vector.y = (sin( 2 * M_PI * ((vector.z / 512) -1 )) * sin ( 2 * M_PI * ((vector.x / 512) -1 ))) * 100;

    gridMesh.setVertex(i, vector);
    //cout << "vector : " << vector << endl;
 }
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


void Terrain::set_colors() {
    int steps = 200;
    int i;
    float n;
    unsigned char r, g, b;
    ofColor color_array[200];
    for( i = 1; i <= steps / 2; i++ )
    {

        n = (float)i / (float) (steps-1);
        r = (float) 0 * (1.0f-n) + (float) 38* n;
        g = (float) 7 * (1.0f-n) + (float) 172 * n;
        b = (float) 299 * (1.0f-n) + (float) 22 * n;
        ofColor t(r,g,b);
        color_array[i] = t;
        cout << " Color " << i << " is " << t << endl;
    }

     for( i = steps / 2; i <= steps; i++ )
    {

        n = (float)i / (float) (steps-1);
        r = (float) 38 * (1.0f-n) + (float) 255* n;
        g = (float) 172 * (1.0f-n) + (float) 255 * n;
        b = (float) 22 * (1.0f-n) + (float) 255 * n;
        ofColor t(r,g,b);
        color_array[i] = t;
        cout << " Color " << i << " is " << t << endl;
    }



    for (int i=0; i < gridMesh.getNumVertices(); i++) {
            ofVec3f v = gridMesh.getVertex(i);
            //if (v.y > 0)
            gridMesh.addColor(color_array[(int)v.y + 100]);
        }
}

void Terrain::getheight() {
  int lowest = 0;
  int highest = 0;
  for (int i = 0; i < gridMesh.getNumVertices(); i++) {
    ofVec3f v = gridMesh.getVertex(i);
    if (v.y < lowest)
     lowest = v.y;
    if (v.y > highest)
     highest = v.y;
  }
  cout << "Highest Y is " << highest << endl;
  cout << "Lowest Y is " << lowest << endl;

}
