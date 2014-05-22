//
//  WaterManager.cpp
//  ypfMaqueta2
//
//  Created by PleekMan on 21/5/2014.
//
//

#include "WaterManager.h"

void WaterManager::setup(){
    
    fluidSolver.setup(100, 100); // gridX;
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	
    //fluidDrawer.setup(&fluidSolver);
    
    water.setup(ofGetWindowWidth(),ofGetWindowHeight(), 20);
    
    velocityMult = 1;
    //water.setFluidSolver(*fluidSolver);
    
}

void WaterManager::update(){
    
    
    fluidSolver.update();
    water.update();
}

void WaterManager::render(){
    
    ofVec2f windowSize(ofGetWindowWidth(), ofGetWindowHeight());
    ofVec2f invWindowSize(1.0f / windowSize.x, 1.0f / windowSize.y);
    
    water.render(fluidSolver, windowSize, invWindowSize);
    ofDrawBitmapString(ofToString(fluidSolver.getAvgSpeed()), 10,10);
}

void WaterManager::onMouseReleased(int x, int y, int button){
    
    
    ofVec2f eventPos = ofVec2f(x, y);
	
    ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
    ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
    addToFluid(mouseNorm, mouseVel, true, true);
    pMouse = eventPos;
    
    addToFluid(mouseNorm, mouseVel, true, true);

    
    /*
    
    
    
    //for (int i = 0; i < 10; i++) {
        ofVec2f particlePos = ofVec2f(mousePos.x + ofRandom(-50,50), mousePos.y + ofRandom(-50,50));
        ofVec2f particleNorm = ofVec2f(particlePos) / ofGetWindowSize();
        ofVec2f particleVel = ofVec2f((particlePos - mousePos)) / ofGetWindowSize();
        
        addToFluid(particleNorm, particleVel, true, true);
    //}
    
    
    int index = fluidSolver.getIndexForPos(ofVec2f(x,y));
    
    fluidSolver.addForceAtIndex(index, ofVec2f(.01,.01));
     */
    
}

// add force and dye to fluid, and create particles
void WaterManager::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce) {
    
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0) {
		pos.x = ofClamp(pos.x, 0.0f, 1.0f);
		pos.y = ofClamp(pos.y, 0.0f, 1.0f);
		
        int index = fluidSolver.getIndexForPos(pos);
        cout << "Index: " << index << " // Speed: " << speed << endl;
		/*
		if(addColor) {
            //			Color drawColor(CM_HSV, (getElapsedFrames() % 360) / 360.0f, 1, 1);
			ofColor drawColor;
			drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
			
			fluidSolver.addColorAtIndex(index, drawColor * colorMult);
			
			//if(drawParticles)
			//	particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
        }
         */
		
		if(addForce)
			fluidSolver.addForceAtIndex(index, vel * velocityMult);
		
    }
}

