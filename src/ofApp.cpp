#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    canvasWidth = ofGetWidth();
    canvasHeight = ofGetHeight();
    
    mainLayer.allocate(canvasWidth, canvasHeight);
    maskLayer.allocate(canvasWidth, canvasHeight);
    
    //water.setup((int)(canvasWidth * 0.8) , (int)(canvasHeight * 0.8), 20);
    water.setup(canvasWidth,canvasHeight, 20);

    ofDisableLighting();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    mainLayer.begin();
    
    water.update();
    water.render();
    
    
    mainLayer.end();
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(0,0,0), ofColor(40,40,200), OF_GRADIENT_LINEAR);
    ofSetColor(255);
    mainLayer.draw(ofPoint(0,0));
    
}

void ofApp::doPerlin(){
    
        
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
