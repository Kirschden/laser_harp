#ifndef _LASER_TRACKER_H
#define _LASER_TRACKER_H

#include "ofMain.h"
#include "ofxOpenCv.h"

#define DEVICE_ID 2

class laserTracker{
    
public:
    
    void setup();
    void update();
    void draw();
    bool keyPressed(int key);
    
    ofxCvGrayscaleImage		binaryOut;
    bool                    bNewFrame;
    
private:
    
    ofVideoGrabber			vidGrabber;
	
	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	greyImage;
	ofxCvGrayscaleImage 	greyBg;
	
	ofxCvGrayscaleImage		red;
	ofxCvGrayscaleImage		green;
	ofxCvGrayscaleImage		blue;
    
    int						greyThresh;
    int                     redThresh;
    int                     greenThresh;
    int                     blueThresh;
    
	bool					bLearnBg;
    bool                    bRemoveBg;
    
};

#endif