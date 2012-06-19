#include "testApp.h"
#include "ofxSimpleGuiToo.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ui.setup();
	//ui.loadSample();
}

//--------------------------------------------------------------
void testApp::update(){
    
	ui.update();
}



//--------------------------------------------------------------
void testApp::draw(){

    ui.draw();
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    ui.onKeyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	ui.onMouseDragged(x, y);
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	ui.onMousePressed(x, y);
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

