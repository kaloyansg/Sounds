#pragma once
#include "Sound.h"
template <typename Type>
class Sequence : public Sound<Type>
{
public:
	Sequence(Sound<Type>** sounds, unsigned numbeOfSounds, const Type amplitude);
};

template<typename Type>
inline Sequence<Type>::Sequence(Sound<Type>** sounds, unsigned numbeOfSounds, const Type amplitude)
{
	unsigned duration = 0;
	for (size_t i = 0; i < numbeOfSounds; i++)
	{
		duration += sounds[i]->getDuration();
	}

	Type* samples = new Type[duration];
	unsigned counter = 0;
	for (size_t i = 0; i < numbeOfSounds; i++)
	{
		unsigned currDuration = sounds[i]->getDuration();
		for (size_t j = 0; j < currDuration; j++)
		{
			samples[counter] = (*(sounds[i]))[j];
			Sound<Type>::clip(samples[counter], amplitude);
			counter++;
		}
	}

	Sound<Type>::setSamples(samples);
	Sound<Type>::setAmplitude(abs(amplitude));
	Sound<Type>::setDuration(duration);
}