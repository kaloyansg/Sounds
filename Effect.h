#pragma once
#include "Sound.h"
template <typename Type>
class Effect : public Sound<Type>
{
public:
	Effect(Sound<Type>* sound, Type(*funcptr)(Type, unsigned), const Type amplitude);
	static double normalizingCoef;
};

template<typename Type>
double Effect<Type>::normalizingCoef = 1;

template<typename Type>
inline Effect<Type>::Effect(Sound<Type>* sound, Type(*funcptr)(Type, unsigned), const Type amplitude)
{
	Type* samples = new Type[sound->getDuration()];
	unsigned duration = sound->getDuration();

	Type maxValue = 0;

	for (size_t i = 0; i < duration; i++)
	{
		if (maxValue < abs((*sound)[i]))
			maxValue = abs((*sound)[i]);
	}

	normalizingCoef = abs(amplitude) / maxValue;

	for (unsigned i = 0; i < duration; i++)
	{
		samples[i] = funcptr((*sound)[i], i);
		Sound<Type>::clip(samples[i], amplitude);
	}

	Sound<Type>::setSamples(samples);
	Sound<Type>::setAmplitude(abs(amplitude));
	Sound<Type>::setDuration(duration);
}