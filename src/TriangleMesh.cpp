//
//  TriangleMesh.cpp
//  noiseField2dExample
//
//  Created by PleekMan on 21/5/2014.
//
//

#include "TriangleMesh.h"

static const float MOMENTUM = 0.1f;
static const float FLUID_FORCE = 0.3f;

void TriangleMesh::setup(int _width, int _height, int rowColumnCount){
    
    complexity = 8; // NOISE SCALE
    timeSpeed = .005; // MOTION SPEED
    
    nPoints = 4096; // points to draw
    //pollenMass = .8; // pollen mass
    phase = TWO_PI; // separate u-noise from v-noise
    //windSpeed = 40; // wind vector magnitude for debug
    //step = 10; // spatial sampling rate for debug
    //debugMode = false;
    
    //---------------------
	// SETUP NOISE GRID
    
	// randomly allocate the points across the screen
    points.resize(nPoints);
    for(int i = 0; i < nPoints; i++) {
        points[i] = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
    }
	
	// we'll be drawing the points into an ofMesh that is drawn as bunch of points
	cloud.clear();
	cloud.setMode(OF_PRIMITIVE_POINTS);
    
    //-----------------------
    
    // CREATE ORIGINAL POINT PLACEMENT
    
    //ofEnableLighting();
    
    width = _width;
    height = _height;
    
    zMultiplier = 70;
    
    vertexRowCount = rowColumnCount;
    int gridWidth = width;
    float separation = gridWidth / (float)vertexRowCount;
    float x = 0;
    float y = 0;
    
    while (y < (gridWidth - separation) ) {
        ofVec3f newPoint = ofVec3f(x,y,0);
        waterPoints.push_back(newPoint);
        x+= separation;
        if ((x) > gridWidth - 1) {
            x = 0;
            y += separation;
        }
    }
    
    
    water.setMode(OF_PRIMITIVE_TRIANGLES);
    
    for (int i=0; i < waterPoints.size(); i++) {
        
        // 0
        water.addVertex(waterPoints[i]);
        // 1
        ofVec3f newPos = ofVec3f(waterPoints[i].x + separation, waterPoints[i].y, waterPoints[i].z);
        water.addVertex(newPos);
        // 2
        newPos = ofVec3f(waterPoints[i].x, waterPoints[i].y + separation, waterPoints[i].z);
        water.addVertex(newPos);
        //----
        //3
        newPos = ofVec3f(waterPoints[i].x + separation, waterPoints[i].y, waterPoints[i].z);
        water.addVertex(newPos);
        //4
        newPos = ofVec3f(waterPoints[i].x, waterPoints[i].y + separation, waterPoints[i].z);
        water.addVertex(newPos);
        //5
        newPos = ofVec3f(waterPoints[i].x + separation, waterPoints[i].y + separation, waterPoints[i].z);
        water.addVertex(newPos);
    }
    
    
    
    for (int i=0; i < water.getVertices().size(); i++) {
        //water.addColor(ofColor(0,0,255));
        water.addColor(ofColor::blue);
    }
    
    //glEnd();
    
    light.setDiffuseColor(ofColor::white);
    light.setSpecularColor(ofColor::white);
    
    light.setPosition(0, 0, -200);
    
    //light.enable();
    
    
    
}

void TriangleMesh::setFluidSolver(const msa::fluid::Solver &fSolver){
    //fluidSolver = *fluidSolver;
    fluidSolver = &fSolver;
    //fluidSolver->setup(width, height);
    //ofVec2f vel = fluidSolver->getVelocityAtPos(ofVec2f(0,0));
    
}

void TriangleMesh::setDimensions(int width, int height){
    
}

void TriangleMesh::setGrid(int rowColumnCount){
    
}


void TriangleMesh::update(){
    
    /*
     for(int i = 0; i < nPoints; i++) {
     float x = points[i].x, y = points[i].y;
     //ofVec2f field = getField(points[i]); // get the field at this position
     // use the strength of the field to determine a speed to move
     // the speed is changing over time and velocity-space as well
     //float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
     // add the velocity of the particle to its position
     //x += ofLerp(-speed, speed, field.x);
     //y += ofLerp(-speed, speed, field.y);
     // if we've moved outside of the screen, reinitialize randomly
     //if(x < 0 || x > width || y < 0 || y > height) {
     //    x = ofRandom(0, width);
     //    y = ofRandom(0, height);
     // }
     // save the changes we made to the position
     //points[i].x = x;
     //points[i].y = y;
     // add the current point to our collection of drawn points
     //cloud.addVertex(ofVec2f(x, y));
     }
     */
    
    t = ofGetFrameNum() * timeSpeed;
    
    light.setPosition(ofGetMouseX(),ofGetMouseY(), 200);
    ofCircle(ofGetMouseX(),ofGetMouseY(), 10);
    
    // CALCULATE VERTEX POSITION AND COLOR
    
    for (int y=0; y < vertexRowCount - 1; y++) {
        for (int x=0; x < vertexRowCount; x++) {
            
            int actualPoint = x + (y * vertexRowCount);
            //cout << actualPoint << " : " << x << "." << y << endl;
            
            // GET NOISE AT POINT (  USING THE ORIGINAL waterPoins[] OR THE ACTUAL VERTEX AT water.getVertex(point * 6)  )
            //float upVector = getField(ofVec2f(waterPoints[actualPoint].x, waterPoints[actualPoint].y)).length();
            float upVector = getField(ofVec2f(water.getVertex(actualPoint * 6).x,water.getVertex(actualPoint * 6).y)).length();
            
            //FROM THE actualPoint MOVE AL TRIANGLES THAT SHARE VERTEX AT SAME POSITION
            moveVerticesFromPoint(actualPoint, upVector, zMultiplier, vertexRowCount);
            
            float colorVariantTriangle1 = getTriangleAverage(actualPoint, 1);
            float colorVariantTriangle2 = getTriangleAverage(actualPoint, 2);
            
            ofColor c1 = ofColor(0,0,ofClamp(colorVariantTriangle1 * 255,0,255));
            ofColor c2 = ofColor(0,0,ofClamp(colorVariantTriangle2 * 255,0,255));
            
            //ofColor c1 = ofColor(50,50,ofClamp(colorVariantTriangle1 * 4, 0, 255));
            //ofColor c2 = ofColor(50,50,ofClamp(colorVariantTriangle2 * 4,0,255));
            
            
            water.setColor(actualPoint * 6, c1);
            water.setColor(actualPoint * 6 + 1, c1);
            water.setColor(actualPoint * 6 + 2, c1);
            water.setColor(actualPoint * 6 + 3, c2);
            water.setColor(actualPoint * 6 + 4, c2);
            water.setColor(actualPoint * 6 + 5, c2);
            
            
            //ofDrawBitmapString(ofToString(actualPoint), ofPoint(waterPoints[actualPoint].x, waterPoints[actualPoint].y + 10));
            
        }
    }
    
    
    //glBegin(GL_QUAD_STRIP);
    //water.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    
    
}

void TriangleMesh::render(const msa::fluid::Solver &fSolver, ofVec2f windowSize, ofVec2f invWindowSize){
    
    ofBackground(255,255,255,10);
    
    ofPushMatrix();
    //ofTranslate(0,500,-ofGetMouseX());
    //ofRotateX(90);
    
    ofSetColor(ofColor::blue);
    //water.draw();
    
    ofSetColor(ofColor::white);
    water.drawWireframe();
    
    ofPopMatrix();
    
    
    // DRAW CIRCLES
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    for (int i=0; i<waterPoints.size(); i+=4) {
        
        //float radius = getField(ofVec2f(waterPoints[i].x, waterPoints[i].y)).length();
        ofVec2f pos = ofVec2f(waterPoints[i].x, waterPoints[i].y);
        
        //float radius = fSolver.getVelocityAtPos(pos).length();
        
        ofVec2f vel (fSolver.getVelocityAtPos( pos * invWindowSize ) * windowSize * MOMENTUM);
        float radius = vel.length();
        
        ofCircle(waterPoints[i].x, waterPoints[i].y, radius * 10000);
        ofDrawBitmapString(ofToString(radius), pos);
        
        
    }
    
    
    // ----------------
    
    
    /*
     if(debugMode) {
     ofSetColor(0);
     // draw a vector field for the debug screen
     for(int i = 0; i < width; i += step) {
     for(int j = 0; j < height; j += step) {
     ofVec2f field = getField(ofVec2f(i, j));
     ofPushMatrix();
     ofTranslate(i, j);
     ofSetColor(0);
     ofLine(0, 0, ofLerp(-windSpeed, windSpeed, field.x), ofLerp(-windSpeed, windSpeed, field.y));
     ofPopMatrix();
     }
     }
     // draw the points as circles
     ofSetColor(ofColor::red);
     for(int i = 0; i < nPoints; i++) {
     ofCircle(points[i], 2);
     }
     } else {
     // when not in debug mode, draw all the points to the screen
     ofSetColor(0, 10);
     cloud.draw();
     }
     
     ofDrawBitmapStringHighlight("click to reset\nhit any key for debug", 10, 10, ofColor::white, ofColor::black);
     */
    
    
    
    
    
}

ofVec2f TriangleMesh::getField(ofVec2f position) {
    
    /*
     This is the magic method that samples a 2d slice of the 3d noise field. When
     you call this method with a position, it returns a direction (a 2d vector). The
     trick behind this method is that the u,v values for the field are taken from
     out-of-phase slices in the first dimension: t + phase for the u, and t - phase
     for the v.
     */
    //--------------------------------------------------------------
    
    float normx = ofNormalize(position.x, 0, ofGetWidth());
    float normy = ofNormalize(position.y, 0, ofGetHeight());
    float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
    float v = ofNoise(t - phase, normx * complexity - phase, normy * complexity + phase);
    return ofVec2f(u, v);
}


void TriangleMesh::moveVerticesFromPoint(int pointIndex, float zMove, float multiplier, int rowCount){
    
    //ofVec3f displaceVector = ofVec3f(waterPoints[pointIndex].x, waterPoints[pointIndex].y, zMove);
    
    
    
    //0
    int actualVertex = (pointIndex) * (6);
    ofVec3f displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    //1
    actualVertex = actualVertex - 3;
    displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    //2
    actualVertex = actualVertex - 2;
    displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    
    
    //3
    actualVertex = ((pointIndex - (rowCount) - 1) * 6) + 5;
    displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    
    //4
    actualVertex = actualVertex + 3;
    displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    //5
    actualVertex = actualVertex + 2;
    displaceVector = ofVec3f(water.getVertex(actualVertex).x, water.getVertex(actualVertex).y, zMove * multiplier);
    water.setVertex(actualVertex, displaceVector);
    
}

float TriangleMesh::getTriangleAverage(int pointIndex, int whichTriangleInTheQuad){
    float average = 0;
    for (int i=0; i<3; i++) {
        int vert = (pointIndex * 6) + (i * whichTriangleInTheQuad);
        average += water.getVertex(vert).z / zMultiplier; // WE DE-MULTIPLY, TO GET THE ORIGINAL NORMALIZED VECTOR
    }
    return average /= 3;
}


