#ifndef AUDIO_H
#define AUDIO_H
#pragma once

namespace metalwalrus
{
	class Audio
	{
	public:
		virtual ~Audio() {}
		virtual void playSound(const char* sound, bool loop = false) = 0;
		virtual void stopAllSounds() = 0;
	};
}

#endif // AUDIO_H