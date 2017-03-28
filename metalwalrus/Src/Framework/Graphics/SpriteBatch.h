/* 
 * File:   SpriteBatch.h
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 *
 * Created on March 27, 2017, 4:28 PM
 */

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#pragma once

#include "Color.h"
#include "Vertex.h"

namespace metalwalrus
{
    class SpriteBatch {
	Color tintCol;
	int size;
	VertData2D vertices[];
	VertexData batchMesh;
	
	void flush();
	void switchTexture(Texture2D tex);
    public:
	int renderCalls = 0;
	
	SpriteBatch();
	SpriteBatch(const SpriteBatch& orig);

	SpriteBatch operator=(const SpriteBatch& orig);
	
	void begin();
	void end();
    };
}

#endif /* SPRITEBATCH_H */

