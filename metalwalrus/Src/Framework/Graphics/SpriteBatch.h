/* 
 * File:   SpriteBatch.h
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 *
 * Created on March 27, 2017, 4:28 PM
 */

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#pragma once

#include <vector>

#include "Color.h"
#include "Vertex.h"
#include "Texture2D.h"
#include "TextureRegion.h"
#include "VertexData.h"
#include "../Math/Matrix3.h"

namespace metalwalrus
{
    class SpriteBatch {
	Color tintCol;
	int size;
	std::vector<VertData2D> vertices;
	VertexData *batchMesh;
	Matrix3 transformMat;
	
	bool drawing = false;
	int index = 0;
	Texture2D *lastTexture = nullptr;
	float invTexWidth = 0;
	float invTexHeight = 0;
	
	void flush();
	void switchTexture(Texture2D *tex);
    public:
	int renderCalls = 0;
	
	SpriteBatch();
	SpriteBatch(int size);
	SpriteBatch(const SpriteBatch& orig);
	
	~SpriteBatch();

	SpriteBatch operator=(const SpriteBatch& orig);
	
	void begin();
	void end();
	
	// standard draw method
	// draw texture from source inside it at position with width, height
	// scale, and rotation
	void draw(Texture2D& tex, float x, float y, float width, float height,
	    float srcX, float srcY, float srcWidth, float srcHeight,
	    float scaleX = 1, float scaleY = 1, float rotation = 0);
	
	// standard with default width
	// draw texture from source inside it at position with texture width
	// and height, scale, and rotation
	void draw(Texture2D& tex, float x, float y,
	    float srcX, float srcY, float srcWidth, float srcHeight,
	    float scaleX = 1, float scaleY = 1, float rotation = 0);
	
	// standard without source
	// draw full texture at position with given width and height, as well
	// as scale and rotation
	void draw(Texture2D& tex, float x, float y, float width, float height,
	    float scaleX = 1, float scaleY = 1, float rotation = 0);
	
	// texture region standard draw
	// this is essentially shorthand for standard draw using a TextureRegion
	void draw(TextureRegion& texRegion, float x, float y, 
	    float width, float height, float scaleX = 1, float scaleY = 1,
	    float rotation = 0);
	
	// texture region default width draw
	// shorthand for standard with default width
	void draw(TextureRegion& texRegion, float x, float y, 
	    float scaleX = 1, float scaleY = 1, float rotation = 0);
    };
}
#endif /* SPRITEBATCH_H */

