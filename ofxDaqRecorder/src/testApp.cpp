#include "testApp.h"

testApp::~testApp(){
    daqMan->stop();
    delete daqMan;
	ofLogNotice() << ofGetTimestampString() << " : Deleted streams and Manager" << endl; 
}

//--------------------------------------------------------------
void testApp::setup(){

    // Set a low frame rate
    ofSetFrameRate(60);
	
    
	if(this->load()){
        daqMan->start(startTime);
    }

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    /*string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0)+"\n";
            info += "Percent of free buffers: "+ofToString(floor(daqMan->percentBuffersFree()))+"\n";
            info += "Data Rate: "+ofToString(daqMan->getTotalDataRate())+"\n";
            //info += "Elapsed Time: "+ofToString(elapsedTime)+"\n";
            info += "TimeStamp: "+ofGetTimestampString()+"\n";
    ofSetColor(0);
    ofDrawBitmapString(info, 20, 20);
	*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
bool testApp::load(){

    // Read the settings file and create streams
    if (!allSettings.loadFile("settings.xml")){
        ofLogError() << ofGetTimestampString() << " : ERROR loading settings file" <<endl;
    }
    
	// this loads the global settings and turns on
	// logging to file.
	daqMan = new ofxDaqManager(allSettings);
	
    int numDevices = allSettings.getNumTags("device");
    if (numDevices == 0){
        ofLogError() << ofGetTimestampString() << ": found no devices" <<endl;
    }

    // Load and allocate the devices
    for(int i=0;i<numDevices;i++){
        allSettings.pushTag("device",i);
        string deviceType = allSettings.getValue("type","");
        
        // Check the different possible types
        if (deviceType == "MCCDEVICE"){
            daqMan->addStream(new ofxDaqMCCDeviceStream(allSettings));
        }
        if (deviceType == "SERIALDEVICE"){
            daqMan->addStream(new ofxDaqSerialStream(allSettings));
        }
		if (deviceType == "PHIDGETSPATIAL"){
			daqMan->addStream(new ofxDaqPhidgetSpatialStream(allSettings));
		}
        allSettings.popTag();
    }
    return true;
}
