#ifndef _BEAM
#define _BEAM

#include "ofMain.h"

typedef struct
{
    int thresh;
    int count;
} timeTrigger;

typedef struct
{
    float current;
    float thresh;
    float min;
} pixelDistance;

class beam{
    
public:
    
    beam(ofPoint _point_low, ofPoint _point_high, int _trig_thresh, float _dist_thresh);
    
    void    setBeamLow(ofPoint _point_low); //set beam values for configuration point
    void    setBeamHigh(ofPoint _point_high); //set beam values for configuration point
    void    setTimeThresh(int _trig_thresh); //set beam-off trigger threshold: _trig_thresh frames/fps [time]
    void    setDistThresh(float _dist_thresh); //set minimum distance threshold between contour centre and beam line equation
    float   distance(){ return dist.current; } //returns distance of contour from beam and stores closes contour since last reset
    float   minDistance(){ return dist.min; } //returns distance of closes contour since last reset
    bool    isBeamOn(){ return isON; } //returns true if a contour is detected within distance threshold
    float   beamHeight(){ return height; } //returns 1 if closest contour is above the upper config point, 0 if below, or a linear correlation if in between
    float   distance(ofPoint current_point); // get the distance of a point from the beam
    void    set(); //update isON an height
    void    reset();
    
private:
    
    void    updateBeam();
    
    bool    isON; // is beam broken
    float   height; // position of object in beam
    float   dist_config_points; // distance between low and high config points
    float   vec_projection; // vecotor projection used to find distance from contour to beam
    ofPoint point_low; // config point
    ofPoint point_high; // config point
    ofPoint closest_point; // closest point since last reset
    ofVec2f vec_norm; // normalized beam vector
    timeTrigger trig;
    pixelDistance dist;
};

#endif