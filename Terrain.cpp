#include "Terrain.h"
#include "ofMain.h"
#include <math.h>

Terrain::Terrain() : super() {
  
  move_count = 0;
  frames = 0;
  meshResolution = 128;
  gridSurfaceSetup();
  super::setBands(meshResolution);
  //setPeeks();
  //debug_vertex();
  
  //set_sinus_heights();
  
  set_colors();
  //set_vertical_color();
  //update_colors();
  //Light
  //light.setPointLight();
  //getheight();
  //test_heights();
  //make_rainbow();
  //draw_rainbow();
  
  setPeeks();
  
  
  
  
}

void Terrain::gridSurfaceSetup() {
  
  int count = 0;
  int count2 = 0;
  
  
  for (int row = 0; row < meshResolution; row++) {
    for (int column = 0; column < meshResolution; column++) {
      
      gridMesh.addVertex( ofPoint( row * 2 , 0.0f , column  * 2 ));
    }
  }
  
  
  cout << "number of meshresolution " << meshResolution << endl;
  
  int maxIndexValue = meshResolution*(meshResolution-1)-1;
  
  for (int i = 0; i < maxIndexValue; i++){
    
    float sideValue = (i+1)%meshResolution;
    
    if ( sideValue ==  0) continue;
    gridMesh.addTriangle(                i,                i+1, meshResolution+i );
    
    gridMesh.addTriangle( meshResolution+i, meshResolution+i+1,              i+1 );
	}
  
  /*
   
   for (int i = 0; i < meshResolution - 1; i++) {
   for (int j = 0; j < meshResolution - 1; j++) {
   gridMesh.addIndex(j + i * meshResolution);               // 0
   gridMesh.addIndex((j + 1) + i * meshResolution);           // 1
   gridMesh.addIndex(j + (i + 1) * meshResolution);           // 10
   
   gridMesh.addIndex((j + 1) + i * meshResolution);           // 1
   gridMesh.addIndex((j + 1) + (i + 1) * meshResolution);       // 11
   gridMesh.addIndex(j + (i + 1) * meshResolution);     
   }
   }
   
   
   */  
}


/*
 void Terrain::update() {
 //update_colors();
 float *val = ofSoundGetSpectrum(nBands);
 
 for (int i = 0; i < nBands; i++) {
 fftSmooth[i] *= 0.97f;
 fftSmooth[i] = fftSmooth[i] < val[i] ? val[i] : fftSmooth[i];
 }
 test_heights();
 //module_terrain();
 
 //Light
 
 //  light.setPosition(cos (ofGetElapsedTimef()) * 200 + 200, 200, sin (ofGetElapsedTimef() * 200));
 // light.setPosition(ofVec3f(512, 20, 512));
 
 }
 */


void Terrain::draw() {
  //Light
  //ofEnableLighting();
  //light.enable();
  
  
  //  update_colors();
  test();
  ofPushStyle();
  ofTranslate(-(meshResolution / 2), 0, -(meshResolution / 2));
  
  ofSetColor(202, 216, 216);
  gridMesh.draw();  
  ofSetColor(0, 0, 0);
  gridMesh.drawWireframe();
  
  
  
  
  
  //test_heights();
  //show_fft();
  //debug_fft();
  //module_terrain();
  ofPopStyle();
}


void Terrain::update() {
  super::update();
  
  if (frames % 3 == 0) { 
    move_peeks();
    
  }
  frames++;
  
  if (frames > 1000)
    frames = 0;
  
  
  
}



void Terrain::setPeeks() {
  int count = 0;
  for (int row = 0; row < meshResolution * 2; row++) {
    //for (int column = 0; column < meshResolution; column++) {
    //  if ((row % 4 == 0 && row != 0 && row != meshResolution - 1) || (column % 4 == 0 && column != 0 && column != meshResolution - 1)) {
    peeks.push_back(count);
    //  }
    count++;
    // }
    
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
  for (int j = 0; j < getBands(); j++) {
    for (int i = 0; i < meshResolution; i++) {
      vector = gridMesh.getVertex(i) ;
      vector.y = 100 * getFFTSmooth()[j] ;
      //cout << 100 + (getFFTSmooth()[j]) << endl;
      //cout << "FFT Smooth " << getFFTSmooth()[j] << endl;/*<< " * 100 " << 100 * getFFTSmooth()[j] << endl*/;
      gridMesh.setVertex(i, vector);
    }
  }
}

void Terrain::move_peeks() { 
  
  for (int i = (meshResolution * meshResolution) - 1; i >= 0; i--) {
    ofVec3f v_follower = gridMesh.getVertex(i);
    ofVec3f v_origin = gridMesh.getVertex(i - meshResolution);
    v_follower.y = v_origin.y;
    gridMesh.setVertex(i, v_follower);
  }
}

void Terrain::test() {
  
  ofVec3f vector;
  
  int range = 0;
  float modulation = 0;
  
  for (int i = 0; i < getBands(); i++) {
    
    modulation = 2 * getFFTSmooth()[i] * pow((i + 1.0), 6/4);
    
    //cout << "Modulation is " << modulation << endl;
    
    for (int j = range; j < (peeks.size() / getBands()) + range; j++) { 
      {
        
        vector = gridMesh.getVertex(peeks[j]);
        vector.y = 2 * modulation;
        gridMesh.setVertex(peeks[j], vector);
        
        
        
          cout << "Vector: " << j << " Modulation: " << modulation * 2 << endl;
        
        
        
      }
    }
    
    range+=(peeks.size() / getBands());
    
  }
  
  
  
  
  
  
}


void Terrain::set_colors() {
  int steps = meshResolution;
  int i;
  float n;
  unsigned char r, g, b;
  
  for( i = 1; i <= steps ; i++ )
  {
    
    n = (float)i / (float) (steps-1);
    r = (float) 18 * (1.0f-n) + (float) 38* n;
    g = (float) 1 * (1.0f-n) + (float) 172 * n;
    b = (float) 194 * (1.0f-n) + (float) 22 * n;
    ofColor t(r,g,b);
    color_array[i] = t;
    
  }
  /*
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
   
   */
  
  
}


void Terrain::update_colors() {
  for (int i = 0; i < gridMesh.getNumVertices(); i++) {
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

void Terrain::module_terrain() {
  ofVec3f vector;
  
  
  float modulation = 0;
  
  
  
  
  for (int i = 0; i < getBands(); i++) {
    
    modulation = (200 * getFFTSmooth()[i]);
    
    
    for (int i = 0; i < gridMesh.getNumVertices(); i++)
      vector = gridMesh.getVertex(i);
    vector.y = modulation;
    //cout << "Modulation is " << modulation << endl;
    gridMesh.setVertex(i, vector);
  }
  
  
}

void Terrain::debug_fft() {
  vector<float> fft;
  
  for (int i = 0; i < getBands(); i++) {
    if (highest < getFFTSmooth()[i])
      highest = getFFTSmooth()[i];
    if (lowest > getFFTSmooth()[i])
      lowest = getFFTSmooth()[i];
    cout << "highest : "<< highest << endl;
    cout << "lowest : "<< lowest << endl;
  }
  
}

void Terrain::show_fft() {
  
  for (int i = 0; i < getBands(); i++) {
    cout << "Band: " << i << " Value: " << getFFTSmooth()[i] << endl;
  }
  
}
/*
 void Terrain::normalize_heights() {
 
 }
 
 */

void Terrain::make_rainbow() {
  for (double i = 0; i < 1; i += 1 / meshResolution) {
    ofColor color = HSL2RGB(i, 0.5, 0.5);
    //  cout << color << endl; 
    rainbow_vector.push_back(color);
  }
  
}


void Terrain::set_vertical_color() {
  int count = 0;
  for (int row = 0; row < meshResolution; row++) {
    for (int columns = 0; columns < meshResolution; columns++) {
      ofVec3f v = gridMesh.getVertex(count);
      gridMesh.addColor(color_array[columns]);
      count++;
    }
  }
  
}


ofColor Terrain::HSL2RGB(double h, double s, double l) {
  unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
  
	float L = ((float)l)/100;
	float S = ((float)s)/100;
	float H = ((float)h)/360;
  
	if(s == 0)
	{
		r = l;
		g = l;
		b = l;
	}
	else
	{
		float temp1 = 0;
		if(L < .50)
		{
			temp1 = L*(1 + S);
		}
		else
		{
			temp1 = L + S - (L*S);
		}
    
		float temp2 = 2*L - temp1;
    
		float temp3 = 0;
		for(int i = 0 ; i < 3 ; i++)
		{
			switch(i)
			{
        case 0: // red
				{
					temp3 = H + .33333f;
					if(temp3 > 1)
						temp3 -= 1;
					HSLtoRGB_Subfunction(r,temp1,temp2,temp3);
					break;
				}
        case 1: // green
				{
					temp3 = H;
					HSLtoRGB_Subfunction(g,temp1,temp2,temp3);
					break;
				}
        case 2: // blue
				{
					temp3 = H - .33333f;
					if(temp3 < 0)
						temp3 += 1;
					HSLtoRGB_Subfunction(b,temp1,temp2,temp3);
					break;
				}
        default:
				{
          
				}
			}
		}
	}
	r = (unsigned int)((((float)r)/100)*255);
	g = (unsigned int)((((float)g)/100)*255);
	b = (unsigned int)((((float)b)/100)*255);
  ofColor color(r, g, b);
  cout << color << endl;
  return color;
}

void Terrain::HSLtoRGB_Subfunction(unsigned int& c, const float& temp1, const float& temp2, const float& temp3)
{
	if((temp3 * 6) < 1)
		c = (unsigned int)((temp2 + (temp1 - temp2)*6*temp3)*100);
	else
		if((temp3 * 2) < 1)
			c = (unsigned int)(temp1*100);
		else
			if((temp3 * 3) < 2)
				c = (unsigned int)((temp2 + (temp1 - temp2)*(.66666 - temp3)*6)*100);
			else
				c = (unsigned int)(temp2*100);
	return;
}



