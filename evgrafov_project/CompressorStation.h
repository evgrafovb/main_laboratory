#pragma once
#include <string>
#include <fstream>

class CompressorStation
{
	int id;
	/*static int MaxID;*/
public:

	static void Reset();
	static int MaxID;
	std::string name;
	int workshops;
	int busyWorkshops;
	char efficiency;
	bool link;

	CompressorStation();

	int getStationID() const;

	friend std::istream& operator >> (std::istream& in, CompressorStation& station);
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& station);
	friend std::ifstream& operator >> (std::ifstream& fin, CompressorStation& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const CompressorStation& pipe);
};