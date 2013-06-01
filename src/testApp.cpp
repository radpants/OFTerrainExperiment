#include "testApp.h"

#define FQ 1.0f
#define TERRAIN_RESOLUTION 64
#define TERRAIN_PATCH_SIZE 4.0f

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofSetWindowShape(1280, 800);
    ofSetVerticalSync(true);
    
    renderTexture.allocate(TERRAIN_RESOLUTION, TERRAIN_RESOLUTION, GL_RGB);
    
    unsigned char* textureData = new unsigned char[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*3];
    
    for( int y = 0; y < TERRAIN_RESOLUTION; ++y )
    {
        for( int x = 0; x < TERRAIN_RESOLUTION; ++x )
        {
            float u = (float)x / (float)TERRAIN_RESOLUTION * FQ;
            float v = (float)y / (float)TERRAIN_RESOLUTION * FQ;
            
            float val = 0.0f;
            for( int o = 0; o < 3; ++o )
            {
                float ofq = FQ * (float)o;
                val += ofNoise(u * ofq, v * ofq);
            }
            
            unsigned char h = (unsigned char)((val / 3.0f) * 255.0f);
            textureData[((y*TERRAIN_RESOLUTION)+x)*3] = h;
            textureData[((y*TERRAIN_RESOLUTION)+x)*3+1] = h;
            textureData[((y*TERRAIN_RESOLUTION)+x)*3+2] = h;
        }
    }
    
    renderTexture.loadData(textureData, TERRAIN_RESOLUTION, TERRAIN_RESOLUTION, GL_RGB);
    
    float verts[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*3];
    float colors[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*3];
    float texCoords[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*2];
    ofIndexType indices[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*6];
    
    cout << "-- vertex data ------------------------" << endl;
    
    for( int i = 0; i < TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*3; i+=3 )
    {
        int idx = i / 3;
        int x = idx % TERRAIN_RESOLUTION;
        int y = idx / TERRAIN_RESOLUTION;
        
        float u = (float)x / (float)TERRAIN_RESOLUTION;
        float v = (float)y / (float)TERRAIN_RESOLUTION;
        
        float offset = (float)(TERRAIN_RESOLUTION / 2) * TERRAIN_PATCH_SIZE;
        
        verts[i] = (float)x * TERRAIN_PATCH_SIZE - offset;
        verts[i+1] = (float)textureData[i] / 255.0f * 100.0f;
        verts[i+2] = (float)y * TERRAIN_PATCH_SIZE - offset;
        
        colors[i]   = verts[i+1] / 100.0f;
        colors[i+1] = verts[i+1] / 100.0f;
        colors[i+2] = verts[i+1] / 100.0f;
        
        
        cout << i << ": (" << verts[i] << ", " << verts[i+1] << ", " << verts[i+2] << ")" << endl;
        
    }
    
    cout << "-- texcoord data ------------------------" << endl;
    
    for( int i = 0; i < TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*2; i+=2 )
    {
        int idx = i / 2;
        int x = idx % TERRAIN_RESOLUTION;
        int y = idx / TERRAIN_RESOLUTION;
        texCoords[i]   = (float)x / (float)TERRAIN_RESOLUTION;
        texCoords[i+1] = (float)y / (float)TERRAIN_RESOLUTION;
        
        cout << i << ": (" << texCoords[i] << ", " << texCoords[i+1] << ")" << endl;
    }
    
    cout << "-- index data ------------------------" << endl;
    
    for( int i = 0; i < (TERRAIN_RESOLUTION-1)*(TERRAIN_RESOLUTION-1)*6; i+=6 )
    {
        int idx = i / 6;
        indices[i] = idx;
        indices[i+1] = idx+1;
        indices[i+2] = idx+(TERRAIN_RESOLUTION);
        
        indices[i+3] = indices[i+2];
        indices[i+4] = indices[i+1];
        indices[i+5] = indices[i+2] + 1;
        
        cout << i << "[" << indices[i] << ":" << indices[i+1] << ":" << indices[i+2] << "|" << indices[i+3] << ":" << indices[i+4] << ":" << indices[i+5] << "]" << endl;
    }
    
    terrainVbo.enableColors();
    terrainVbo.enableTexCoords();
    terrainVbo.setVertexData(&verts[0], 3, TERRAIN_RESOLUTION*TERRAIN_RESOLUTION, GL_STATIC_DRAW, sizeof(float)*3);
    terrainVbo.setTexCoordData(&texCoords[0], TERRAIN_RESOLUTION*TERRAIN_RESOLUTION, GL_STATIC_DRAW, sizeof(float)*2);
    terrainVbo.setColorData(&colors[0], TERRAIN_RESOLUTION*TERRAIN_RESOLUTION, GL_STATIC_DRAW, sizeof(float)*3);
    terrainVbo.setIndexData(&indices[0], TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*6, GL_STATIC_DRAW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofClear(0, 0, 0);
    renderTexture.draw(16, 16, 64, 64);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 10);
    ofRotate(ofGetElapsedTimef() * 20.0, 1, 1, 0);
    glPointSize(10.0f);
    renderTexture.bind();
    terrainVbo.drawElements(GL_TRIANGLES, (TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*6));
    renderTexture.unbind();
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