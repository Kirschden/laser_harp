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
    void    setDistThresh(float _dist_thresh);
    float   distance(){ return dist.current; }
    float   minDistance(){ return dist.min; }
    bool    isBeamOn(){ return isON; }
    float   beamHeight(){ return height; }
    float   distance(ofPoint current_point); // get the distance of a point from the beam
    void    set(); //update isON an height
    void    reset();
    
private:
    
    void    updateBeam();
    
    bool    isON; // is beam broken
    float   height; // position of object in beam
    float   dist_config_points; // distance between low and high config points
    float   vec_projection;
    ofPoint point_low; // config point
    ofPoint point_high; // config point
    ofPoint closest_point;
    ofVec2f vec_norm;
    timeTrigger trig;
    pixelDistance dist;
};

#endif