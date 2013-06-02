//
//  TerrainPatch.h
//  TerrainTest
//
//  Created by AJ Austinson on 6/1/13.
//
//

#ifndef __TerrainTest__TerrainPatch__
#define __TerrainTest__TerrainPatch__

#include <iostream>
#include "ofMain.h"

class TerrainPatch {
public:

    TerrainPatch();
    TerrainPatch(ofVec2f position);
    
    void build();
    void draw();
    
private:
    
    ofVec2f position;
    ofVboMesh terrainVbo;
    ofTexture diffuseTexture;
    unsigned char *heightmapData;
    
};

#endif /* defined(__TerrainTest__TerrainPatch__) */
