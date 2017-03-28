/* 
 * File:   SpriteBatch.cpp
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 * 
 * Created on March 27, 2017, 4:28 PM
 */

#include "SpriteBatch.h"

namespace metalwalrus
{
	SpriteBatch::SpriteBatch() : SpriteBatch(1000) { }

	SpriteBatch::SpriteBatch(int size)
	{
		int length = size * 4; // 4 vertices per sprite
		this->tintCol = Color();
		this->size = size;
		this->vertices.resize(length); // 4 vertices per sprite
		
		std::vector<GLuint> indices(length);
		for (int i = 0; i < length; i += 4)
		{
			indices[i] = i;
			indices[i+1] = i+1;
			indices[i+2] = i+2;
			indices[i+3] = i+3;
		}
		
		this->batchMesh = VertexData::create(this->vertices.data(), 
				length, indices.data(), length);
	}
	
	SpriteBatch::SpriteBatch(const SpriteBatch& orig) 
	{
		// self explan.
	}
	
	SpriteBatch::~SpriteBatch() 
	{
		delete batchMesh;
	}
	
	SpriteBatch SpriteBatch::operator=(const SpriteBatch& orig)
	{
		this->tintCol = orig.tintCol;
		this->size = orig.size;
		this->vertices = orig.vertices;
		*this->batchMesh = *orig.batchMesh;
	}
	
	void SpriteBatch::flush() 
	{
		if (index == 0) return;
		
		renderCalls++;
		
		int spritesInBatch = index / 16; // 4 vertices: X,Y,U,V for each
		int count = spritesInBatch * 4; // vertex count
		if (lastTexture != nullptr) lastTexture->bind();
		
		batchMesh->bind();
		
		batchMesh->draw(count);
		
		batchMesh->unbind();
		lastTexture->unbind();
		
		index = 0;
	}
}
