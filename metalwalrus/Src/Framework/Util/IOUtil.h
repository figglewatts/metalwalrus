#pragma once

#include <vector>

namespace metalwalrus
{
	namespace utilities 
	{
		class IOUtil {
			IOUtil();
		public:
			static std::vector<unsigned char> *loadTexture(char *filePath, unsigned int &texWidth, unsigned int &texHeight);
		

		};
	}
}