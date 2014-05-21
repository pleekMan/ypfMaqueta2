#pragma once

#include "ofMain.h"

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
    
    // NOISE
    
    float increment = 0.01;
    float zoff = 0.0;     // The noise function's 3rd argument, a global variable that increments once per cycle
    float zincrement = 0.01;     // We will increment zoff differently than xoff and yoff
    
    
    
		
};
