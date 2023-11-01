#include "CompressorStation.h"
#include "utils.h"

int CompressorStation::MaxID = 0;

CompressorStation::CompressorStation()
{
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
	out	<< "\tName: " << station.name
		<< "\tWorkshops: " << station.workshops
		<< "\tWorkshops are worked: " << station.busyWorkshops
		<< "\tEfficiency: " << station.efficiency << endl;
	return out;
}
