//
//  WaterManager.h
//  ypfMaqueta2
//
//  Created by PleekMan on 21/5/2014.
//
//

//#ifndef __ypfMaqueta2__WaterManager__
//#define __ypfMaqueta2__WaterManager__

#include <iostream>
#include "ofMain.h"
#include "MSAFluid.h"
#include "TriangleMesh.h"

//#endif /* defined(__ypfMaqueta2__WaterManager__) */

class WaterManager {
    
    
public:
    WaterManager(){};

    void setup();
    void update();
    void render();
    
    void onMouseReleased(int x, int y, int button);
    void addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce);


    msa::fluid::Solver      fluidSolver;
	//msa::fluid::DrawerGl	fluidDrawer;
    
    ofVec2f pMouse;
    float velocityMult;
    
    TriangleMesh water;
};