#pragma once

#include "ofMain.h"
#include "WaterManager.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void doPerlin();
    
    int canvasWidth, canvasHeight;
    
    ofFbo mainLayer;
    ofFbo maskLayer;
    
    ofShader maskShader;
    
    WaterManager waterManager;
    
    INTEGRANDO EL FLUID: USAR EL FLUID PASADO A TRIANGLE PARA MOVER EL MESHX
    
		
};
