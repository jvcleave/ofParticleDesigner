/*
 *  ofxParticleDesignerUI.cpp
 *  ofParticleDesigner
 *
 *  Created by Van Cleave, Jason on 6/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxParticleDesignerUI.h"

ofxParticleDesignerUI::ofxParticleDesignerUI()
{
	pexID = 0;
	textureID = 0;
	currentTextureID = 0;
	currentPexID = 0;
	
	doUseMouse = false;
	doSaveParticleXML = false;
    speed = 0.0;
    duration = -1.0;
}


void ofxParticleDesignerUI::setup()
{

	
	sampleDirectory.open(ofToDataPath("sampleParticles", true));
	sampleDirectory.listDir();
	vector<ofFile> files = sampleDirectory.getFiles();
	
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
	

    loadSample();
	createGUI();
	
}

void ofxParticleDesignerUI::createGUI()
{
	//---------- SETTINGS ---------------
	gui.addTitle("Particle Settings");
    
	//gui.addToggle("Play", doPlay);
    gui.addToggle("Use Mouse", doUseMouse);
    gui.addSlider("Source Pos X", emitter.sourcePosition.x, 0.0, ofGetWidth());
    gui.addSlider("Source Pos X Var", emitter.sourcePositionVariance.x, 0.0, ofGetWidth());
    gui.addSlider("Source Pos Y", emitter.sourcePosition.y, 0.0, ofGetHeight());
    gui.addSlider("Source Pos Y Var", emitter.sourcePositionVariance.y, 0.0, ofGetHeight());
    
    gui.addSlider("Angle", emitter.angle, 0.0, 360);
    gui.addSlider("Angle Var", emitter.angleVariance, 0.0, 360);
    
    gui.addSlider("LifeSpan", emitter.particleLifespan, 0.000, 10.000);
    gui.addSlider("LifeSpan Var", emitter.particleLifespanVariance, 0.000, 10.000);
    
    gui.addSlider("Start Size", emitter.startParticleSize, 0, 512);
    gui.addSlider("Start Size Var", emitter.startParticleSizeVariance, 0, 512);
    gui.addSlider("Finish Size", emitter.finishParticleSize, 0, 512);
    gui.addSlider("Finish Size Var", emitter.finishParticleSizeVariance, 0, 512);
    
    //gui.addSlider("Max Particles", emitter.maxParticles, 0, 1000);
    //gui.addSlider("Particle Count", emitter.particleCount, 0, 1000);
    
    //--------- TYPE --------------------
    gui.addTitle("Type");
    string titleArray[] = {"Gravity","Radial"};
	gui.addComboBox("Emitter Type", emitter.emitterType, 2, titleArray);
    
    gui.addTitle("Gravity");
    gravityControls.push_back(&gui.addSlider("Speed", emitter.speed, 0.0, 1000));
	gravityControls.push_back(&gui.addSlider("Speed Var", emitter.speedVariance, 0.0, 1000));
    
	gravityControls.push_back(&gui.addSlider("Radial Acc", emitter.radialAcceleration, -1000.000, 1000.000));
    gravityControls.push_back(&gui.addSlider("Radial Acc Var", emitter.radialAccelVariance, -1000.000, 1000.000));
    
    gravityControls.push_back(&gui.addSlider("Tan Acc", emitter.tangentialAcceleration, -1000.000, 1000.000));
    gravityControls.push_back(&gui.addSlider("Tan Acc Var", emitter.tangentialAccelVariance, -1000.000, 1000.000));
  
    gravityControls.push_back(&gui.addSlider("Gravity X", emitter.gravity.x, -3000, 3000));
    gravityControls.push_back(&gui.addSlider("Gravity Y", emitter.gravity.y, -3000, 3000));

    gui.addTitle("Radial");
    radialControls.push_back(&gui.addSlider("Max Radius", emitter.maxRadius, 0, 480));
    radialControls.push_back(&gui.addSlider("Max Radius Var", emitter.maxRadiusVariance, 0, 480));
    radialControls.push_back(&gui.addSlider("Min Radius", emitter.minRadius, 0, 480));
    
    radialControls.push_back(&gui.addSlider("Deg. Per Sec", emitter.rotatePerSecond, 0.0, 360));
    radialControls.push_back(&gui.addSlider("Deg. Per Sec Var", emitter.rotatePerSecondVariance, 0.0, 360));
    
    radialControls.push_back(&gui.addSlider("Radius Speed", emitter.radiusSpeed, 0, 1000));
    
	//gui.addSlider("Duration", emitter.duration, -1.0, 200);
    
    //----------- COLOR ------------------
    gui.addPage("Color");
    gui.addTitle("Color");
	gui.addColorPicker("Start Color", &(emitter.startColor).r);
    gui.addColorPicker("Start Color Var", &(emitter.startColorVariance).r);
    gui.addColorPicker("End Color", &(emitter.finishColor).r);
    gui.addColorPicker("End Color Var", &(emitter.finishColorVariance).r);
    
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
	
	
	
	gui.addComboBox("TEXTURE FILE", textureID, textureFileNames.size(),  &textureFileNames[0]);
    gui.addComboBox("SOURCE", pexID, pexFileNames.size(),  &pexFileNames[0]);
    gui.setPage(1);
    gui.show();
	
    
    blendSrc = getBlendType(emitter.blendFuncSource);
    blendDst = getBlendType(emitter.blendFuncDestination);
}


void ofxParticleDesignerUI::loadSample()
{
		loadFromParticleXML( "circles.pex" );
		cout << "emitter.emitterType: " << emitter.emitterType << endl;
		//emitter.sourcePosition.x = ofGetWidth()/2;
		//emitter.sourcePosition.y = ofGetHeight()/2;
}

void ofxParticleDesignerUI::update()
{
	emitter.update();
    if (emitter.emitterType == EMITTER_TYPE_GRAVITY) 
	{
		toggleControls(radialControls, gravityControls);
	}else {
		toggleControls(gravityControls, radialControls);
	}

	if( isNormal )
	{
        //ofSetWindowTitle("Normal");
        isNormal = false;
        blendSrc = 4;
        blendDst = 5;
		if( isAddictive )
		{
			//ofSetWindowTitle("Addictive");
			isAddictive = false;
			blendDst = 1;
		}
    }
   if( doSaveParticleXML )
   {
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
		emitter.changeTexture(textureFileNames[currentTextureID]);
	}
	
    setBlendType(blendSrc, emitter.blendFuncSource);
    setBlendType(blendDst, emitter.blendFuncDestination);
	
}

void ofxParticleDesignerUI::draw()
{
	ofPushMatrix();
		ofPushStyle();
			emitter.draw();
			gui.draw();
		ofPopStyle();
	ofPopMatrix();
}

void ofxParticleDesignerUI::saveToParticleXML() {
    
	
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
    XML.addAttribute("texture", "name", emitter.getTextureName(), 0);
    XML.pushTag("texture");
    XML.popTag();
    
    XML.addTag("sourcePosition");
    XML.addAttribute("sourcePosition", "x", emitter.sourcePosition.x, 0);
    XML.addAttribute("sourcePosition", "y", emitter.sourcePosition.y, 0);
    XML.pushTag("sourcePosition");
    XML.popTag();
    
    XML.addTag("sourcePositionVariance");
    XML.addAttribute("sourcePositionVariance", "x", emitter.sourcePositionVariance.x, 0);
    XML.addAttribute("sourcePositionVariance", "y", emitter.sourcePositionVariance.y, 0);
    XML.pushTag("sourcePositionVariance");
    XML.popTag();
    
    XML.addTag("speed");
    XML.addAttribute("speed", "value", emitter.speed, 0);
    XML.pushTag("speed");
    XML.popTag();
    
    XML.addTag("speedVariance");
    XML.addAttribute("speedVariance", "value", emitter.speedVariance, 0);
    XML.pushTag("speedVariance");
    XML.popTag();
    
    XML.addTag("angle");
    XML.addAttribute("angle", "value", emitter.angle, 0);
    XML.pushTag("angle");
    XML.popTag();
    
    XML.addTag("angleVariance");
    XML.addAttribute("angleVariance", "value", emitter.angleVariance, 0);
    XML.pushTag("angleVariance");
    XML.popTag();
    
    XML.addTag("particleLifeSpan");
    XML.addAttribute("particleLifeSpan", "value", emitter.particleLifespan, 0);
    XML.pushTag("particleLifeSpan");
    XML.popTag();
    
    XML.addTag("particleLifespanVariance");
    XML.addAttribute("particleLifespanVariance", "value", emitter.particleLifespanVariance, 0);
    XML.pushTag("particleLifespanVariance");
    XML.popTag();
    
    XML.addTag("gravity");
    XML.addAttribute("gravity", "x", emitter.gravity.x, 0);
    XML.addAttribute("gravity", "y", emitter.gravity.y, 0);
    XML.pushTag("gravity");
    XML.popTag();
    
    XML.addTag("radialAcceleration");
    XML.addAttribute("radialAcceleration", "value", emitter.radialAcceleration, 0);
    XML.pushTag("radialAcceleration");
    XML.popTag();
    
    XML.addTag("tangentialAcceleration");
    XML.addAttribute("tangentialAcceleration", "value", emitter.tangentialAcceleration, 0);
    XML.pushTag("tangentialAcceleration");
    XML.popTag();
    
    XML.addTag("radialAccelVariance");
    XML.addAttribute("radialAccelVariance", "value", emitter.radialAccelVariance, 0);
    XML.pushTag("radialAccelVariance");
    XML.popTag();
    
    XML.addTag("tangentialAccelVariance");
    XML.addAttribute("tangentialAccelVariance", "value", emitter.tangentialAccelVariance, 0);
    XML.pushTag("tangentialAccelVariance");
    XML.popTag();
    
    XML.addTag("startColor");
    XML.addAttribute("startColor", "red", emitter.startColor.r, 0);
    XML.addAttribute("startColor", "green", emitter.startColor.g, 0);
    XML.addAttribute("startColor", "blue", emitter.startColor.b, 0);
    XML.addAttribute("startColor", "alpha", emitter.startColor.a, 0);
    XML.pushTag("startColor");
    XML.popTag();
    
    XML.addTag("startColorVariance");
    XML.addAttribute("startColorVariance", "red", emitter.startColorVariance.r, 0);
    XML.addAttribute("startColorVariance", "green", emitter.startColorVariance.g, 0);
    XML.addAttribute("startColorVariance", "blue", emitter.startColorVariance.b, 0);
    XML.addAttribute("startColorVariance", "alpha", emitter.startColorVariance.a, 0);
    XML.pushTag("startColorVariance");
    XML.popTag();
    
    XML.addTag("finishColor");
    XML.addAttribute("finishColor", "red", emitter.finishColor.r, 0);
    XML.addAttribute("finishColor", "green", emitter.finishColor.g, 0);
    XML.addAttribute("finishColor", "blue", emitter.finishColor.b, 0);
    XML.addAttribute("finishColor", "alpha", emitter.finishColor.a, 0);
    XML.pushTag("finishColor");
    XML.popTag();
    
    XML.addTag("finishColorVariance");
    XML.addAttribute("finishColorVariance", "red", emitter.finishColorVariance.r, 0);
    XML.addAttribute("finishColorVariance", "green", emitter.finishColorVariance.g, 0);
    XML.addAttribute("finishColorVariance", "blue", emitter.finishColorVariance.b, 0);
    XML.addAttribute("finishColorVariance", "alpha", emitter.finishColorVariance.a, 0);
    XML.pushTag("finishColorVariance");
    XML.popTag();
    
    XML.addTag("maxParticles");
    XML.addAttribute("maxParticles", "value", emitter.maxParticles, 0);
    XML.pushTag("maxParticles");
    XML.popTag();
    
    XML.addTag("startParticleSize");
    XML.addAttribute("startParticleSize", "value", emitter.startParticleSize, 0);
    XML.pushTag("startParticleSize");
    XML.popTag();
    
    XML.addTag("startParticleSizeVariance");
    XML.addAttribute("startParticleSizeVariance", "value", emitter.startParticleSizeVariance, 0);
    XML.pushTag("startParticleSizeVariance");
    XML.popTag();
    
    XML.addTag("finishParticleSize");
    XML.addAttribute("finishParticleSize", "value", emitter.finishParticleSize, 0);
    XML.pushTag("finishParticleSize");
    XML.popTag();
    
    XML.addTag("finishParticleSizeVariance");
    XML.addAttribute("finishParticleSizeVariance", "value", emitter.finishParticleSizeVariance, 0);
    XML.pushTag("finishParticleSizeVariance");
    XML.popTag();
    
    XML.addTag("duration");
    XML.addAttribute("duration", "value", emitter.duration, 0);
    XML.pushTag("duration");
    XML.popTag();
    
    XML.addTag("emitterType");
    XML.addAttribute("emitterType", "value", emitter.emitterType, 0);
    XML.pushTag("emitterType");
    XML.popTag();
    
    XML.addTag("maxRadius");
    XML.addAttribute("maxRadius", "value", emitter.maxRadius, 0);
    XML.pushTag("maxRadius");
    XML.popTag();
    
    XML.addTag("maxRadiusVariance");
    XML.addAttribute("maxRadiusVariance", "value", emitter.maxRadiusVariance, 0);
    XML.pushTag("maxRadiusVariance");
    XML.popTag();
    
    XML.addTag("minRadius");
    XML.addAttribute("minRadius", "value", emitter.minRadius, 0);
    XML.pushTag("minRadius");
    XML.popTag();
    
    XML.addTag("rotatePerSecond");
    XML.addAttribute("rotatePerSecond", "value", emitter.rotatePerSecond, 0);
    XML.pushTag("rotatePerSecond");
    XML.popTag();
    
    XML.addTag("rotatePerSecondVariance");
    XML.addAttribute("rotatePerSecondVariance", "value", emitter.rotatePerSecondVariance, 0);
    XML.pushTag("rotatePerSecondVariance");
    XML.popTag();
    
    XML.addTag("blendFuncSource");
    XML.addAttribute("blendFuncSource", "value", emitter.blendFuncSource, 0);
    XML.pushTag("blendFuncSource");
    XML.popTag();
    
    XML.addTag("blendFuncDestination");
    XML.addAttribute("blendFuncDestination", "value", emitter.blendFuncDestination, 0);
    XML.pushTag("blendFuncDestination");
    XML.popTag();
	
	XML.popTag();
	
	XML.saveFile(xmlFilename);
	//	if(doSaveBackup) 
	//ofLog(OF_LOG_VERBOSE, "ofxSimpleGuiPage::saveToXML: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
}

void ofxParticleDesignerUI::loadFromParticleXML(string xmlname) {
    
	
    if ( !emitter.loadFromXml( xmlname, sampleDirectory ) )
	{
		ofLog( OF_LOG_ERROR, "ofxParticleDesignerUI::setup() - failed to load emitter config" );
	}
    
    emitter.sourcePosition.x = ofGetWidth()/2;
    emitter.sourcePosition.y = ofGetHeight()/2;
    
    emitter.gravity.y = emitter.gravity.y * -1; //FIX for y axis
}

void ofxParticleDesignerUI::onMousePressed(int x, int y)
{
	if (doUseMouse && !gui.isOn()) 
	{
		emitter.sourcePosition.x = x;
		emitter.sourcePosition.y = y;
	}
}

void ofxParticleDesignerUI::onMouseDragged(int x, int y)
{
	if (doUseMouse && !gui.isOn()) 
	{
		emitter.sourcePosition.x = x;
		emitter.sourcePosition.y = y;
	}
}

void ofxParticleDesignerUI::onKeyPressed(int key)
{
    
    if(key>='0' && key<='9') 
	{
		gui.setPage(key - '0');
		gui.show();
	} else 
	{
		 switch(key)
			{
				case ' ' :	gui.toggleDraw();			break;
				case '[' :	gui.prevPage();				break;
				case ']' :	gui.nextPage();				break;
				case 'p' :	gui.nextPageWithBlank();	break;
				case 'm' :	doUseMouse = !doUseMouse;	break;
				case 's' :	doSaveParticleXML = true;	break;
			 }
	}
	 
}
void ofxParticleDesignerUI::setBlendType(int s, int &val) {
    
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

int ofxParticleDesignerUI::getBlendType(int s) {
    
    int val;
    val = 0;
    
    //GL BLEND TYPE
    switch (s) {
            
        case GL_ZERO:
            val = GL_ZERO; // 0
            break;
            
        case GL_ONE:
            val = GL_ONE; // 1
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

void ofxParticleDesignerUI::toggleControls(vector<ofxSimpleGuiControl*> controlsToHide, vector<ofxSimpleGuiControl*> controlsToShow)
{
	for (int i=0; i<controlsToHide.size(); i++) {
		controlsToHide[i]->isHidden = true;
	}
	for (int i=0; i<controlsToShow.size(); i++) {
		controlsToShow[i]->isHidden = false;
	}
}