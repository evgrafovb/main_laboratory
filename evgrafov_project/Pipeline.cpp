#include "Pipeline.h"
#include "utils.h"

int Pipeline::MaxID = 0;

void Pipeline::Reset()
{
	MaxID = 0;
}

Pipeline::Pipeline()
{
	//MaxID++;
	id = ++MaxID;
	kilometre = "Unknown";
	length = 0.1;
	diametre = 500;
	isRepaired = false;
	CSin = -1;
	CSout = -1;
}

int Pipeline::getPipeID() const
{
	return id;
}

std::istream& operator >> (std::istream& in, Pipeline& pipe)
{
	std::cout << "Type a pipeline name: ";
	READ_LINE(in, pipe.kilometre);
	std::cout << "Enter a length: ";
	pipe.length = CorrectInput(0.1, 999.9);
	std::cout << "Enter a diametre: ";
	pipe.diametre = CorrectDiametre();
	std::cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
	pipe.isRepaired = CorrectInput(0, 1);
	return in;
}

std::ostream& operator << (std::ostream& out, const Pipeline& pipe)
{
	out << "ID: " << pipe.id
		<< "\tName: " << pipe.kilometre
		<< "\tLength: " << pipe.length
		<< "\tDiametre: " << pipe.diametre
		<< "\tIs repaired: " << pipe.isRepaired
		<< "\tIn CS's ID: " << pipe.CSin 
		<< "\tOut CS's ID: " << pipe.CSout << endl;
	return out;
}

std::ifstream& operator>>(std::ifstream& fin, Pipeline& pipe)
{
	fin >> pipe.id;
	LOAD_LINE(fin, pipe.kilometre);
	fin >> pipe.length
		>> pipe.diametre
		>> pipe.isRepaired
		>> pipe.CSin
		>> pipe.CSout;
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Pipeline& pipe)
{
	fout << pipe.id << '\n'
		<< pipe.kilometre << '\n'
		<< pipe.length << '\n'
		<< pipe.diametre << '\n'
		<< pipe.isRepaired << '\n'
		<< pipe.CSin << '\n' 
		<< pipe.CSout << endl;
	return fout;
}