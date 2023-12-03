#include "CompressorStation.h"
#include "utils.h"

int CompressorStation::MaxID = 0;

void CompressorStation::ResetMaxID()
{
	MaxID = 0;
}

void CompressorStation::SetMaxID() const
{
	MaxID = id;
}

CompressorStation::CompressorStation()
{
	id = ++MaxID;
	name = "Unknown";
	workshops = 1;
	busyWorkshops = 0;
	efficiency = 'A';
	start = 0;
	end = 0;
}

void CompressorStation::StartWorkshop()
{
	if (busyWorkshops < workshops) {
		busyWorkshops++;
	}
}

void CompressorStation::FinishWorkshop()
{
	if (busyWorkshops > 0) {
		busyWorkshops--;
	}
}

void CompressorStation::StartAmountIncrease()
{
	start++;
}

void CompressorStation::EndAmountIncrease()
{
	end++;
}

void CompressorStation::StartAmountDicrease()
{
	start--;
}

void CompressorStation::EndAmountDicrease()
{
	start--;
}

int CompressorStation::getStationID() const
{
	return id;
}

int CompressorStation::getStationWorks() const
{
	return workshops;
}

int CompressorStation::getStationBusyWorks() const
{
	return busyWorkshops;
}

int CompressorStation::getStationStart() const
{
	return start;
}

int CompressorStation::getStationEnd() const
{
	return end;
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
		<< "\tEfficiency: " << station.efficiency
		<< "\tTimes being start CS: " << station.start
		<< "\tTimes being end CS: " << station.end << endl;
	return out;
}

std::ifstream& operator >> (std::ifstream& fin, CompressorStation& station)
{
	fin >> station.id;
	LOAD_LINE(fin, station.name);
	fin >> station.workshops
		>> station.busyWorkshops
		>> station.efficiency
		>> station.start
		>> station.end;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, const CompressorStation& station)
{
	fout << station.id << '\n'
		<< station.name << '\n'
		<< station.workshops << '\n'
		<< station.busyWorkshops << '\n'
		<< station.efficiency << '\n'
		<< station.start << '\n' 
		<< station.end << endl;
	return fout;
}