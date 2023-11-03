#include "CompressorStation.h"
#include "utils.h"

int CompressorStation::MaxID = 0;

void CompressorStation::Reset()
{
	MaxID = 0;
}

CompressorStation::CompressorStation()
{
	//MaxID++;
	id = ++MaxID;
	name = "Unknown";
	workshops = 1;
	busyWorkshops = 0;
	efficiency = 'A';
}

int CompressorStation::getStationID() const
{
	return id;
}

std::istream& operator >> (std::istream& in, CompressorStation& station)
{
	cout << "Type a station name: ";
	READ_LINE(in, station.name);
	cout << "Enter an amount of workshops: ";
	station.workshops = CorrectInput(1, 100);
	cout << "Enter an amount of busy workshops: ";
	station.busyWorkshops = CorrectInput(0, station.workshops);
	cout << "Enter \"A\", if a station is efficient, enter \"B\" - if it isn't: ";
	station.efficiency = CorrectInput('A', 'B');
	return in;
}

std::ostream& operator << (std::ostream& out, const CompressorStation& station)
{
	out << "ID: " << station.id
		<< "\tName: " << station.name
		<< "\tWorkshops: " << station.workshops
		<< "\tWorkshops are worked: " << station.busyWorkshops
		<< "\tEfficiency: " << station.efficiency << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, CompressorStation& station)
{
	fin >> station.id;
	LOAD_LINE(fin, station.name);
	fin >> station.workshops
		>> station.busyWorkshops
		>> station.efficiency;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, const CompressorStation& station)
{
	fout << station.id << '\n'
		<< station.name << '\n'
		<< station.workshops << '\n'
		<< station.busyWorkshops << '\n'
		<< station.efficiency << endl;
	return fout;
}