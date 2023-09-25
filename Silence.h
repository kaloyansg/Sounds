#pragma once
#include "Sound.h"
template <typename Type>
class Silence : public Sound<Type>
{
public:
	Silence(unsigned duration);
};

template<typename Type>
inline Silence<Type>::Silence(const unsigned duration)
{
	Type* samples = new Type[duration];
	for (size_t i = 0; i < duration; i++)
	{
		samples[i] = 0;
	}
	Sound<Type>::setSamples(samples);
	Sound<Type>::setDuration(duration);
	Sound<Type>::setAmplitude(0);
}