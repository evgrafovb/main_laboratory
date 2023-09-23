#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Pipeline {
	string kilometre;
	double length;
	int diametre;
	bool isRepaired;
};

struct CompressorStation {
	string name;
	int workshops;
	int busyWorkshops;
	char efficiency;
};

template <typename type>
type CorrectInput(type min, type max) {
	type item;
	while ((cin >> item).fail() || item < min || item > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter a number from " << min << " to " << max << ": ";
	} 
	return item;
}

Pipeline InputPipeline() {
	Pipeline pipe;
	cout << "Type a kilometre name: ";
	cin >> pipe.kilometre;
	cout << "Enter a length: ";
	pipe.length = CorrectInput(0.1, 999.9);
	//cin >> pipe.length;
	cout << "Enter a diametre: ";
	pipe.diametre = CorrectInput(100, 1400);
	//cin >> pipe.diametre;
	cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
	cin >> pipe.isRepaired;
	return pipe;
}

CompressorStation InputStation() {
	CompressorStation station;
	cout << "Type a station name: ";
	cin >> station.name;
	cout << "Enter an amount of workshops: ";
	station.workshops = CorrectInput(1, 100);
	cout << "Enter an amount of busy workshops: ";
	station.busyWorkshops = CorrectInput(0, station.workshops);
	cout << "Enter \"A\", if a station is efficient, enter \"B\" - if it isn't: ";
	cin >> station.efficiency;
	return station;
}

void OutputPipeline(const Pipeline& pipe) {
	if (pipe.kilometre != "") {
		cout << "Name: " << pipe.kilometre
			<< "\tLength: " << pipe.length
			<< "\tDiametre: " << pipe.diametre
			<< "\tIs repaired: " << pipe.isRepaired << endl;
	}
	else {
		cout << "Add new pipeline at first" << endl;

	}
}

void OutputStation(const CompressorStation& station) {
	if (station.name != "") {
		cout << "Name: " << station.name
			<< "\tWorkshops: " << station.workshops
			<< "\tWorkshops are worked: " << station.busyWorkshops
			<< "\tEfficiency: " << station.efficiency << endl;
	}
	else {
		cout << "Add new compressor station at first" << endl;
	}
}

void EditPipeline(Pipeline& pipe) {
	if (pipe.kilometre != "") {
		pipe.isRepaired == 1 ? pipe.isRepaired = 0 : pipe.isRepaired = 1;
	}
}

void EditStation(CompressorStation& station) {
	if (station.name != "") {
		string decision;
		cout << "Enter \"+\", if you want to start one workshop, enter \"-\" - if you want to stop one workshop: ";
		cin >> decision;
		if (decision == "+" && station.busyWorkshops < station.workshops) {
			station.busyWorkshops++;
		}
		if (decision == "-" && station.busyWorkshops > 0) {
			station.busyWorkshops--;
		}
	}
}

void SavePipeline(const Pipeline& pipe) {
	ofstream fout;
	fout.open("data.txt", ios::app);
	if (fout.is_open()) {
		fout << "PIPE" << '\n' 
			<< pipe.kilometre << '\n'
			<< pipe.length << '\n'
			<< pipe.diametre << '\n'
			<< pipe.isRepaired << endl;
		fout.close();
	}
}

void SaveStation(const CompressorStation& station) {
	ofstream fout;
	fout.open("data.txt", ios::app);
	if (fout.is_open()) {
		fout << "STATION" << '\n' 
			<< station.name << '\n'
			<< station.workshops << '\n'
			<< station.busyWorkshops << '\n'
			<< station.efficiency << endl;
		fout.close();
	}
}

Pipeline LoadPipeline() {
	Pipeline pipe;
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) {
		string id;
		while (getline(fin, id)) {
			if (id == "PIPE") {
				fin >> pipe.kilometre
					>> pipe.length
					>> pipe.diametre
					>> pipe.isRepaired;
			}
		}
		fin.close();
	}
	return pipe;
}

CompressorStation LoadStation() {
	CompressorStation station;
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) {
		string id;
		while (getline(fin, id)) {
			if (id == "STATION") {
				fin >> station.name
					>> station.workshops
					>> station.busyWorkshops
					>> station.efficiency;
			}
		}
		fin.close();
	}
	return station;
}

void PrintMenu() {
	cout << "1. Add a pipeline" << endl
		<< "2. Add a compressor station" << endl
		<< "3. Show all objects" << endl
		<< "4. Edit a pipeline" << endl
		<< "5. Edit a compressor station" << endl
		<< "6. Save changes" << endl
		<< "7. Load" << endl
		<< "0. Exit" << endl << endl
		<< "Enter a number from 0 to 7: ";
}

int main() {
	Pipeline pipe;
	CompressorStation station;
	while (1) {
		PrintMenu();
		switch (CorrectInput(0, 7)) {
		case 1: {
			pipe = InputPipeline();
			break;
		}
		case 2: {
			station = InputStation();
			break;
		}
		case 3: {
			OutputStation(station);
			OutputPipeline(pipe);
			break;
		}
		case 4: {
			EditPipeline(pipe);
			break;
		}
		case 5: {
			EditStation(station);
			break;
		}
		case 6: {
			if (pipe.kilometre != "") {
				SavePipeline(pipe);
			}
			if (station.name != "") {
				SaveStation(station);
			}
			break;
		}
		case 7: {
			station = LoadStation();
			pipe = LoadPipeline();
			break;
		}
		case 0:
			return 0;
		}
	}
	return 0;
}