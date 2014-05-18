laser_harp
==========

The Laser Harp project consists of two applications, one developed in C++ using openFrameworks, and the other in Max MSP. With these applications, any webcam can be used to make a laser harp, no external hardware necessary (apart from laser diodes).

Demo video --> https://vimeo.com/95560794

openFrameworks

laserTracker detects the reflected beams through thresholding. In situations with low ambient lighting, a binary image made from high thresholding values in RGB components detects the lasers with no background noise. In higher ambient lighting situations, a binary image of the red component with a high threshold and background subtraction (toggle with x) gives a large enough contour for detection.
These values can all be played around with at run-time to best suit the current environment.

The beam class describes each beam based on two user input points. Ensure there is a large enough offset (< 15cm) between the camera and the laser. The user must break the beam in two different places (again with enough distance between the two points to allow for an accurate line description). These data points are collected when a key stroke is detected (see testApp.cpp for details) and stored in bin/data/config_points.xml. For each beam, an integer for note ON/OFF (beam broken/not broken) and a floating point value to describe hand-height in the beam are sent via OSC (UDP). The float is 0.0 below the lower user defined beam point, 1.0 above the higher of the two, and a value from 0.0 to 1.0 between the two points (linear relationship).

Max MSP

The UPD packet can control whatever parameters of sound you would like! Change the UPD port at run time to send values to different Max patches and add new layers of sound. In the demo video, drum sequences (the three beams controlling kick, snare, closedHH respectively) are controlled with hand-height. Bell-like samples are triggered at different playback speeds based on hand-height (effecting the pitch). Lastly, an additive synthesizer is played with hand-height varying the fundamental frequency (harmonics change accordingly to maintain relationship with fundamental) to create pitch bending/glissando.

To make your own, you'll need:
A webcam and necessary drivers (I used the PS3Eye)
Some laser diodes and appropriate voltage to power them (AA batteries should do)
OpenFrameworks -> http://openframeworks.cc/download/
Ensure ofxOpenCv, ofxOsc and ofxXmlSettings addons are included
Max MSP (they offer a 30 day free trial -> http://cycling74.com/downloads/)
...or you can give Pure Date a whirl. It's open source!

Enjoy!

