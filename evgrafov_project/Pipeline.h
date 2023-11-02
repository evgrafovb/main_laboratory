#pragma once
#include <string>

class Pipeline
{
	int id;

public:

	static int MaxID;
	
	std::string kilometre;
	double length;
	int diametre;
	bool isRepaired;
	
	Pipeline();
	
	int getPipeID() const;
	
	friend std::istream& operator >> (std::istream& in, Pipeline& pipe);
	friend std::ostream& operator << (std::ostream& out, const Pipeline& pipe);
	/*friend std::ifstream& operator >> (std::ifstream& fin, Pipeline& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipeline& pipe);*/
};