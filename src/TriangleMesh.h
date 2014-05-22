//
//  TriangleMesh.h
//  ypfMaqueta2
//
//  Created by PleekMan on 21/5/2014.
//
//

//#ifndef __ypfMaqueta2__TriangleMesh__
//#define __ypfMaqueta2__TriangleMesh__

#include <iostream>
#include "ofMain.h"
#include <MSAFluid.h>

class TriangleMesh {
    
public:
    
    TriangleMesh(){};
    //~TriangleMesh(){};
    
    void setup(int width, int height, int rowColumnCount);
    void update();
    void render(const msa::fluid::Solver &fSolver, ofVec2f windowSize, ofVec2f invWindowSize);
    
    void setDimensions(int width, int height);
    void setGrid(int rowColumnCount);
    
    void setFluidSolver(const msa::fluid::Solver &fSolver);
    //void addForceToFluid();
    
    
private:
    
    //---
    int nPoints; // points to draw
    float complexity; // wind complexity
    float pollenMass; // pollen mass
    float timeSpeed; // wind variation speed
    float phase; // separate u-noise from v-noise
    float windSpeed; // wind vector magnitude for debug
    int step; // spatial sampling rate for debug
    bool debugMode;
    //---
    
    ofVec2f getField(ofVec2f position);
    void moveVerticesFromPoint(int pointIndex, float zMove, float multiplier, int gridWidth);
    float getTriangleAverage(int pointIndex, int whichTriangleInTheQuad); // THE QUAD IS MADE OUT OF 2 TRIANGLES
    
    const msa::fluid::Solver *fluidSolver;
    
    vector<ofVec2f> points;
    ofMesh cloud;
    float t;
    float width, height;
    
    ofMesh water;
    vector<ofVec3f> waterPoints;
    ofLight light;
    
    int vertexRowCount;
    
    float zMultiplier;
    
};
//#endif /* defined(__ypfMaqueta2__TriangleMesh__) */

