#include "utils.h"
#include <unordered_set>

int CorrectDiametre()
{
	int dia;
	unordered_set<int> diametres = { 500, 700, 1000, 1400 };
	while ((cin >> dia).fail() || !(diametres.contains(dia))) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter 500, 700, 1000 or 1400 for diametre: ";
	}
	std::cerr << dia << endl;
	return dia;
}