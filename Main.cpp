#include <iostream>
#include <fstream>
#include "Sound.h"
#include "Silence.h"
#include "FromFile.h"
#include "Periodical.h"
#include "Mix.h"
#include "Sequence.h"
#include "Effect.h"
#include "Playlist.h"

template <typename Type>
Type mute(Type sample, unsigned index)
{
	return sample*0;
}

template <typename Type>
Type normalize(Type sample, unsigned index)
{
	return sample * Effect<Type>::normalizingCoef;
}

int main()
{
	double array[5];
	for (size_t i = 0; i < 4; i++)
	{
		array[i] = i + 0.5;
	}
	array[4] = -9;

	Sound<double> s(5, array, 5);
	try
	{
		for (size_t i = 0; i < s.getDuration(); i++)
		{
			std::cout << s[i] << "; ";
		}
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
	}

	Silence<double> a(5);
	//std::cout << a[3] << std::endl;

	try
	{
		FromFile<double> f("file.dat", 4);
		for (size_t i = 0; i < 6; i++)
		{
			//std::cout << f[i] << "; ";
		}
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
	}

	Periodical<double> p(array, 5, 3, 3);
	try
	{
		for (size_t i = 0; i < 16; i++)
		{
			//std::cout << p[i] << "; ";
		}
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
	}


	Sound<double>** arrr = new Sound<double>*[3];
	arrr[0] = &s;
	arrr[1] = &a;
	arrr[2] = &p;

	Mix<double> m(arrr, 3, 2.1);
	for (size_t i = 0; i < m.getDuration(); i++)
	{
		//std::cout << m[i] << std::endl;
	}
	std::cout << std::endl;

	Sequence<double> w(arrr, 3, 2.5);
	for (size_t i = 0; i < w.getDuration(); i++)
	{
		//std::cout << w[i] << std::endl;
	}

	double (*func) (double, unsigned);
	func = normalize;
	Effect<double> e(&s, func, 10);
	for (size_t i = 0; i < e.getDuration(); i++)
	{
		std::cout << e[i] << "; ";
	}
	std::cout << std::endl;

	delete[] arrr;

	{
		std::ofstream file("playlist1.txt");
		file << "TheWhiteRabbit.bin 10 5\n" <<
			"20\n" <<
			"AClockIsTickingInMyHome.bin 0.84\n" <<
			"30\n" <<
			"10\n" <<
			"GodIsInTheRain.bin 1.3\n" <<
			"50\n" <<
			"LectureNotesInC++.bin 2\n" <<
			"HowToOOP.bin 1.7\n" <<
			"MyMomSayingToEatMoreVegetables.bin 0\n" <<
			"AFriendCallingToPlayFootball.bin 1\n" <<
			"10 5 0.5\n" <<
			"AFriendInviteMeToABeer.bin 1\n";

		double y = 1;
		double z = 10;

		std::ofstream file1("TheWhiteRabbit.bin");
		for (double i = 0; i < 20; i++)
		{
			file1.write((const char*)&y, sizeof(y));
		}
		std::ofstream file2("AClockIsTickingInMyHome.bin");
		for (double i = 0; i < 10; i += 2)
		{
			file2.write((const char*)&i, sizeof(i));
		}
		std::ofstream file3("GodIsInTheRain.bin");
		for (double i = 0; i < 15; i += 3)
		{
			file3.write((const char*)&i, sizeof(i));
		}
		std::ofstream file4("LectureNotesInC++.bin");
		for (double i = 0; i < 20; i += 4)
		{
			file4.write((const char*)&i, sizeof(i));
		}
		std::ofstream file5("HowToOOP.bin");
		for (double i = 0; i < 25; i += 5)
		{
			file5.write((const char*)&i, sizeof(i));
		}
		std::ofstream file6("MyMomSayingToEatMoreVegetables.bin");
		for (double i = 0; i < 30; i += 6)
		{
			file6.write((const char*)&i, sizeof(i));
		}
		std::ofstream file7("AFriendCallingToPlayFootball.bin");
		for (double i = 0; i < 20; i++)
		{
			file7.write((const char*)&z, sizeof(z));
		}
		std::ofstream file8("AFriendInviteMeToABeer.bin");
		z /= 5;
		for (double i = 0; i < 10; i++)
		{
			file8.write((const char*)&z, sizeof(z));
		}

		file1.close();
		file2.close();
		file3.close();
		file4.close();
		file5.close();
		file6.close();
		file7.close();
		file8.close();
		file.close();
	}

	Playlist<double> playlist("playlist1.txt");
	std::cout << (playlist[2])[3] << std::endl;
	playlist.reproduce("playlistToFile.bin");
	FromFile<double> newFromFile("playlistToFile.bin", 100);
	for (size_t i = 0; i < newFromFile.getDuration(); i++)
	{
		std::cout << newFromFile[i] << " ";
	}
	std::cout << std::endl;
	Sequence<double>* soundFromPlaylist = (*(playlist));
	std::cout<<(*soundFromPlaylist)[9];
	delete soundFromPlaylist;
}