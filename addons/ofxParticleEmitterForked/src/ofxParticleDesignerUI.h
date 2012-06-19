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
private:
	ofxParticleEmitter emitter;
	
    int				emitterType;
	ofVec2f		sourcePosition, sourcePositionVariance;			
	GLfloat			angle, angleVariance;								
	GLfloat			speed, speedVariance;	
	GLfloat			radialAcceleration, tangentialAcceleration;
	GLfloat			radialAccelVariance, tangentialAccelVariance;
	ofVec2f		gravity;	
	GLfloat			particleLifespan, particleLifespanVariance;
	ofFloatColor			startColor, startColorVariance;						
	ofFloatColor			finishColor, finishColorVariance;
	GLfloat			startParticleSize, startParticleSizeVariance;
	GLfloat			finishParticleSize, finishParticleSizeVariance;
	GLint			maxParticles;
	GLint			particleCount;
	GLfloat			duration;
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
	ofDirectory sampleDirectory;
	
	ofxSimpleGuiToo gui;
};
