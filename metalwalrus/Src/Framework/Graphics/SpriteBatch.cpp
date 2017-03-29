/* 
 * File:   SpriteBatch.cpp
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 * 
 * Created on March 27, 2017, 4:28 PM
 */

#include "SpriteBatch.h"

#include <stdexcept>
#include <GL/glew.h>

namespace metalwalrus
{
	SpriteBatch::SpriteBatch() : SpriteBatch(1000) { }

	SpriteBatch::SpriteBatch(int size)
	{
		int length = size * 4; // 4 vertices per sprite
		this->tintCol = Color();
		this->size = size;
		this->vertices.resize(length); // 4 vertices per sprite
		
		std::vector<GLuint>* indices = new std::vector<GLuint>(length);
		for (int i = 0; i < length; i += 4)
		{
			indices->at(i) = i;
			indices->at(i+1) = i+1;
			indices->at(i+2) = i+2;
			indices->at(i+3) = i+3;
		}
		
		this->batchMesh = VertexData::create(&this->vertices, indices);
		
		this->transformMat = Matrix3();
	}
	
	SpriteBatch::SpriteBatch(const SpriteBatch& orig) 
	{
		this->tintCol = orig.tintCol;
		this->size = orig.size;
		this->vertices = orig.vertices;
		*this->batchMesh = *orig.batchMesh;
		this->transformMat = orig.transformMat;
	}
	
	SpriteBatch::~SpriteBatch() 
	{
		delete batchMesh;
	}
	
	SpriteBatch SpriteBatch::operator=(const SpriteBatch& orig)
	{
		if (this != &orig)
		{
			this->tintCol = orig.tintCol;
			this->size = orig.size;
			this->vertices = orig.vertices;
			*this->batchMesh = *orig.batchMesh;
			this->transformMat = orig.transformMat;
		}
	}
	
	void SpriteBatch::flush() 
	{
		if (index == 0 || lastTexture == nullptr) return;
		
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		
		renderCalls++;
		
		this->batchMesh->updateContents();
		
		int spritesInBatch = index / 4; // 4 vertices
		int count = spritesInBatch * 4; // vertex count
		lastTexture->bind();
		
		batchMesh->bind();
		
		batchMesh->draw(spritesInBatch);
		
		batchMesh->unbind();
		lastTexture->unbind();
		this->vertices.clear();
		
		index = 0;
	}
	
	void SpriteBatch::switchTexture(Texture2D *tex)
	{
		this->flush();
		lastTexture = tex;
		invTexWidth = 1.0 / tex->get_width();
		invTexHeight = 1.0 / tex->get_height();
	}
	
	void SpriteBatch::begin()
	{
		// TODO: custom exceptions
		if (drawing) 
			throw std::runtime_error("A previous batch has not yet ended!");
		
		glDepthMask(false);
		
		drawing = true;
	}
	
	void SpriteBatch::end()
	{
		// TODO: custom exceptions
		if (!drawing)
			throw std::runtime_error("A batch has not been started!");
		
		if (index > 0)
			this->flush();
		
		this->lastTexture = nullptr;
		
		glDepthMask(true);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		
		drawing = false;
	}
	
	void SpriteBatch::draw(Texture2D& tex, float xPos, float yPos, 
			float width, float height,
			float scaleX, float scaleY, 
			float rotation)
	{	
		if (&tex != lastTexture)
			this->switchTexture(&tex);
		else if (index >= vertices.capacity())
			this->flush();
		
		float u = 0;
		float v = 1;
		float u2 = 1;
		float v2 = 0;
		float x2 = xPos + width;
		float y2 = yPos + height;
		
		Matrix3 transMat = Matrix3();
		if (scaleX != 1 || scaleY != 1)
		{
			transMat.scale(scaleX, scaleY);
		}
		
		VertData2D vert0;
		vert0.pos = Vector2(xPos, yPos) * transMat;
		vert0.texCoord = Vector2(u, v);
		
		VertData2D vert1;
		vert1.pos = Vector2(x2, yPos) * transMat;
		vert1.texCoord = Vector2(u2, v);
		
		VertData2D vert2;
		vert2.pos = Vector2(x2, y2) * transMat;
		vert2.texCoord = Vector2(u2, v2);
		
		VertData2D vert3;
		vert3.pos = Vector2(xPos, y2) * transMat;
		vert3.texCoord = Vector2(u, v2);
		
		vertices[index] = vert0;
		vertices[index+1] = vert1;
		vertices[index+2] = vert2;
		vertices[index+3] = vert3;
		
		index += 4;
	}
}
