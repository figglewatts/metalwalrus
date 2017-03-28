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
#include "VertexData.h"

namespace metalwalrus
{
    class SpriteBatch {
	Color tintCol;
	int size;
	std::vector<VertData2D> vertices;
	VertexData *batchMesh;
	
	bool drawing = false;
	int index = 0;
	Texture2D *lastTexture = nullptr;
	
	void flush();
	void switchTexture(Texture2D tex);
    public:
	int renderCalls = 0;
	
	SpriteBatch();
	SpriteBatch(int size);
	SpriteBatch(const SpriteBatch& orig);
	
	~SpriteBatch();

	SpriteBatch operator=(const SpriteBatch& orig);
	
	void begin();
	void end();
    };
}

#endif /* SPRITEBATCH_H */

