#pragma once
#include <iostream>
#include <string>

class Pipeline
{
public:
	std::string kilometre;
	double length;
	int diametre;
	bool isRepaired;
	friend std::istream& operator >> (std::istream& in, Pipeline& pipe);
	friend std::ostream& operator << (std::ostream& out, const Pipeline& pipe);
};

