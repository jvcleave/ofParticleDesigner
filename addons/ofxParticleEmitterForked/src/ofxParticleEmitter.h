//
// ofxParticleEmitter.h
//
// Copyright (c) 2010 71Squared, ported to Openframeworks by Shawn Roske
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

#ifndef _OFX_PARTICLE_EMITTER
#define _OFX_PARTICLE_EMITTER

#include "ofMain.h"
#include "ofxXmlSettings.h"

// ------------------------------------------------------------------------
// Structures
// ------------------------------------------------------------------------





// Particle type
enum kParticleTypes 
{
	kParticleTypeGravity = 0,
	kParticleTypeRadial = 1
};

// Structure that holds the location and size for each point sprite
typedef struct 
{
	GLfloat x;
	GLfloat y;
	GLfloat size;
	ofFloatColor color;
} PointSprite;

// Structure used to hold particle specific information
typedef struct 
{
	ofVec2f	position;
	ofVec2f	direction;
    ofVec2f	startPos;
	ofFloatColor		color;
	ofFloatColor		deltaColor;
    GLfloat		radialAcceleration;
    GLfloat		tangentialAcceleration;
	GLfloat		radius;
	GLfloat		radiusDelta;
	GLfloat		angle;
	GLfloat		degreesPerSecond;
	GLfloat		particleSize;
	GLfloat		particleSizeDelta;
	GLfloat		timeToLive;
} Particle;

// ------------------------------------------------------------------------
// Macros
// ------------------------------------------------------------------------

// Macro which returns a random value between -1 and 1
#define RANDOM_MINUS_1_TO_1() (ofRandom( -1.0f, 1.0f ))

// Macro which returns a random number between 0 and 1
#define RANDOM_0_TO_1() (ofRandom( 0.0f, 1.0f ))

// Macro which converts degrees into radians
#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * PI)

// ------------------------------------------------------------------------
// Inline functions
// ------------------------------------------------------------------------

// Return a ofFloatColor structure populated with 1.0's
static const ofFloatColor ofColorOnes(1.0f, 1.0f, 1.0f, 1.0f);



// Return a ofVec2f containing a normalized vector v
static inline ofVec2f ofVec2fNormalize(ofVec2f v) {
	return v*1.0f/v.length();
}

#define MAXIMUM_UPDATE_RATE 90.0f	// The maximum number of updates that occur per frame

// ------------------------------------------------------------------------
// ofxParticleEmitter
// ------------------------------------------------------------------------

class ofxParticleEmitter 
{
	
public:
	
	ofxParticleEmitter();
	~ofxParticleEmitter();
	
	bool	loadFromXml( const std::string& filename );
	void	update();
	void	draw( int x = 0, int y = 0 );
	void	exit();
    string  getTextureName();
    void    changeTexture(string filename);

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

	// Particle ivars only used when a maxRadius value is provided.  These values are used for
	// the special purpose of creating the spinning portal emitter
	GLfloat			maxRadius;						// Max radius at which particles are drawn when rotating
	GLfloat			maxRadiusVariance;				// Variance of the maxRadius
	GLfloat			radiusSpeed;					// The speed at which a particle moves from maxRadius to minRadius
	GLfloat			minRadius;						// Radius from source below which a particle dies
	GLfloat			rotatePerSecond;				// Number of degrees to rotate a particle around the source position per second
	GLfloat			rotatePerSecondVariance;		// Variance in degrees for rotatePerSecond
	
protected:
	
	void	parseParticleConfig();
	void	setupArrays();
	
	void	stopParticleEmitter();
	bool	addParticle();
	void	initParticle( Particle* particle );
	
	void	drawTextures();
	void	drawPoints();
	void	drawPointsOES();
	
	ofxXmlSettings*	settings;

	ofImage*		texture;												
	ofTextureData	textureData;
    string          textureName;
	
	GLfloat			emissionRate;
	GLfloat			emitCounter;	
	GLfloat			elapsedTime;
	int				lastUpdateMillis;

	bool			active, useTexture;
	GLint			particleIndex;	// Stores the number of particles that are going to be rendered

	GLuint			verticesID;		// Holds the buffer name of the VBO that stores the color and vertices info for the particles
	Particle*		particles;		// Array of particles that hold the particle emitters particle details
	PointSprite*	vertices;		// Array of vertices and color information for each particle to be rendered
};

#endif