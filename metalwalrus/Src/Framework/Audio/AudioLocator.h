#ifndef AUDIOLOCATOR_H
#define AUDIOLOCATOR_H
#pragma once

#include "Audio.h"
#include "NullAudio.h"

namespace metalwalrus
{
	// code adapted from "Game Programming Patterns - Robert Nystrom"
	// Service Locator Pattern, pg. 251-265
	class AudioLocator
	{
	private:
		static Audio *service_;
		static NullAudio *nullService_;
	public:
		static void initialize();
		static Audio &getAudio();
		static void provide(Audio *service);
		static void dispose();
	};
}

#endif // AUDIOLOCATOR_H