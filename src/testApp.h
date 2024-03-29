#pragma once

#include "ofMain.h"
#include "TerrainPatch.h"

#define PATCHES_WIDTH 8
#define PATCHES_HEIGHT 4

class testApp : public ofBaseApp{

	public:

    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofVec2f previousMousePosition;
    ofLight light;
    ofCamera camera;
    
    TerrainPatch terrainPatches[PATCHES_WIDTH*PATCHES_HEIGHT];
    	
};
