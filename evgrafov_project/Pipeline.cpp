#include "Pipeline.h"
#include "utils.h"

int Pipeline::MaxID = 0;

Pipeline::Pipeline()
{
	id = ++MaxID;
	kilometre = "Unknown";
	length = 0.1;
	diametre = 100;
	isRepaired = false;
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
	pipe.diametre = CorrectInput(100, 1400);
	std::cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
	pipe.isRepaired = CorrectInput(0, 1);
	return in;
}

std::ostream& operator << (std::ostream& out, const Pipeline& pipe)
{
	out << "\tName: " << pipe.kilometre
		<< "\tLength: " << pipe.length
		<< "\tDiametre: " << pipe.diametre
		<< "\tIs repaired: " << pipe.isRepaired << std::endl;
	return out;
}
