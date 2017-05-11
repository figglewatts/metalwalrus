#ifndef AUDIO_H
#define AUDIO_H
#pragma once

#include <irrKlang/irrKlang.h>

namespace metalwalrus
{
	class Audio
	{
	public:
		~Audio();

		static void createEngine();
		static void dropEngine();

		static irrklang::ISoundEngine *engine; 
	};
}

#endif // AUDIO_H