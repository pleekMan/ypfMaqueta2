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

    msa::fluid::Solver      fluidSolver;
	//msa::fluid::DrawerGl	fluidDrawer;
    
    TriangleMesh water;
};