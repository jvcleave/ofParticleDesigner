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
	ofSetVerticalSync(true);
	pexID = 0;
	textureID = 0;
	currentTextureID = 0;
	currentPexID = 0;
	doUseMouse = false;
	doSaveParticleXML = false;
    loadFromParticleXML( "circles.pex" );
    
    doPlay = false;
        
    speed = 0.0;
    duration = -1.0;
    
    //---------- SETTINGS ---------------
	gui.addTitle("Particle Settings");
    
	//gui.addToggle("Play", doPlay);
    gui.addToggle("Use Mouse", doUseMouse);
    gui.addSlider("Source Pos X", m_emitter.sourcePosition.x, 0.0, ofGetWidth());
    gui.addSlider("Source Pos X Var", m_emitter.sourcePositionVariance.x, 0.0, ofGetWidth());
    gui.addSlider("Source Pos Y", m_emitter.sourcePosition.y, 0.0, ofGetHeight());
    gui.addSlider("Source Pos Y Var", m_emitter.sourcePositionVariance.y, 0.0, ofGetHeight());
    
    gui.addSlider("Angle", m_emitter.angle, 0.0, 360);
    gui.addSlider("Angle Var", m_emitter.angleVariance, 0.0, 360);
    
    gui.addSlider("LifeSpan", m_emitter.particleLifespan, 0.000, 10.000);
    gui.addSlider("LifeSpan Var", m_emitter.particleLifespanVariance, 0.000, 10.000);
    
    gui.addSlider("Start Size", m_emitter.startParticleSize, 0, 512);
    gui.addSlider("Start Size Var", m_emitter.startParticleSizeVariance, 0, 512);
    gui.addSlider("Finish Size", m_emitter.finishParticleSize, 0, 512);
    gui.addSlider("Finish Size Var", m_emitter.finishParticleSizeVariance, 0, 512);
    
    //gui.addSlider("Max Particles", m_emitter.maxParticles, 0, 1000);
    //gui.addSlider("Particle Count", m_emitter.particleCount, 0, 1000);
    
    //--------- TYPE --------------------
    gui.addTitle("Type");
    string titleArray[] = {"Gravity","Radial"};
	gui.addComboBox("Emitter Type", m_emitter.emitterType, 2, titleArray);
    
    gui.addTitle("Gravity");
    gui.addSlider("Speed", m_emitter.speed, 0.0, 1000);
    gui.addSlider("Speed Var", m_emitter.speedVariance, 0.0, 1000);
    
    gui.addSlider("Radial Acc", m_emitter.radialAcceleration, -1000.000, 1000.000);
    gui.addSlider("Radial Acc Var", m_emitter.radialAccelVariance, -1000.000, 1000.000);
    
    gui.addSlider("Tan Acc", m_emitter.tangentialAcceleration, -1000.000, 1000.000);
    gui.addSlider("Tan Acc Var", m_emitter.tangentialAccelVariance, -1000.000, 1000.000);
    
    gui.addSlider("Gravity X", m_emitter.gravity.x, -3000, 3000);
    gui.addSlider("Gravity Y", m_emitter.gravity.y, -3000, 3000);
    
    gui.addTitle("Radial");
    gui.addSlider("Max Radius", m_emitter.maxRadius, 0, 480);
    gui.addSlider("Max Radius Var", m_emitter.maxRadiusVariance, 0, 480);
    gui.addSlider("Min Radius", m_emitter.minRadius, 0, 480);
    
    gui.addSlider("Deg. Per Sec", m_emitter.rotatePerSecond, 0.0, 360);
    gui.addSlider("Deg. Per Sec Var", m_emitter.rotatePerSecondVariance, 0.0, 360);
    
    gui.addSlider("Radius Speed", m_emitter.radiusSpeed, 0, 1000);
    
	//gui.addSlider("Duration", m_emitter.duration, -1.0, 200);
    
    //----------- COLOR ------------------
    gui.addPage("Color");
    gui.addTitle("Color");
	gui.addColorPicker("Start Color", &(m_emitter.startColor).r);
    gui.addColorPicker("Start Color Var", &(m_emitter.startColorVariance).r);
    gui.addColorPicker("End Color", &(m_emitter.finishColor).r);
    gui.addColorPicker("End Color Var", &(m_emitter.finishColorVariance).r);
    
    gui.addTitle("Blend Mode");
    string glTitleArray[] = {"GL_ZERO", "GL_ONE", "GL_DST_COLOR", "GL_ONE_MINUS_DST_COLOR", "GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA", "GL_DST_ALPHA",
    "GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"};
	gui.addComboBox("Blend Type Src", blendSrc, 9, glTitleArray);
    gui.addComboBox("Blend Type Dest", blendDst, 9, glTitleArray);
    gui.addButton("Normal", isNormal);
    gui.addButton("Addictive", isAddictive);
    
    //----------- GALLERY ----------------
    gui.addPage("Gallery");
    gui.addTitle("Particle Texture");

	pexID = currentPexID =  0;
	textureID = currentTextureID = 0;
	ofDirectory dir = ofToDataPath("sampleParticles", true);
	dir.listDir();
	vector<ofFile> files = dir.getFiles();
	
	for(int i=0; i<files.size(); i++)
	{
		cout << files[i].getExtension() << endl;
		
		string fileExtension = files[i].getExtension();
		string fileName = files[i].getFileName();
		if (fileExtension == "pex")
		{
			pexFileNames.push_back(fileName);
		}
		if (fileExtension == "jpg" || fileExtension == "png")
		{
			textureFileNames.push_back(fileName);
		}
	}
	
	gui.addComboBox("TEXTURE FILE", textureID, textureFileNames.size(),  &textureFileNames[0]);
    gui.addComboBox("SOURCE", pexID, pexFileNames.size(),  &pexFileNames[0]);
    gui.setPage(1);
    gui.show();
    
    //m_emitter.sourcePosition.x = ofGetWidth()/2;
    //m_emitter.sourcePosition.y = ofGetHeight()/2;
    
    blendSrc = getBlendType(m_emitter.blendFuncSource);
    blendDst = getBlendType(m_emitter.blendFuncDestination);
    
    //m_emitter.gravity.y = m_emitter.gravity.y * -1;
}

//--------------------------------------------------------------
void testApp::update(){
    
    m_emitter.update();
    
    if( doPlay ){
        //ofSetWindowTitle("Clicked");
        //doPlay = false;
    }
    else if( isNormal ){
        //ofSetWindowTitle("Normal");
        isNormal = false;
        blendSrc = 4;
        blendDst = 5;
    }
    else if( isAddictive ) {
        //ofSetWindowTitle("Addictive");
        isAddictive = false;
        blendSrc = 4;
        blendDst = 1;
    }
    else if( doSaveParticleXML ) {
        doSaveParticleXML = false;
        saveToParticleXML();
    }
	if (currentPexID != pexID)
	{
		currentPexID = pexID;	
		loadFromParticleXML(pexFileNames[currentPexID]);
	}
	if ( currentTextureID!= textureID)
	{
		currentTextureID = textureID;
		m_emitter.changeTexture(textureFileNames[currentTextureID]);
	}
        
    setBlendType(blendSrc, m_emitter.blendFuncSource);
    setBlendType(blendDst, m_emitter.blendFuncDestination);
    
   // ofSetWindowTitle(ofToString(m_emitter.blendFuncSource));
}

void testApp::setBlendType(int s, int &val) {
    
    //GL BLEND TYPE
    switch (s) {
            
        case 0:
            val = 0;
            break;
            
        case 1:
            val = 1;
            break;
            
        case 2:
            val = GL_DST_COLOR;
            break;
            
        case 3:
            val = GL_ONE_MINUS_DST_COLOR;
            break;
            
        case 4:
            val = GL_SRC_ALPHA;
            break;
            
        case 5:
            val = GL_ONE_MINUS_SRC_ALPHA;
            break;
            
        case 6:
            val = GL_DST_ALPHA;
            break;
            
        case 7:
            val = GL_ONE_MINUS_DST_ALPHA;
            break;
            
        case 8:
            val = GL_SRC_ALPHA_SATURATE;
            break;
            
        default:
            val = 0;
            break;
    }
}

int testApp::getBlendType(int s) {
    
    int val;
    val = 0;
    
    //GL BLEND TYPE
    switch (s) {
            
        case GL_ZERO:
            val = 0;
            break;
            
        case GL_ONE:
            val = 1;
            break;
            
        case GL_DST_COLOR:
            val = 2;
            break;
            
        case GL_ONE_MINUS_DST_COLOR:
            val = 3;
            break;
            
        case GL_SRC_ALPHA:
            val = 4;
            break;
            
        case GL_ONE_MINUS_SRC_ALPHA:
            val = 5;
            break;
            
        case GL_DST_ALPHA:
            val = 6;
            break;
            
        case GL_ONE_MINUS_DST_ALPHA:
            val = 7;
            break;
            
        case GL_SRC_ALPHA_SATURATE:
            val = 8;
            break;
            
        default:
            val = 0;
            break;
    }
    
    return val;
}

//--------------------------------------------------------------
void testApp::draw(){

    gui.draw();
    
    m_emitter.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key>='0' && key<='9') {
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
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	if (doUseMouse && !gui.isOn()) 
	{
		m_emitter.sourcePosition.x = x;
		m_emitter.sourcePosition.y = y;
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	if (doUseMouse && !gui.isOn()) 
	{
		m_emitter.sourcePosition.x = x;
		m_emitter.sourcePosition.y = y;
	}
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

void testApp::saveToParticleXML() {
    
	
	//Open the Open File Dialog
	ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a Folder", true); 
	ofDirectory targetDirectory(ofToDataPath("myParticles", true));
	//Check if the user opened a file
	if (openFileResult.bSuccess){
		
		ofLogVerbose("User selected a file");
		
		//We have a file, check it and process it
		ofFile file (openFileResult.getPath());
		if (file.isDirectory()) {
			ofDirectory newTarget(file.path());
			targetDirectory = newTarget;
		}
		
	}else {
		ofLogVerbose("User hit cancel");
		return;
	}
	//targetDirectory.path()+
	ofFile folder(targetDirectory.path());
    string xmlFilename = targetDirectory.path() + "/" + folder.getBaseName() + ".pex";
	//"/new_settings.pex";
	
	XML.saveFile(xmlFilename + ".bak");
	
	XML.clear();	// clear cause we are building a new xml file
	
	XML.addTag("particleEmitterConfig");
	XML.pushTag("particleEmitterConfig");
        
    XML.addTag("texture");
    XML.addAttribute("texture", "name", m_emitter.getTextureName(), 0);
    XML.pushTag("texture");
    XML.popTag();
    
    XML.addTag("sourcePosition");
    XML.addAttribute("sourcePosition", "x", m_emitter.sourcePosition.x, 0);
    XML.addAttribute("sourcePosition", "y", m_emitter.sourcePosition.y, 0);
    XML.pushTag("sourcePosition");
    XML.popTag();
    
    XML.addTag("sourcePositionVariance");
    XML.addAttribute("sourcePositionVariance", "x", m_emitter.sourcePositionVariance.x, 0);
    XML.addAttribute("sourcePositionVariance", "y", m_emitter.sourcePositionVariance.y, 0);
    XML.pushTag("sourcePositionVariance");
    XML.popTag();
    
    XML.addTag("speed");
    XML.addAttribute("speed", "value", m_emitter.speed, 0);
    XML.pushTag("speed");
    XML.popTag();
    
    XML.addTag("speedVariance");
    XML.addAttribute("speedVariance", "value", m_emitter.speedVariance, 0);
    XML.pushTag("speedVariance");
    XML.popTag();
    
    XML.addTag("angle");
    XML.addAttribute("angle", "value", m_emitter.angle, 0);
    XML.pushTag("angle");
    XML.popTag();
    
    XML.addTag("angleVariance");
    XML.addAttribute("angleVariance", "value", m_emitter.angleVariance, 0);
    XML.pushTag("angleVariance");
    XML.popTag();
    
    XML.addTag("particleLifeSpan");
    XML.addAttribute("particleLifeSpan", "value", m_emitter.particleLifespan, 0);
    XML.pushTag("particleLifeSpan");
    XML.popTag();
    
    XML.addTag("particleLifespanVariance");
    XML.addAttribute("particleLifespanVariance", "value", m_emitter.particleLifespanVariance, 0);
    XML.pushTag("particleLifespanVariance");
    XML.popTag();
    
    XML.addTag("gravity");
    XML.addAttribute("gravity", "x", m_emitter.gravity.x, 0);
    XML.addAttribute("gravity", "y", m_emitter.gravity.y, 0);
    XML.pushTag("gravity");
    XML.popTag();
    
    XML.addTag("radialAcceleration");
    XML.addAttribute("radialAcceleration", "value", m_emitter.radialAcceleration, 0);
    XML.pushTag("radialAcceleration");
    XML.popTag();
    
    XML.addTag("tangentialAcceleration");
    XML.addAttribute("tangentialAcceleration", "value", m_emitter.tangentialAcceleration, 0);
    XML.pushTag("tangentialAcceleration");
    XML.popTag();
    
    XML.addTag("radialAccelVariance");
    XML.addAttribute("radialAccelVariance", "value", m_emitter.radialAccelVariance, 0);
    XML.pushTag("radialAccelVariance");
    XML.popTag();
    
    XML.addTag("tangentialAccelVariance");
    XML.addAttribute("tangentialAccelVariance", "value", m_emitter.tangentialAccelVariance, 0);
    XML.pushTag("tangentialAccelVariance");
    XML.popTag();
    
    XML.addTag("startColor");
    XML.addAttribute("startColor", "red", m_emitter.startColor.r, 0);
    XML.addAttribute("startColor", "green", m_emitter.startColor.g, 0);
    XML.addAttribute("startColor", "blue", m_emitter.startColor.b, 0);
    XML.addAttribute("startColor", "alpha", m_emitter.startColor.a, 0);
    XML.pushTag("startColor");
    XML.popTag();
    
    XML.addTag("startColorVariance");
    XML.addAttribute("startColorVariance", "red", m_emitter.startColorVariance.r, 0);
    XML.addAttribute("startColorVariance", "green", m_emitter.startColorVariance.g, 0);
    XML.addAttribute("startColorVariance", "blue", m_emitter.startColorVariance.b, 0);
    XML.addAttribute("startColorVariance", "alpha", m_emitter.startColorVariance.a, 0);
    XML.pushTag("startColorVariance");
    XML.popTag();
    
    XML.addTag("finishColor");
    XML.addAttribute("finishColor", "red", m_emitter.finishColor.r, 0);
    XML.addAttribute("finishColor", "green", m_emitter.finishColor.g, 0);
    XML.addAttribute("finishColor", "blue", m_emitter.finishColor.b, 0);
    XML.addAttribute("finishColor", "alpha", m_emitter.finishColor.a, 0);
    XML.pushTag("finishColor");
    XML.popTag();
    
    XML.addTag("finishColorVariance");
    XML.addAttribute("finishColorVariance", "red", m_emitter.finishColorVariance.r, 0);
    XML.addAttribute("finishColorVariance", "green", m_emitter.finishColorVariance.g, 0);
    XML.addAttribute("finishColorVariance", "blue", m_emitter.finishColorVariance.b, 0);
    XML.addAttribute("finishColorVariance", "alpha", m_emitter.finishColorVariance.a, 0);
    XML.pushTag("finishColorVariance");
    XML.popTag();
    
    XML.addTag("maxParticles");
    XML.addAttribute("maxParticles", "value", m_emitter.maxParticles, 0);
    XML.pushTag("maxParticles");
    XML.popTag();
    
    XML.addTag("startParticleSize");
    XML.addAttribute("startParticleSize", "value", m_emitter.startParticleSize, 0);
    XML.pushTag("startParticleSize");
    XML.popTag();
    
    XML.addTag("startParticleSizeVariance");
    XML.addAttribute("startParticleSizeVariance", "value", m_emitter.startParticleSizeVariance, 0);
    XML.pushTag("startParticleSizeVariance");
    XML.popTag();
    
    XML.addTag("finishParticleSize");
    XML.addAttribute("finishParticleSize", "value", m_emitter.finishParticleSize, 0);
    XML.pushTag("finishParticleSize");
    XML.popTag();
    
    XML.addTag("finishParticleSizeVariance");
    XML.addAttribute("finishParticleSizeVariance", "value", m_emitter.finishParticleSizeVariance, 0);
    XML.pushTag("finishParticleSizeVariance");
    XML.popTag();
    
    XML.addTag("duration");
    XML.addAttribute("duration", "value", m_emitter.duration, 0);
    XML.pushTag("duration");
    XML.popTag();
    
    XML.addTag("emitterType");
    XML.addAttribute("emitterType", "value", m_emitter.emitterType, 0);
    XML.pushTag("emitterType");
    XML.popTag();
    
    XML.addTag("maxRadius");
    XML.addAttribute("maxRadius", "value", m_emitter.maxRadius, 0);
    XML.pushTag("maxRadius");
    XML.popTag();
    
    XML.addTag("maxRadiusVariance");
    XML.addAttribute("maxRadiusVariance", "value", m_emitter.maxRadiusVariance, 0);
    XML.pushTag("maxRadiusVariance");
    XML.popTag();
    
    XML.addTag("minRadius");
    XML.addAttribute("minRadius", "value", m_emitter.minRadius, 0);
    XML.pushTag("minRadius");
    XML.popTag();
    
    XML.addTag("rotatePerSecond");
    XML.addAttribute("rotatePerSecond", "value", m_emitter.rotatePerSecond, 0);
    XML.pushTag("rotatePerSecond");
    XML.popTag();
    
    XML.addTag("rotatePerSecondVariance");
    XML.addAttribute("rotatePerSecondVariance", "value", m_emitter.rotatePerSecondVariance, 0);
    XML.pushTag("rotatePerSecondVariance");
    XML.popTag();
    
    XML.addTag("blendFuncSource");
    XML.addAttribute("blendFuncSource", "value", m_emitter.blendFuncSource, 0);
    XML.pushTag("blendFuncSource");
    XML.popTag();
    
    XML.addTag("blendFuncDestination");
    XML.addAttribute("blendFuncDestination", "value", m_emitter.blendFuncDestination, 0);
    XML.pushTag("blendFuncDestination");
    XML.popTag();
        
	XML.popTag();
	
	XML.saveFile(xmlFilename);
	//	if(doSaveBackup) 
	//ofLog(OF_LOG_VERBOSE, "ofxSimpleGuiPage::saveToXML: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
}

void testApp::loadFromParticleXML(string xmlname) {
    
	ofDirectory dir = ofToDataPath("sampleParticles", true);

	
    if ( !m_emitter.loadFromXml( xmlname, dir ) )
	{
		ofLog( OF_LOG_ERROR, "testApp::setup() - failed to load emitter config" );
	}
    
    m_emitter.sourcePosition.x = ofGetWidth()/2;
    m_emitter.sourcePosition.y = ofGetHeight()/2;
    
    m_emitter.gravity.y = m_emitter.gravity.y * -1; //FIX for y axis
}
