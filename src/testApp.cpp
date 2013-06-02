#include "testApp.h"
#include "noise.h"



//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofSetWindowShape(1280, 800);
    ofSetVerticalSync(true);
//    ofEnableLighting();

    light.setPosition(0.0f, 300.0f, 0.0f);
    light.setDirectional();
    light.lookAt(ofVec3f(-500.0f, 0.0f, 100.0f));
    light.setDiffuseColor(ofFloatColor::white);
    light.setSpecularColor(ofFloatColor::white);
    
//    light.enable();
    
    
    for( int y = 0; y < PATCHES_HEIGHT; ++y )
    {
        for( int x = 0; x < PATCHES_WIDTH; ++x )
        {
            TerrainPatch *patch = &terrainPatches[(y*PATCHES_WIDTH)+x];
            *patch = TerrainPatch(ofVec2f(x,y));
            patch->build();
        }
    }
    
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    camera.setPosition( 0.0f, 450.0f, 0.0f );
    camera.lookAt( camera.getPosition() + ofVec3f(0.0f, -camera.getPosition().y, 200.0f) );
    camera.setFov(60);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofClear(0, 0, 0);
    
    camera.begin();
    glPointSize(10.0f);
    
    
    for( int y = 0; y < PATCHES_HEIGHT; ++y )
    {
        for( int x = 0; x < PATCHES_WIDTH; ++x )
        {
            terrainPatches[(y*PATCHES_WIDTH)+x].draw();            
        }
    }
    
    ofRotate(90.0f, 0.0f, 0.0f, 1.0f);
    ofDrawGridPlane(1000.0f);
    camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    ofVec2f movement = ofVec2f(x,y) - previousMousePosition;
    movement *= 0.7;
    camera.setPosition( camera.getPosition() + ofVec3f(movement.x, 0.0f, movement.y) );
    camera.lookAt( camera.getPosition() + ofVec3f(0.0f, -camera.getPosition().y, 200.0f) );
    previousMousePosition = ofVec2f(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    previousMousePosition = ofVec2f(x,y);
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