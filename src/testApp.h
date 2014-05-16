#pragma once

#include "ofMain.h"
#include "beam.h"
#include "laserTracker.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

#define HOST "localhost"
#define PORT1 12345
#define PORT2 12346
#define PORT3 12347

#define NUM_BEAMS 3

//--------------------------------------------------------
class testApp : public ofBaseApp{
	
public:
    
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
    void updateXML(int beam, bool bLow);
    
    ofxXmlSettings			XML;
	ofxOscSender			sender;
    ofxCvContourFinder		contourFinder;
    
    laserTracker            myTracker;
    beam**                  myBeam;
    
    ofPoint                 currentPoint;
    
    int						pixels;
    int                     trig_thresh;
    float                   dist_thresh;
	
};

