#include "AudioLocator.h"

namespace metalwalrus
{
	Audio *AudioLocator::service_;
	NullAudio *AudioLocator::nullService_;
	
	void AudioLocator::initialize()
	{
		nullService_ = new NullAudio();
		service_ = nullService_;
	}

	Audio &AudioLocator::getAudio() 
	{ 
		return *service_; 
	}

	void AudioLocator::provide(Audio *service)
	{
		if (service == nullptr)
			service = nullService_;

		service_ = service;
	}

	void AudioLocator::dispose() 
	{ 
		delete service_;
	}
}