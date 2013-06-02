//
//  TerrainPatch.cpp
//  TerrainTest
//
//  Created by AJ Austinson on 6/1/13.
//
//

#include "TerrainPatch.h"
#include "noise.h"

#define FQ 0.6f
#define TERRAIN_RESOLUTION 64
#define TEXTURE_RESOLUTION 512
#define TERRAIN_PATCH_SIZE 4.0f

TerrainPatch::TerrainPatch()
{
    this->position = ofVec2f::zero();
}

TerrainPatch::TerrainPatch(ofVec2f position)
{
    this->position = position;
}

void TerrainPatch::build()
{
    
    noise::module::Perlin perlin;
    
    heightmapData = new unsigned char[TERRAIN_RESOLUTION*TERRAIN_RESOLUTION];
    
    for( int y = 0; y < TERRAIN_RESOLUTION; ++y )
    {
        for( int x = 0; x < TERRAIN_RESOLUTION; ++x )
        {
            float u = (float)(x+(position.x*TERRAIN_RESOLUTION)) / (float)TERRAIN_RESOLUTION * FQ;
            float v = (float)(y+(position.y*TERRAIN_RESOLUTION)) / (float)TERRAIN_RESOLUTION * FQ;
            
            //            float val = 0.0f;
            //            for( int o = 0; o < 3; ++o )
            //            {
            //                float ofq = FQ * (float)o;
            //                val += ofNoise(u * ofq, v * ofq);
            //            }
            double val = perlin.GetValue(u, 0.0f, v) * 0.5 + 0.5 * 2.0;
            unsigned char h = (unsigned char)((val / 3.0) * 255.0);
            heightmapData[(y*TERRAIN_RESOLUTION)+x] = h;
        }
    }
    
    
    diffuseTexture.allocate(TEXTURE_RESOLUTION, TEXTURE_RESOLUTION, GL_RGB);
    unsigned char *terrainTextureData = new unsigned char[TEXTURE_RESOLUTION*TEXTURE_RESOLUTION*3];
    
    for( int y = 0; y < TEXTURE_RESOLUTION; ++y )
    {
        for( int x = 0; x < TEXTURE_RESOLUTION; ++x )
        {
            float u = (float)(x+(position.x*TEXTURE_RESOLUTION)) / (float)TEXTURE_RESOLUTION * FQ;
            float v = (float)(y+(position.y*TEXTURE_RESOLUTION)) / (float)TEXTURE_RESOLUTION * FQ;
            
            double val = perlin.GetValue(u, 0.0f, v) * 0.5 + 0.5 * 2.0;
            unsigned char h = (unsigned char)((val / 3.0) * 255.0);
            
            if( h > 80 )
            {
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3] = h;
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3+1] = h;
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3+2] = h;
            }
            else
            {
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3] = 0;
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3+1] = h / 2;
                terrainTextureData[((y*TEXTURE_RESOLUTION)+x)*3+2] = h;
            }
            
        }
    }
    diffuseTexture.loadData(terrainTextureData, TEXTURE_RESOLUTION, TEXTURE_RESOLUTION, GL_RGB);
    
    for( int y = 0; y < TERRAIN_RESOLUTION; ++y )
    {
        for( int x = 0; x < TERRAIN_RESOLUTION; ++x )
        {
            float h = heightmapData[(y*TERRAIN_RESOLUTION)+x];
            ofVec3f v0 = ofVec3f(x*TERRAIN_PATCH_SIZE, h, y*TERRAIN_PATCH_SIZE);
            terrainVbo.addVertex(v0);
            
            float u = ((float)x / (float)TERRAIN_RESOLUTION) * (float)TEXTURE_RESOLUTION;
            float v = ((float)y / (float)TERRAIN_RESOLUTION) * (float)TEXTURE_RESOLUTION;
            terrainVbo.addTexCoord(ofVec2f(u, v));
            
            //            terrainVbo.addColor(ofFloatColor(0.0f, 0))
            
            
            if( x < TERRAIN_RESOLUTION - 1 && y < TERRAIN_RESOLUTION - 1 )
            {
                ofVec3f v1 = ofVec3f((x+1)*TERRAIN_PATCH_SIZE, heightmapData[(y*TERRAIN_RESOLUTION)+(x+1)], y*TERRAIN_PATCH_SIZE);
                ofVec3f v2 = ofVec3f(x*TERRAIN_PATCH_SIZE, heightmapData[((y+1)*TERRAIN_RESOLUTION)+x], (y+1)*TERRAIN_PATCH_SIZE);
                
                ofVec3f e1 = v1 - v0;
                ofVec3f e2 = v2 - v0;
                ofVec3f normal = e1.cross(e2).normalized();
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
}

void TerrainPatch::draw()
{
    diffuseTexture.bind();
    ofPushMatrix();
    ofTranslate(position.x*TERRAIN_PATCH_SIZE*(TERRAIN_RESOLUTION-1), 0.0f, position.y*TERRAIN_PATCH_SIZE*(TERRAIN_RESOLUTION-2));
    terrainVbo.draw();
    ofPopMatrix();
    diffuseTexture.unbind();
}