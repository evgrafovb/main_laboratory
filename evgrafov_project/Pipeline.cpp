#include "Pipeline.h"
#include "utils.h"

std::istream& operator >> (std::istream& in, Pipeline& pipe)
{
	std::cout << "Type a pipeline name: ";
	READ_LINE(in, pipe.kilometre);
	std::cout << "Enter a length: ";
	pipe.length = CorrectInput(0.1, 999.9);
	std::cout << "Enter a diametre: ";
	pipe.diametre = CorrectInput(100, 1400);
	std::cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
	in >> pipe.isRepaired;
	return in;
}

std::ostream& operator << (std::ostream& out, const Pipeline& pipe)
{
	if (pipe.kilometre != "") {
		out << "Name: " << pipe.kilometre
			<< "\tLength: " << pipe.length
			<< "\tDiametre: " << pipe.diametre
			<< "\tIs repaired: " << pipe.isRepaired << std::endl;
	}
	return out;
}
