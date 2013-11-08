#include "TApp.h"


testApp::testApp()
{
}

//--------------------------------------------------------------
void testApp::setup() {
	ofBackground( 185, 140, 90 );
}

//--------------------------------------------------------------
void testApp::update() {
	
	float t = (ofGetElapsedTimef()) * 0.9f;
	float div = 250.0;
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetColor(255);
	string info = ofToString(ofGetFrameRate(), 2)+"\n";
	ofDrawBitmapStringHighlight(info, 30, 30);
	
	

}
//--------------------------------------------------------------
void testApp::exit() {
	ofBackgroundGradient(ofColor(255), ofColor(230, 240, 255));
	
	string info = ofToString(ofGetFrameRate(), 2)+"\n";
	ofDrawBitmapStringHighlight(info, 30, 30);
	
	ofSetColor(255);
	

}
