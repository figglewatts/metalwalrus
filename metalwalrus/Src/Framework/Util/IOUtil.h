#pragma once

#include <vector>

namespace metalwalrus
{
	class IOUtil
	{
		IOUtil(); // static class
	public:
		static std::vector<unsigned char> *loadTexture(char *filePath, unsigned int &texWidth, unsigned int &texHeight);
	};
}