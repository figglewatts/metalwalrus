#ifndef NULLAUDIO_H
#define NULLAUDIO_H
#pragma once

#include "Audio.h"

namespace metalwalrus
{
	class NullAudio : public Audio
	{
	public:
		virtual void playSound(const char* sound, bool loop = false) { }
		virtual void stopAllSounds() { }
	};
}

#endif // NULLAUDIO_H