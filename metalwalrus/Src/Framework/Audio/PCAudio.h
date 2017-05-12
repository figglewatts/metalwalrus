#ifndef PCAUDIO_H
#define PCAUDIO_H
#pragma once

#include <irrKlang\irrKlang.h>

#include "Audio.h"

namespace metalwalrus
{
	class PCAudio : public Audio
	{
		irrklang::ISoundEngine *engine;
	public:
		PCAudio(irrklang::ISoundEngine *engine) : engine(engine) { }
		~PCAudio();

		virtual void playSound(const char* sound, bool loop = false) override;
		virtual void stopAllSounds() override;
	};
}

#endif // PCAUDIO_H