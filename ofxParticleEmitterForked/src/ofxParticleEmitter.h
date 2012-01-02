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

// Structure that defines the elements which make up a color
typedef struct {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat alpha;
} Color4f;

// Structure that defines a vector using x and y
typedef struct {
	GLfloat x;
	GLfloat y;
} Vector2f;

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
	Color4f color;
} PointSprite;

// Structure used to hold particle specific information
typedef struct 
{
	Vector2f	position;
	Vector2f	direction;
    Vector2f	startPos;
	Color4f		color;
	Color4f		deltaColor;
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

// Return a Color4f structure populated with 1.0's
static const Color4f Color4fOnes = {1.0f, 1.0f, 1.0f, 1.0f};

// Return a zero populated Vector2f
static const Vector2f Vector2fZero = {0.0f, 0.0f};

// Return a populated Vector2d structure from the floats passed in
static inline Vector2f Vector2fMake(GLfloat x, GLfloat y) {
	Vector2f r; r.x = x; r.y = y;
	return r;
}

// Return a Color4f structure populated with the color values passed in
static inline Color4f Color4fMake(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	Color4f c; c.red = red; c.green = green; c.blue = blue; c.alpha = alpha;
	return c;
}

// Return a Vector2f containing v multiplied by s
static inline Vector2f Vector2fMultiply(Vector2f v, GLfloat s) {
	Vector2f r; 
	r.x = v.x * s;
	r.y = v.y * s;
	return r;
}

// Return a Vector2f containing v1 + v2
static inline Vector2f Vector2fAdd(Vector2f v1, Vector2f v2) {
	Vector2f r; 
	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	return r;
}

// Return a Vector2f containing v1 - v2
static inline Vector2f Vector2fSub(Vector2f v1, Vector2f v2) {
	Vector2f r; 
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	return r;
}

// Return the dot product of v1 and v2
static inline GLfloat Vector2fDot(Vector2f v1, Vector2f v2) {
	return (GLfloat) v1.x * v2.x + v1.y * v2.y;
}

// Return the length of the vector v
static inline GLfloat Vector2fLength(Vector2f v) {
	return (GLfloat) sqrtf(Vector2fDot(v, v));
}

// Return a Vector2f containing a normalized vector v
static inline Vector2f Vector2fNormalize(Vector2f v) {
	return Vector2fMultiply(v, 1.0f/Vector2fLength(v));
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
	Vector2f		sourcePosition, sourcePositionVariance;			
	GLfloat			angle, angleVariance;								
	GLfloat			speed, speedVariance;	
	GLfloat			radialAcceleration, tangentialAcceleration;
	GLfloat			radialAccelVariance, tangentialAccelVariance;
	Vector2f		gravity;	
	GLfloat			particleLifespan, particleLifespanVariance;			
	Color4f			startColor, startColorVariance;						
	Color4f			finishColor, finishColorVariance;
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