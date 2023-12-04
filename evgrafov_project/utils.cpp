#include "utils.h"
#include <unordered_set>
#include <filesystem>

int CorrectDiametre()
{
	int dia;
	const int diametres[] = {500, 700, 1000, 1400};
	while ((cin >> dia).fail() || find(begin(diametres), end(diametres), dia) == end(diametres)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter 500, 700, 1000 or 1400 for diametre: ";
	}
	std::cerr << dia << endl;
	return dia;
}

int CorrectIntID() {
	int id;
	while ((cin >> id).fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter an integer: ";
	}
	cerr << id << endl;
	return id;
}

string FileName() {
	string file_name;
	cout << "Enter a file name: ";
	READ_LINE(cin, file_name);
	if (!(filesystem::exists(file_name))) {
		cout << "No such file in directory" << endl;
	}
	return file_name;
}
