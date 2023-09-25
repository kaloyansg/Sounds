#pragma once
#include "Sound.h"
template <typename Type>
class Periodical : public Sound<Type>
{
public:
	Periodical(const Type* samples, unsigned numberOfSamples, unsigned repentance, const Type amplitude);
};

template<typename Type>
inline Periodical<Type>::Periodical(const Type* numbers, unsigned numberOfSamples, unsigned repentance, const Type amplitude)
{
	unsigned duration = numberOfSamples * repentance;
	Type* samples = new Type[duration];
	unsigned counter = 0;
	for (size_t i = 0; i < repentance; i++)
	{
		for (size_t j = 0; j < numberOfSamples; j++)
		{
			samples[counter] = numbers[j];
			Sound<Type>::clip(samples[counter], amplitude);
			counter++;
		}
	}

	Sound<Type>::setSamples(samples);
	Sound<Type>::setAmplitude(abs(amplitude));
	Sound<Type>::setDuration(duration);
}