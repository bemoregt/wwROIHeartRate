#include "ofApp.h"

using namespace ofxCv;
//--------------------------------------------------------------
void ofApp::setup(){

    camWidth = 320;  // try to grab at this size.
    camHeight = 240;
    
    //get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(size_t i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    //videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
    //videoTexture.allocate(videoInverted);
    ofSetVerticalSync(true);
    
    // for graph
    ofSetFrameRate(60);
    // ofxGraph uses ofxGui as a internal setting UI
    ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
    
    // ofxGraph Init
    graph.setup("Sample");
    graph.setDx(1.0); // which means delta of time
    graph.setColor(ofColor::white); // ofColor(255,255,255)
    graph.setPosition(10, 250);
    graph.setSize(620, 220);
    graph.setAutoScale(true, 1.0);
    graph.setBufSize(4096);
}

//--------------------------------------------------------------
void ofApp::update(){

    ofBackground(100, 100, 100);
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){
        frame1.setFromPixels(vidGrabber.getPixelsRef());        //ofPixels & pixels = vidGrabber.getPixels();
        //for(size_t i = 0; i < pixels.size(); i++){
            //invert the color of the pixel
        //    videoInverted[i] = 255 - pixels[i];
        //}
        
        //load the inverted pixels
        //videoTexture.loadData(videoInverted);
        cv::Mat image= toCv(frame1);
        rect1 = cv::Rect(100, 100, 20, 20);
        roi1= image(rect1);
        cv::Scalar meanRect= mean(roi1);
        
        //ofLog() << meanRect << endl;
        graph.add(meanRect.val[1]);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // graph
    ofBackground(50,50,50);
    graph.draw();
    
    // video
    ofSetColor(255);
    vidGrabber.draw(0, 0);
    //videoTexture.draw(camWidth, 0, camWidth, camHeight);
    
    // roi
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofDrawRectangle(rect1.x, rect1.y, rect1.width, rect1.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 's' || key == 'S'){
        vidGrabber.videoSettings();
    }
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
