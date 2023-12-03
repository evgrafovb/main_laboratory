#pragma once
#include <string>
#include <fstream>

class CompressorStation
{
	int id;
	static int MaxID;	
	int workshops;
	int busyWorkshops;
	int start;
	int end;
public:
	std::string name;
	char efficiency;

	static void ResetMaxID();
	void SetMaxID() const;
	CompressorStation();
	void StartWorkshop();
	void FinishWorkshop();
	void StartAmountIncrease();
	void EndAmountIncrease();
	void StartAmountDicrease();
	void EndAmountDicrease();

	int getStationID() const;
	int getStationWorks() const;
	int getStationBusyWorks() const;
	int getStationStart() const;
	int getStationEnd() const;

	friend std::istream& operator >> (std::istream& in, CompressorStation& station);
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& station);
	friend std::ifstream& operator >> (std::ifstream& fin, CompressorStation& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const CompressorStation& pipe);
};