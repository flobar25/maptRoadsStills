#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxImageSequenceRecorder.h"
#define CAPTURE_SCALE 5

class ofApp : public ofBaseApp, public ofxMidiListener {
    
public:
    void setup();
    void exit();
    void update();
    void draw();
    
    // recording
    void toggleRecording();
    void captureScreen();
    
    // MIDI
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    
private:
    // midi
    ofxMidiIn midiIn;
    
    // camera
    ofEasyCam cam;
    
    // lights
    vector<ofLight*> lights;
    
    // recording
    ofxImageSequenceRecorder recorder;
    Boolean recording;
    Boolean capture;
    ofImage screenCapture;
    ofFbo fboCapture;
    
    // shapes
    vector<ofBoxPrimitive*> cubes;
    vector<ofBoxPrimitive*> roads;
    ofTexture oceanTexture;
    ofTexture moonTexture;
};
