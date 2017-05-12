#include "PCAudio.h"

namespace metalwalrus
{
	PCAudio::~PCAudio()
	{
		engine->drop();
	}

	void PCAudio::playSound(const char * sound, bool loop)
	{
		engine->play2D(sound, loop);
	}

	void PCAudio::stopAllSounds()
	{
		engine->stopAllSounds();
	}
}