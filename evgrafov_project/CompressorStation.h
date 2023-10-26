#pragma once
#include <iostream>
#include <string>

class CompressorStation
{
public:
	std::string name;
	int workshops;
	int busyWorkshops;
	char efficiency;
	friend std::istream& operator >> (std::istream& in, CompressorStation& station);
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& station);
};

