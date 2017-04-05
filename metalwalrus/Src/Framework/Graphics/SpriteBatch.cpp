/* 
 * File:   SpriteBatch.cpp
 * Author: Sam Gibson (100115871) <sam.gibson@uea.ac.uk>
 * 
 * Created on March 27, 2017, 4:28 PM
 */

#include "SpriteBatch.h"

#include <stdexcept>
#include <GL/glew.h>

#include "../Util/Debug.h"
#include "../Util/MathUtil.h"

namespace metalwalrus
{
	SpriteBatch::SpriteBatch() : SpriteBatch(1000) { }

	SpriteBatch::SpriteBatch(int size)
	{
		int length = size * 4; // 4 vertices per sprite
		this->size = size;
		this->vertices.resize(length, VertData2D()); // 4 vertices per sprite
		
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
			this->size = orig.size;
			this->vertices = orig.vertices;
			*this->batchMesh = *orig.batchMesh;
			this->transformMat = orig.transformMat;
		}
		return *this;
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
		
		glLoadIdentity();
		glLoadMatrixf(transformMat.glMatrix().data());

		batchMesh->draw(spritesInBatch);
		
		batchMesh->unbind();
		lastTexture->unbind();
		//this->vertices.clear();
		
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
		glPushMatrix();
		
		// TODO: custom exceptions
		if (drawing) 
			throw std::runtime_error("A previous batch has not yet ended!");
		
		glDepthMask(false);

		renderCalls = 0;
		
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
		glPopMatrix();

		Debug::set_drawCalls(renderCalls);
		
		drawing = false;
	}
	
	void SpriteBatch::drawtex(Texture2D& tex, float x, float y,
	    float scaleX, float scaleY, float rotation)
	{
		drawtexsize(tex, x, y, tex.get_width(), tex.get_height(), 
				scaleX, scaleY, rotation);
	}
	
	void SpriteBatch::drawtexsize(Texture2D& tex, float xPos, float yPos, 
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
		float x = -(width / 2);
		float y = -(height / 2);
		float x2 = x + width;
		float y2 = y + height;
		
		float vals[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
		vals[6] = xPos - x;
		vals[7] = yPos - y;
		
		if (rotation != 0.0)
		{
			float cosine = cosf(utilities::MathUtil::degToRad(rotation));
			float sine = sinf(utilities::MathUtil::degToRad(rotation));
			vals[0] = cosine;
			vals[3] = -sine;
			vals[1] = sine;
			vals[4] = cosine;
		}
		if (scaleX != 1.0 || scaleY != 1.0)
		{
			vals[0] *= scaleX;
			vals[4] *= scaleY;
		}
		Matrix3 transMat = Matrix3(vals);
		
		VertData2D vert0;
		vert0.pos = Vector2(x, y).transform(transMat);
		vert0.texCoord = Vector2(u, v);
		
		VertData2D vert1;
		vert1.pos = Vector2(x2, y).transform(transMat);
		vert1.texCoord = Vector2(u2, v);
		
		VertData2D vert2;
		vert2.pos = Vector2(x2, y2).transform(transMat);
		vert2.texCoord = Vector2(u2, v2);
		
		VertData2D vert3;
		vert3.pos = Vector2(x, y2).transform(transMat);
		vert3.texCoord = Vector2(u, v2);
		
		vertices[index] = vert0;
		vertices[index+1] = vert1;
		vertices[index+2] = vert2;
		vertices[index+3] = vert3;
		
		index += 4;
	}
	
	void SpriteBatch::drawreg(TextureRegion& texRegion, float x, float y, 
	    float scaleX, float scaleY, float rotation)
	{
		drawregsize(texRegion, x, y, texRegion.get_width(), 
				texRegion.get_height(), scaleX, scaleY, rotation);
	}
	
	void SpriteBatch::drawregsize(TextureRegion& texRegion, float xPos, 
			float yPos, float width, float height, float scaleX, 
			float scaleY, float rotation)
	{
		if (texRegion.get_texture() != lastTexture)
			this->switchTexture(texRegion.get_texture());
		else if (index >= vertices.capacity())
			this->flush();

		float u = texRegion.get_u();
		float v = texRegion.get_v();
		float u2 = texRegion.get_u2();
		float v2 = texRegion.get_v2();
		float x = -(width / 2);
		float y = -(height / 2);
		float x2 = x + width;
		float y2 = y + height;

		float vals[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
		vals[6] = xPos - x;
		vals[7] = yPos - y;

		if (rotation != 0.0)
		{
			float cosine = cosf(utilities::MathUtil::degToRad(rotation));
			float sine = sinf(utilities::MathUtil::degToRad(rotation));
			vals[0] = cosine;
			vals[3] = -sine;
			vals[1] = sine;
			vals[4] = cosine;
		}
		if (scaleX != 1.0 || scaleY != 1.0)
		{
			vals[0] *= scaleX;
			vals[4] *= scaleY;
		}
		Matrix3 transMat = Matrix3(vals);

		VertData2D vert0;
		vert0.pos = Vector2(x, y).transform(transMat);
		vert0.texCoord = Vector2(u, v2);

		VertData2D vert1;
		vert1.pos = Vector2(x2, y).transform(transMat);
		vert1.texCoord = Vector2(u2, v2);

		VertData2D vert2;
		vert2.pos = Vector2(x2, y2).transform(transMat);
		vert2.texCoord = Vector2(u2, v);

		VertData2D vert3;
		vert3.pos = Vector2(x, y2).transform(transMat);
		vert3.texCoord = Vector2(u, v);

		vertices[index] = vert0;
		vertices[index + 1] = vert1;
		vertices[index + 2] = vert2;
		vertices[index + 3] = vert3;

		index += 4;
	}

	void SpriteBatch::setTransformMat(Matrix3 m)
	{
		if (index > 0)
			flush();
		this->transformMat = m;
	}
}
