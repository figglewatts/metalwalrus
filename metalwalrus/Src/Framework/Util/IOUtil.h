#pragma once

#include <vector>

namespace metalwalrus
{
	namespace utilities 
	{
		static std::vector<unsigned char> *loadTexture(char *filePath, unsigned int &texWidth, unsigned int &texHeight);
	}
}