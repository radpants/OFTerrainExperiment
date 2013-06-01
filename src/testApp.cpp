#include "testApp.h"
#include "noise.h"

#define FQ 3.0f
#define TERRAIN_RESOLUTION 256
#define TERRAIN_PATCH_SIZE 2.0f

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    ofSetWindowShape(1280, 800);
    ofSetVerticalSync(true);
    
    renderTexture.allocate(TERRAIN_RESOLUTION, TERRAIN_RESOLUTION, GL_RGB);
    
    noise::module::Perlin perlin;    
    
    unsigned char* textureData = new unsigned char[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION*3];
    
    for( int y = 0; y < TERRAIN_RESOLUTION; ++y )
    {
        for( int x = 0; x < TERRAIN_RESOLUTION; ++x )
        {
            float u = (float)x / (float)TERRAIN_RESOLUTION * FQ;
            float v = (float)y / (float)TERRAIN_RESOLUTION * FQ;
            
//            float val = 0.0f;
//            for( int o = 0; o < 3; ++o )
//            {
//                float ofq = FQ * (float)o;
//                val += ofNoise(u * ofq, v * ofq);
//            }
            double val = perlin.GetValue(u, 0.0f, v) * 0.5 + 0.5 * 2.0;
            unsigned char h = (unsigned char)((val / 3.0) * 255.0);
            textureData[((y*TERRAIN_RESOLUTION)+x)*3] = h;
            textureData[((y*TERRAIN_RESOLUTION)+x)*3+1] = h;
            textureData[((y*TERRAIN_RESOLUTION)+x)*3+2] = h;
        }
    }
    
    renderTexture.loadData(textureData, TERRAIN_RESOLUTION, TERRAIN_RESOLUTION, GL_RGB);
    
    
    for( int y = 0; y < TERRAIN_RESOLUTION; ++y )
    {
        for( int x = 0; x < TERRAIN_RESOLUTION; ++x )
        {
            float h = textureData[((y*TERRAIN_RESOLUTION)+x)*3];
            float offset = ((float)TERRAIN_RESOLUTION / 2.0f) * TERRAIN_PATCH_SIZE;
            ofVec3f v0 = ofVec3f(x*TERRAIN_PATCH_SIZE-offset, h, y*TERRAIN_PATCH_SIZE-offset);
            terrainVbo.addVertex(v0);
            terrainVbo.addTexCoord(ofVec2f(x, y));
            
            
            
            if( x < TERRAIN_RESOLUTION - 1 && y < TERRAIN_RESOLUTION - 1 )
            {
                ofVec3f v1 = ofVec3f((x+1)*TERRAIN_PATCH_SIZE-offset, textureData[((y*TERRAIN_RESOLUTION)+(x+1))*3], y*TERRAIN_PATCH_SIZE-offset);
                ofVec3f v2 = ofVec3f(x*TERRAIN_PATCH_SIZE-offset, textureData[(((y+1)*TERRAIN_RESOLUTION)+x)*3], (y+1)*TERRAIN_PATCH_SIZE-offset);
                
                ofVec3f e1 = v1 - v0;
                ofVec3f e2 = v2 - v0;
                ofVec3f normal = e2.cross(e1).normalized();
                terrainVbo.addNormal(normal);
                
//                cout << e1 << endl;
                
//                ofFloatColor color;
//                color.r = normal.x;
//                color.g = normal.y;
//                color.b = normal.z;
//                color.a = 1.0f;
//                terrainVbo.addColor(color);
                
                ofIndexType a = (y*TERRAIN_RESOLUTION)+x;
                ofIndexType b = (y*TERRAIN_RESOLUTION)+x+1;
                ofIndexType c = ((y+1)*TERRAIN_RESOLUTION)+x;
                ofIndexType d = ((y+1)*TERRAIN_RESOLUTION)+x+1;
                
                terrainVbo.addIndex(a);
                terrainVbo.addIndex(b);
                terrainVbo.addIndex(c);
                
                terrainVbo.addIndex(c);
                terrainVbo.addIndex(b);
                terrainVbo.addIndex(d);
            }            
        }
    }
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    camera.setPosition(-250.0f, 250.0f, -250.0f);
    camera.lookAt(ofVec3f::zero());
    camera.setFov(60);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofClear(0, 0, 0);
    renderTexture.draw(16, 16, 64, 64);
    
    camera.begin();
    glPointSize(10.0f);
    renderTexture.bind();
    terrainVbo.draw();
    renderTexture.unbind();
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
    float theta = ((float)x / (float)ofGetWindowWidth()) * (3.14159f * 2.0f);
    float h = (y - ofGetWindowWidth()/2.0f) * 3.0f;
    camera.setPosition(500 * cos(theta), h, 400 * sin(theta));
    camera.lookAt(ofVec3f::zero());
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