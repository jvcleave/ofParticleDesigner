/*
 *  ofxParticleDesignerUI.h
 *  ofParticleDesigner
 *
 *  Created by Van Cleave, Jason on 6/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxParticleEmitter.h"
#include "ofxSimpleGuiToo.h"
enum EmitterType {
	EMITTER_TYPE_GRAVITY = 0,
	EMITTER_TYPE_RADIAL = 1
};
class ofxParticleDesignerUI
{
	
public:
	ofxParticleDesignerUI();
	void setup();
	void update();
	void draw();
	void loadSample();
	void onMouseDragged(int x, int y);
	void onMousePressed(int x, int y);
	void onKeyPressed(int key);
	void createGUI();
	void addDirectory(string filePath);
private:
	ofxParticleEmitter emitter;
	
    EmitterType				emitterType;
	ofVec2f			sourcePosition, sourcePositionVariance;			
	GLfloat			angle, angleVariance;								
	GLfloat			speed, speedVariance;	
	GLfloat			radialAcceleration, tangentialAcceleration;
	GLfloat			radialAccelVariance, tangentialAccelVariance;
	ofVec2f			gravity;	
	GLfloat			particleLifespan, particleLifespanVariance;
	ofFloatColor	startColor, startColorVariance;						
	ofFloatColor	finishColor, finishColorVariance;
	GLfloat			startParticleSize, startParticleSizeVariance;
	GLfloat			finishParticleSize, finishParticleSizeVariance;
	GLint			maxParticles;
	GLint			particleCount;
	GLfloat			duration;
	GLfloat rotationStart, rotationStartVariance;
    GLfloat rotationEnd, rotationEndVariance;
	int				blendFuncSource, blendFuncDestination;
    
    GLfloat			maxRadius;						// Max radius at which particles are drawn when rotating
	GLfloat			maxRadiusVariance;				// Variance of the maxRadius
	GLfloat			radiusSpeed;					// The speed at which a particle moves from maxRadius to minRadius
	GLfloat			minRadius;						// Radius from source below which a particle dies
	GLfloat			rotatePerSecond;				// Number of degrees to rotate a particle around the source position per second
	GLfloat			rotatePerSecondVariance;		// Variance in degrees for rotatePerSecond
    
    bool            doSaveParticleXML, isNormal, isAddictive;
	
    
    int             blendSrc, blendDst;
    
    ofxXmlSettings  XML;
    
    void            setBlendType(int s, int &val);
    int             getBlendType(int s);
    void            saveToParticleXML();
    void            loadFromParticleXML(string xmlname);
	
	int pexID;
	int textureID;
	int currentTextureID;
	int currentPexID;
	bool doUseMouse;
	vector<string> pexFileNames;
	vector<string> textureFileNames;
	vector<ofDirectory> directories;
	ofxSimpleGuiToo gui;
	vector<ofxSimpleGuiControl*> gravityControls;
	vector<ofxSimpleGuiControl*> radialControls;
	void toggleControls(vector<ofxSimpleGuiControl*> controlsToHide, vector<ofxSimpleGuiControl*> controlsToShow);

};
