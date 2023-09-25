#pragma once
#include "Sound.h"
template <typename Type>
class Mix : public Sound<Type>
{
public:
	Mix(Sound<Type>** sounds, unsigned numberOfSounds, const Type amplitude);
};

template<typename Type>
inline Mix<Type>::Mix(Sound<Type>** sounds, unsigned numberOfSounds, const Type amplitude)
{
	unsigned duration = 0;
	for (size_t i = 0; i < numberOfSounds; i++)
	{
		if (sounds[i]->getDuration() > duration) duration = sounds[i]->getDuration();
	}

	Type* samples = new Type[duration];
	Type currValue = 0;
	for (size_t i = 0; i < duration; i++)
	{
		currValue = 0;
		for (size_t j = 0; j < numberOfSounds; j++)
		{
			try
			{
				currValue += (*(sounds[j]))[i];
			}
			catch (const char* err)
			{
				currValue += 0;
			}
		}
		currValue /= numberOfSounds;
		samples[i] = currValue;

		Sound<Type>::clip(samples[i], amplitude);
	}

	Sound<Type>::setSamples(samples);
	Sound<Type>::setAmplitude(abs(amplitude));
	Sound<Type>::setDuration(duration);
}