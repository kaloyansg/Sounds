#pragma once
#include <cmath>
template <typename Type>
class Sound
{
	unsigned duration;
	Type* samples;
	Type amplitude;

protected:
	Sound();
	void setDuration(const unsigned duration);
	void setSamples(Type* samples);
	void setAmplitude(const Type amplitude);
	static void clip(Type& sample, const Type amplitude);

public:
	Sound(const unsigned duration, const Type* samples, const Type amplitude);
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	virtual ~Sound();

	const Type operator[](unsigned index) const;
	const unsigned getDuration() const;
};

template<typename Type>
inline Sound<Type>::Sound()
{
	duration = 0;
	samples = nullptr;
	amplitude = 0;
}

template<typename Type>
inline void Sound<Type>::setDuration(const unsigned duration)
{
	this->duration = duration;
}

template<typename Type>
inline void Sound<Type>::setSamples(Type* samples)
{
	this->samples = samples;
}

template<typename Type>
inline void Sound<Type>::setAmplitude(const Type amplitude)
{
	this->amplitude = amplitude;
}

template<typename Type>
inline void Sound<Type>::clip(Type& sample, const Type amplitude)
{
	if (abs(sample) > abs(amplitude))
	{
		if (sample > 0) sample = abs(amplitude);
		else sample = abs(amplitude) * (-1);
	}
}


template<typename Type>
inline Sound<Type>::Sound(const unsigned duration, const Type* samples, const Type amplitude)
{

	this->samples = new Type[duration];

	for (size_t i = 0; i < duration; i++)
	{
		this->samples[i] = samples[i];
	}
	for (size_t i = 0; i < duration; i++)
	{
		clip(this->samples[i], amplitude);
	}

	this->duration = duration;
	this->amplitude = abs(amplitude);
}

template<typename Type>
inline Sound<Type>::~Sound()
{
	delete[] samples;
	samples = nullptr;
}

template<typename Type>
inline const Type Sound<Type>::operator[](unsigned index) const
{
	if (index < 0 || index >= duration) throw "Index out of range!";

	return samples[index];
}

template<typename Type>
inline const unsigned Sound<Type>::getDuration() const
{
	return duration;
}