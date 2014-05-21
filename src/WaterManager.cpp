//
//  WaterManager.cpp
//  ypfMaqueta2
//
//  Created by PleekMan on 21/5/2014.
//
//

#include "WaterManager.h"

void WaterManager::setup(){
    
    fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	
    //fluidDrawer.setup(&fluidSolver);
    
    water.setup(ofGetWindowWidth(),ofGetWindowHeight(), 20);
    water.setFluidSolver(&fluidSolver);

}

void WaterManager::update(){
    fluidSolver.update();
    water.update();
}

void WaterManager::render(){
    water.render();
}