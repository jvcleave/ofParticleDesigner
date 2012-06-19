//
// Copyright (c) 2012, Sound of Code, Lahiru Lakmal Priyadarshana
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "testApp.h"

#include "ofxSimpleGuiToo.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofBackground(0, 0, 0);
	ui.setup();
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
    
    /*if(key>='0' && key<='9') {
		gui.setPage(key - '0');
		gui.show();
	} else {
		switch(key) {
			case ' ': gui.toggleDraw(); break;
			case '[': gui.prevPage(); break;
			case ']': gui.nextPage(); break;
			case 'p': gui.nextPageWithBlank(); break;
			case 'm': doUseMouse = !doUseMouse; break;
			case 's' : doSaveParticleXML = true; break;
		}
	}*/
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

