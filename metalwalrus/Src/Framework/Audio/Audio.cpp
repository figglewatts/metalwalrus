#include "Audio.h"

namespace metalwalrus
{
	irrklang::ISoundEngine *Audio::engine;

	void Audio::createEngine()
	{
		engine = irrklang::createIrrKlangDevice();
	}

	void Audio::dropEngine()
	{
		engine->drop();
	}
}