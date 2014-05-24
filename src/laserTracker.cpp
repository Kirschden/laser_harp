#include "laserTracker.h"

//---------------------------
void laserTracker::setup(){
    
    vidGrabber.setDeviceID(DEVICE_ID);
	vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(320,240);
	
    colorImg.allocate(320,240);
	greyImage.allocate(320,240);
	greyBg.allocate(320,240);
    red.allocate(320,240);
	green.allocate(320,240);
	blue.allocate(320,240);
	binaryOut.allocate(320,240);
	
	bLearnBg = true; // use current frame as background
    bRemoveBg = true; // remove background image
	greyThresh = 80;
    
    //the reflected laser will cause saturation in the image
    //set these values for the current lighting situation
    //for low ambient lighting, setting R, G, and B thresh to max (254) will easily remove any background and cleanly detect the lasers
    //for higher ambient lighting, lower B and G thresh to allow for larger contours
    redThresh = 254;
    blueThresh = 0;
    greenThresh = 0;
}

//---------------------------
void laserTracker::update(){
    
    vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();
	if (bNewFrame){
		
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		colorImg.convertToGrayscalePlanarImages(red, green, blue);
        
        red.threshold(redThresh);
        green.threshold(greenThresh);
        blue.threshold(blueThresh);
        
        binaryOut = red;
        binaryOut *= green;
        binaryOut *= blue;
        
        greyImage = colorImg;
        
		if (bLearnBg){
			greyBg = greyImage;
			bLearnBg = false;
		}
        
        if(bRemoveBg){
            greyImage -= greyBg;
            greyImage.threshold(greyThresh);
            binaryOut *= greyImage;
        }
    }
}

//---------------------------
void laserTracker::draw(){
    
	colorImg.draw(20,40);
    greyImage.draw(360,40);
	binaryOut.draw(700,40);
    
    //report:
	ofSetHexColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "toggle bg subtraction: x\npress ' ' to capture bg\nbg threshold: %i (press: -/+)\nred threshold: %i (press r/R)\ngreen threshold: %i (press g/G)\nblue threshold: %i (press b/B)", greyThresh, redThresh, greenThresh, blueThresh);
	ofDrawBitmapString(reportStr,20, 310);
    
}

//---------------------------
bool laserTracker::keyPressed(int key){
    
    bool bKey = false;
    switch (key){
        case ' ':
			bLearnBg = true;
            bKey = true;
			break;
        case 'x':
			bRemoveBg = !bRemoveBg;
            bKey = true;
            break;
		case '=':
			greyThresh ++;
			if (greyThresh > 255) greyThresh = 255;
            bKey = true;
			break;
		case '-':
			greyThresh --;
			if (greyThresh < 0) greyThresh = 0;
            bKey = true;
			break;
        case 'R':
			redThresh ++;
			if (redThresh > 255) redThresh = 255;
            bKey = true;
			break;
		case 'r':
			redThresh --;
			if (redThresh < 0) redThresh = 0;
            bKey = true;
			break;
        case 'G':
			greenThresh ++;
			if (greenThresh > 255) greenThresh = 255;
            bKey = true;
			break;
		case 'g':
			greenThresh --;
			if (greenThresh < 0) greenThresh = 0;
            bKey = true;
			break;
        case 'B':
			blueThresh ++;
			if (blueThresh > 255) blueThresh = 255;
            bKey = true;
			break;
		case 'b':
			blueThresh --;
			if (blueThresh < 0) blueThresh = 0;
            bKey = true;
			break;
    }
    return(bKey);
}
