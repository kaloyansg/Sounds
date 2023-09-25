#pragma once
#include "Sound.h"
#include <fstream>
template <typename Type>
class FromFile : public Sound<Type>
{
public:
	FromFile(const char* fileName, const Type amplitude);
};

template<typename Type>
inline FromFile<Type>::FromFile(const char* fileName, const Type amplitude)
{
	std::ifstream sampleReader(fileName, std::ios::binary);
	if (!sampleReader) throw "File not opened!";

	sampleReader.seekg(0, std::ios::end);
	unsigned duration = sampleReader.tellg()/sizeof(Type);
	sampleReader.seekg(0, std::ios::beg);
	
	Type* samples = new Type[duration];
	Type sample;
	for (size_t i = 0; i < duration; i++)
	{
		sampleReader.read((char*)&sample, sizeof(Type));
		samples[i] = sample;

		Sound<Type>::clip(samples[i], amplitude);
	}
	sampleReader.close();

	Sound<Type>::setSamples(samples);
	Sound<Type>::setDuration(duration);
	Sound<Type>::setAmplitude(abs(amplitude));
}