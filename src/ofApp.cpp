#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    ofEnableDepthTest();
    
    recorder.setPrefix(ofToDataPath("recording/frame_"));
    recorder.setFormat("bmp");
    recorder.startThread();
    ofSetFrameRate(30);
    midiIn.openPort(0);
    midiIn.addListener(this);
    
    ofSetBackgroundColor(ofColor::white);
    for (int i = 0; i < 10000; i++){
        ofVec3f p;
        p.x = ofRandomf();
        p.y = ofRandomf();
        p.z = ofRandomf();
        p /= sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
        p *= 2000;
        ofBoxPrimitive* cube = new ofBoxPrimitive();
        cube->set(15);
        cube->setPosition(p.x, p.y, p.z);
        cubes.push_back(cube);
    }
    
    for (int i = 0; i < 6; i++){
        auto road = new ofBoxPrimitive();
        ofVec3f p;
        auto tilt = ofRandom(360);
        auto roll = ofRandom(360);
        auto pan = ofRandom(360);
        road->setPosition(0, 0, 0);
        road->set(5, 5, 100000);
        road->tiltDeg(tilt);
        road->rollDeg(roll);
        road->panDeg(pan);
        roads.push_back(road);
    }
    
    fboCapture.allocate(ofGetWidth() * CAPTURE_SCALE, ofGetHeight() * CAPTURE_SCALE, GL_RGBA);
    screenCapture.allocate(ofGetWidth() * CAPTURE_SCALE, ofGetHeight() * CAPTURE_SCALE, ofImageType::OF_IMAGE_COLOR_ALPHA);
    
    ofImage oceanImage;
    oceanImage.load("ocean.jpg");
    oceanTexture = oceanImage.getTexture();
    oceanTexture.setTextureWrap(GL_REPEAT, GL_REPEAT);
    oceanTexture.generateMipmap();
    oceanTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);
    
    ofImage moonImage;
    moonImage.load("moon.jpg");
    moonTexture = moonImage.getTexture();
    moonTexture.setTextureWrap(GL_REPEAT, GL_REPEAT);
    moonTexture.generateMipmap();
    moonTexture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST);
    
    cam.setDistance(500);
    cam.setFarClip(100000);
    
    ofLight* light1 = new ofLight();
    light1->setPosition(-2500, -2500, -2500);
    light1->enable();
    
    ofLight* light2 = new ofLight();
    light2->setPosition(0, 0, 3000);
    light2->enable();
    
    ofLight* light3 = new ofLight();
    light3->setPosition(3500, 0, 0);
    light3->enable();
    
    lights.push_back(light1);
    lights.push_back(light2);
    lights.push_back(light3);
}

void ofApp::exit(){
    recorder.waitForThread();
    recorder.stopThread();
}

//--------------------------------------------------------------
void ofApp::update(){
    // show the framerate on window title
    std::stringstream strm;
    strm << "fps: " << ofGetFrameRate();
    ofSetWindowTitle(strm.str());
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (capture){
        fboCapture.begin();
        ofClear(ofColor::white);
        ofScale(CAPTURE_SCALE, CAPTURE_SCALE, CAPTURE_SCALE);
    }

    cam.begin();
    oceanTexture.bind();
    for (auto cube : cubes){
        cube->draw();
    }
    oceanTexture.unbind();
    
    moonTexture.bind();
    for (auto road : roads){
        road->draw();
    }
    moonTexture.unbind();
    cam.end();
    
    // capture one image (this might skip a rendering frame on the screen)
    if (capture){
        fboCapture.end();
        ofPixels pixels;
        fboCapture.readToPixels(pixels);
        screenCapture.setFromPixels(pixels);
        screenCapture.save("captures/capture.bmp");
        capture = false;
    }
    
    
    // capture all the images if recording is started
    // this can slow down the rendering by a lot, so be aware of the framerate...
    // if frames are skipped this is going to mess up the rendering when imported as a video
    if (recording){
        screenCapture.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        recorder.addFrame(screenCapture);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'r':
            toggleRecording();
            break;
        case 'p':
            captureScreen();
            break;
        default:
            break;
    }
}

void ofApp::newMidiMessage(ofxMidiMessage& eventArgs){
    
}

void ofApp::captureScreen(){
    capture = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

void ofApp::toggleRecording(){
    recording = !recording;
}

