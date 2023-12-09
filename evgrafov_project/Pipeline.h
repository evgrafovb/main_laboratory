#pragma once
#include <string>
#include <fstream>

class Pipeline
{
	int id;
	static int MaxID;
	double length;
	int diametre;
	int CSin;
	int CSout;
public:
	std::string kilometre;
	bool isRepaired;

	static void ResetMaxID();
	void SetMaxID() const;
	Pipeline();
	static Pipeline CreatePipe(int d = 0);

	int getPipeProductivity() const;
	
	int getPipeID() const;
	int getPipeDiametre() const;
	double getPipeLength() const;
	int getPipeCSin() const;
	int getPipeCSout() const;
	void setPipeCSin(int id = -1);
	void setPipeCSout(int id = -1);

	friend std::istream& operator >> (std::istream& in, Pipeline& pipe);
	friend std::ostream& operator << (std::ostream& out, const Pipeline& pipe);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipeline& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipeline& pipe);
};