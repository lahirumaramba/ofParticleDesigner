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

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxParticleEmitter.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    ofxParticleEmitter m_emitter;
        
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
    
    GLfloat			maxRadius;						// Max radius at which particles are drawn when rotating
	GLfloat			maxRadiusVariance;				// Variance of the maxRadius
	GLfloat			radiusSpeed;					// The speed at which a particle moves from maxRadius to minRadius
	GLfloat			minRadius;						// Radius from source below which a particle dies
	GLfloat			rotatePerSecond;				// Number of degrees to rotate a particle around the source position per second
	GLfloat			rotatePerSecondVariance;		// Variance in degrees for rotatePerSecond
    
    bool            bPlay, bSaveParticleXML, bNormal, bAddictive;
    bool            circle1, circle2, circle3, particle1, particle2, particle3, particle4, particle5, particle6;
    bool            circles, drugs, fire, sun, waterfall, jellyfish;
    
    int             blendSrc, blendDst;
    
    ofxXmlSettings  XML;
    
    void            setBlendType(int s, int &val);
    int             getBlendType(int s);
    void            saveToParticleXML();
    void            loadFromParticleXML(string xmlname);
};
