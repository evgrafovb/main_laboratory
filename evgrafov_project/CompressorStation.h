#pragma once
#include <string>

class CompressorStation
{
	int id;

public:

	static int MaxID;
	
	std::string name;
	int workshops;
	int busyWorkshops;
	char efficiency;
	
	CompressorStation();
	
	int getStationID() const;
	
	friend std::istream& operator >> (std::istream& in, CompressorStation& station);
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& station);
};
