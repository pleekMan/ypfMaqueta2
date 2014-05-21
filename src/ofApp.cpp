#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    canvasWidth = ofGetWidth();
    canvasHeight = ofGetHeight();
    
    mainLayer.allocate(canvasWidth, canvasHeight);
    maskLayer.allocate(canvasWidth, canvasHeight);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    mainLayer.begin();
    
    
    
    
    
    mainLayer.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

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
