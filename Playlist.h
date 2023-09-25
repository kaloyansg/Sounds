#pragma once
#include "Sound.h"
#include "FromFile.h"
#include "Effect.h"
#include "Silence.h"
#include "Sequence.h"
#include <fstream>
//#include <iostream>

struct TrnsitionsData
{
	unsigned duration;
	unsigned samples;
	double attenuationLevel;
};

template <typename Type>
class Playlist
{
private:
	Sound<Type>** sounds;
	unsigned numberOfSounds;

	static const Type M;
	static double functionCoef;
	static Type finalLevel;
	static Type function(Type sample, unsigned index);
	static Type fadeIn(Type sample, unsigned index);
	

	static bool checkSong(const char* row);
	static bool checkPuse(const char* row);
	static bool checkFadeIn(const char* row);
	static bool checkTransition(const char* row);

	static void getFileName(const char* row, std::string& fileName);
	static double getSongCoef(const char* row);
	static unsigned getFirstNum(const char* row);
	static unsigned getSecondNum(const char* row);
	static double getThirdNum(const char* row);

	void resizeSounds();

public:
	Playlist(const char* fileName);
	~Playlist();

	Sound<Type>& operator[](unsigned index);
	void reproduce(const char* filename);
	Sequence<Type>*& operator*();
};
template<typename Type>
const Type Playlist<Type>::M = 50; //it is 50, beacause the samples I use during the testing are between 1 and 50

template<typename Type>
double Playlist<Type>::functionCoef = 1;

template<typename Type>
Type Playlist<Type>::finalLevel = 0;

template<typename Type>
inline Type Playlist<Type>::function(Type sample, unsigned index)
{
	return sample * functionCoef;
}

template<typename Type>
inline Type Playlist<Type>::fadeIn(Type sample, unsigned index)
{
	Type coef = functionCoef * index;

	if (coef > finalLevel)
		return sample*finalLevel;
	else	
		return sample*coef;
}

template<typename Type>
inline bool Playlist<Type>::checkSong(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}

	std::string first("");
	while (row[index] != ' ' && row[index] != '\0')
	{
		first += row[index];
		index++;
	}

	std::ifstream file(first);
	if (file.is_open())
		file.close();
	else
		return false;

	if (row[index] == '\0') return false;

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

template<typename Type>
inline bool Playlist<Type>::checkPuse(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}
	bool num = false;
	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}
	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}
	return num;
}

template<typename Type>
inline bool Playlist<Type>::checkFadeIn(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}

	std::string first("");
	while (row[index] != ' ' && row[index] != '\0')
	{
		first += row[index];
		index++;
	}

	std::ifstream file(first);
	if (file.is_open())
		file.close();
	else
		return false;

	if (row[index] == '\0') return false;

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index])) return false;

	while (row[index] != '\0' && row[index] != ' ')
	{
		if (!isdigit(row[index]))
			return false;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

template<typename Type>
inline bool Playlist<Type>::checkTransition(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
	{
		index++;
	}
	bool num = false;
	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index])) return false;

	while (row[index] != '\0')
	{
		if (row[index] == ' ')
			break;
		if (!isdigit(row[index]))
			return false;
		else
			num = true;
		index++;
	}

	while (row[index] == ' ')
	{
		index++;
	}

	if (!isdigit(row[index]) && row[index] != '.') return false;
	bool point = false;
	while (row[index] != '\0')
	{
		if (!isdigit(row[index]))
		{
			if (row[index] == ' ')
				break;

			if (!point) point = true;
			else return false;
		}
		index++;
	}

	while (row[index] != '\0')
	{
		if (row[index] != ' ')
			return false;
		index++;
	}

	return true;
}

template<typename Type>
inline void Playlist<Type>::getFileName(const char* row, std::string& fileName)
{
	unsigned index = 0;

	while (row[index] == ' ')
		index++;

	while (row[index] != ' ')
	{
		fileName += row[index];
		index++;
	}
}

template<typename Type>
inline double Playlist<Type>::getSongCoef(const char* row)
{
	unsigned index = 0;

	while (row[index] == ' ')
		index++;

	while (row[index] != ' ')
		index++;

	while (row[index] == ' ')
		index++;

	double result = 0;
	bool point = false;
	double decimalPart = 0.1;
	while (isdigit(row[index]) || row[index] == '.')
	{
		if (row[index] == '.')
		{
			point = true;
		}
		else if (!point)
		{
			result = result * 10 + (row[index]) - '0';
		}
		else
		{
			result = result + (((row[index]) - '0') * decimalPart);
			decimalPart *= 0.1;
		}
		index++;
	}
	return result;
}

template<typename Type>
inline unsigned Playlist<Type>::getFirstNum(const char* row)
{
	unsigned index = 0;
	unsigned result = 0;

	while (row[index] == ' ')
		index++;

	while (isdigit(row[index]))
	{
		result = result*10 + (row[index]) - '0';
		index++;
	}
	return result;
}

template<typename Type>
inline unsigned Playlist<Type>::getSecondNum(const char* row)
{
	unsigned index = 0;
	unsigned result = 0;

	while (row[index] == ' ')
		index++;

	while (row[index] != ' ')
		index++;

	while (row[index] == ' ')
		index++;

	while (isdigit(row[index]))
	{
		result = result * 10 + (row[index]) - '0';
		index++;
	}
	return result;
}

template<typename Type>
inline double Playlist<Type>::getThirdNum(const char* row)
{
	unsigned index = 0;
	double result = 0;

	while (row[index] == ' ')
		index++;

	while (row[index] != ' ')
		index++;

	while (row[index] == ' ')
		index++;

	while (row[index] != ' ')
		index++;

	while (row[index] == ' ')
		index++;

	bool point = false;
	double decimalPart = 0.1;
	while (isdigit(row[index]) || row[index] == '.')
	{
		if (row[index] == '.')
		{
			point = true;
		}
		else if (!point)
		{
			result = result * 10 + (row[index]) - '0';
		}
		else
		{
			result = result + (((row[index]) - '0') * decimalPart);
			decimalPart *= 0.1;
		}
		index++;
	}
	return result;
}

template<typename Type>
inline void Playlist<Type>::resizeSounds()
{
	Sound<Type>** temp = new Sound<Type>*[this->numberOfSounds + 1];
	for (size_t i = 0; i < this->numberOfSounds; i++)
	{
		temp[i] = this->sounds[i];
	}
	delete[] this->sounds;
	this->sounds = temp;
	this->numberOfSounds++;
}

template<typename Type>
inline Playlist<Type>::Playlist(const char* fileName)
{
	char row[1024];

	std::ifstream file(fileName);
	if (!file) throw "File not opened!";
	
	char charForCheck;
	file >> charForCheck;
	if (file.eof()) throw "File is empty!";

	this->sounds = new Sound<Type>*[0];
	this->numberOfSounds = 0;

	TrnsitionsData* transitions = new TrnsitionsData[1];
	unsigned numberOfTransitions = 0;
	bool prevSong = false;  //for finding out if a transition is right after a song
	bool prevTrans = false; //for finding out if a song is right after a trantision

	//const Type M = 50; //it is 50, beacause the sample I use during the testing are between 1 and 50

	while (!file.eof())
	{
		file.seekg(-1, std::ios::cur);
		file.getline(row, 1024);
		if (strlen(row) <= 1000 && strlen(row) >= 1)
		{
			if (checkSong(row))
			{
				if (prevTrans)
				{
					numberOfTransitions++;
					resizeSounds();
					sounds[numberOfSounds - 1] = nullptr;
					prevTrans = false;
				}
				
				resizeSounds();
				std::string fileName("");
				getFileName(row, fileName);
				FromFile<Type> fromFile(fileName.c_str(), M);
				functionCoef = getSongCoef(row);
				Type (*func) (Type, unsigned);
				func = function;
				sounds[numberOfSounds - 1] = nullptr;
				sounds[numberOfSounds-1] = new Effect<Type>(&fromFile, func, M);
				
				prevSong = true;
				prevTrans = false;
			}
			else if (checkPuse(row))
			{
				prevSong = false;
				prevTrans = false;
				resizeSounds();
				sounds[numberOfSounds - 1] = new Silence<Type>(getFirstNum(row));
			}
			else if (checkFadeIn(row))
			{
				prevSong = false;
				prevTrans = false;
				resizeSounds();
				std::string fileName("");
				getFileName(row, fileName);
				FromFile<Type> fromFile(fileName.c_str(), M);
				finalLevel = getThirdNum(row);
				functionCoef = finalLevel / (getSecondNum(row) - 1); //-1 because it has to ztart from 0
				sounds[numberOfSounds - 1] = nullptr;
				Type(*func) (Type, unsigned);
				func = fadeIn;
				sounds[numberOfSounds-1] = new Effect<Type>(&fromFile, func, M);
			}
			else if(checkTransition(row))
			{
				if (prevSong)
				{
					TrnsitionsData* temp = new TrnsitionsData[numberOfTransitions + 1];
					unsigned i = 0;
					for (i = 0; i < numberOfTransitions; i++)
					{
						temp[i] = transitions[i];
					}
					temp[i].duration = getFirstNum(row);
					temp[i].samples = getSecondNum(row);
					temp[i].attenuationLevel = getThirdNum(row);
					delete[] transitions;
					transitions = temp;


					prevTrans = true;
					prevSong = false;
				}
			}
		}
		file >> charForCheck;
	}

	unsigned transitionIndex = 0;
	for (size_t i = 0; i < numberOfSounds; i++)
	{
		if (sounds[i] == nullptr)
		{
			unsigned soundDuration = 
				(sounds[i - 1])->getDuration() + (sounds[i + 1])->getDuration() - transitions[transitionIndex].samples;
			Type* samples = new Type[soundDuration];

			unsigned c = 0;
			unsigned border = (sounds[i - 1])->getDuration() - transitions[transitionIndex].duration;
			for (c = 0; c < border; c++)
			{
				samples[c] = (*(sounds[i - 1]))[c];
			}

			border = transitions[transitionIndex].duration - transitions[transitionIndex].samples;
			Type reducer = (1 - transitions[transitionIndex].attenuationLevel) / border;
			Type coef = 1 - reducer;
			for (size_t h = 0; h < border; h++)
			{
				samples[c] = (*(sounds[i - 1]))[c] * coef;
				coef -= reducer;
				++c;
			}

			reducer = transitions[transitionIndex].attenuationLevel / transitions[transitionIndex].samples;
			Type secondCoef = 1.0 / (transitions[transitionIndex].samples);
			Type riser = secondCoef;
			unsigned h = 0;
			for (h = 0; h < border; h++)
			{
				samples[c] = ((*(sounds[i - 1]))[c] * coef) + ((*(sounds[i + 1]))[h] * secondCoef);
				coef -= reducer;
				secondCoef += riser;
				++c;
			}

			for (h; c < soundDuration; h++)
			{
				samples[c] = (*(sounds[i + 1]))[h];
				++c;
			}

			sounds[i] = new Sound<Type>(soundDuration, samples, M);
			delete[] samples;
			transitionIndex++;
		}
	}

	/*for (size_t i = 0; i < numberOfSounds; i++)
	{
		if (sounds[i] == nullptr)
		{
			std::cout << "NULL" << std::endl;
			continue;
		}

		std::cout << typeid(*(sounds[i])).name() << ": ";
		for (size_t j = 0; j < sounds[i]->getDuration(); j++)
		{
			std::cout << (*(sounds[i]))[j] << "; ";
		}
		std::cout << std::endl;
	}*/

	delete[] transitions;
	file.close();
}

template<typename Type>
inline Playlist<Type>::~Playlist()
{
	for (size_t i = 0; i < numberOfSounds; i++)
	{
		delete sounds[i];
	}
	delete[] sounds;
}

template<typename Type>
inline Sound<Type>& Playlist<Type>::operator[](unsigned index)
{
	if (index >= numberOfSounds) throw "Invalid index";

	return *(sounds[index]);
}

template<typename Type>
inline void Playlist<Type>::reproduce(const char* filename)
{
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open()) throw "File not opened!";

	Type value;

	for (size_t i = 0; i < numberOfSounds; i++)
	{
		Sound<Type>* reproduce = sounds[i];
		for (size_t c = 0; c < reproduce->getDuration(); c++)
		{
			value = (*reproduce)[c];
			file.write(reinterpret_cast<const char*>(&value), sizeof(Type));
		}
	}

	file.close();
}

template<typename Type>
inline Sequence<Type>*& Playlist<Type>::operator*()
{
	Sequence<Type>* result = new Sequence<Type>(sounds, numberOfSounds, M);
	return result;
}
