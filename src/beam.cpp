#include "beam.h"

beam::beam(ofPoint _point_low, ofPoint _point_high, int _trig_thresh, float _dist_thresh){
    point_low = _point_low;
    point_high = _point_high;
    trig.thresh = _trig_thresh;
    dist.thresh = _dist_thresh;
    updateBeam();
}

//---------------------------
void beam::setBeamLow(ofPoint _point_low){
    point_low = _point_low;
    updateBeam();
}

//---------------------------
void beam::setBeamHigh(ofPoint _point_high){
    point_high = _point_high;
    updateBeam();
}

//---------------------------
void beam::setTimeThresh(int _trig_thresh){
    trig.thresh = _trig_thresh;
}

//---------------------------
void beam::setDistThresh(float _dist_thresh){
    dist.thresh = _dist_thresh;
}

//---------------------------
float beam::distance(ofPoint current_point){
    vec_projection = (current_point - point_low).dot(vec_norm);
    dist.current = (vec_projection * vec_norm + point_low).distance(current_point);
    if(dist.current <dist.min){
        dist.min = dist.current;
        closest_point = current_point;
    }
    return(dist.current);
}

//---------------------------
void beam::set(){
        trig.count = trig.thresh;
        isON = true;
        if (vec_projection < 0){
            height = 0;
        }
        else if (closest_point.distance(point_low) > dist_config_points){
            height = 1;
        }
        else {
            height = (closest_point.distance(point_low))/dist_config_points;
        }
}

//---------------------------
void beam::reset(){
    //value is only reset if no beam has been detected for trig.thresh frames
    //this prevents glitches or accidental successive triggers
    if(trig.count > 0) trig.count--;
    else isON = false;
    dist.min = dist.thresh;
}

//---------------------------
void beam::updateBeam(){
    vec_norm = (point_high - point_low).getNormalized(); //normalized beam vector
    dist_config_points = point_high.distance(point_low); //distance between configuration points
}