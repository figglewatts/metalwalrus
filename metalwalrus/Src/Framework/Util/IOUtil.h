#ifndef IOUTIL_H
#define IOUTIL_H
#pragma once

#include <vector>

namespace metalwalrus
{
	namespace utilities 
	{
		class IOUtil {
			IOUtil();
		public:
			static std::vector<unsigned char> *loadTexture(std::string filePath, unsigned int &texWidth, unsigned int &texHeight);
		

		};
	}
}
#endif