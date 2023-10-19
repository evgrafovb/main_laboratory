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

string ReadLine() {
	string full_name;
	getline(cin >> ws, full_name);
	return full_name;
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

void SavePipeline(ofstream& fout, const Pipeline& pipe) {
	if (pipe.kilometre != "") {
		fout << "PIPE" << '\n'
			<< pipe.kilometre << '\n'
			<< pipe.length << '\n'
			<< pipe.diametre << '\n'
			<< pipe.isRepaired << endl;
	}
}

void SaveStation(ofstream& fout, const CompressorStation& station) {
	if (station.name != "") {
		fout << "STATION" << '\n'
			<< station.name << '\n'
			<< station.workshops << '\n'
			<< station.busyWorkshops << '\n'
			<< station.efficiency << endl;
	}
}

void Save(const Pipeline& pipe, const CompressorStation& station) {
	if (pipe.kilometre != "" || station.name != "") {
		ofstream fout;
		fout.open("data.txt", ios::out);
		if (fout.is_open()) {
			if (pipe.kilometre != "") {
				fout << "PIPE" << '\n'
					<< pipe.kilometre << '\n'
					<< pipe.length << '\n'
					<< pipe.diametre << '\n'
					<< pipe.isRepaired << endl;
			}
			if (station.name != "") {
				fout << "STATION" << '\n'
					<< station.name << '\n'
					<< station.workshops << '\n'
					<< station.busyWorkshops << '\n'
					<< station.efficiency << endl;
			}
			fout.close();
		}
	}
}

Pipeline LoadPipeline(ifstream& fin) {
	Pipeline pipe;
	string id;
	while (getline(fin >> ws, id)) {
		if (id == "PIPE") {
			getline(fin, pipe.kilometre);
			fin >> pipe.length
				>> pipe.diametre
				>> pipe.isRepaired;
		}
	}
	return pipe;
}

CompressorStation LoadStation(ifstream& fin) {
	CompressorStation station;
	string id;
	while (getline(fin >> ws, id)) {
		if (id == "STATION") {
			getline(fin, station.name);
			fin >> station.workshops
				>> station.busyWorkshops
				>> station.efficiency;
		}
	}
	return station;
}

istream& operator >> (istream& in, Pipeline& pipe) {
	cout << "Type a pipeline name: ";
	pipe.kilometre = ReadLine();
	cout << "Enter a length: ";
	pipe.length = CorrectInput(0.1, 999.9);
	cout << "Enter a diametre: ";
	pipe.diametre = CorrectInput(100, 1400);
	cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
	in >> pipe.isRepaired;
	return in;
}

ostream& operator << (ostream& out, const Pipeline& pipe) {
	if (pipe.kilometre != "") {
		out << "Name: " << pipe.kilometre
			<< "\tLength: " << pipe.length
			<< "\tDiametre: " << pipe.diametre
			<< "\tIs repaired: " << pipe.isRepaired << endl;
	}
	else {
		cout << "Add new pipeline at first" << endl;

	}
	return out;
}

istream& operator >> (istream& in, CompressorStation& station) {
	cout << "Type a station name: ";
	station.name = ReadLine();
	cout << "Enter an amount of workshops: ";
	station.workshops = CorrectInput(1, 100);
	cout << "Enter an amount of busy workshops: ";
	station.busyWorkshops = CorrectInput(0, station.workshops);
	cout << "Enter \"A\", if a station is efficient, enter \"B\" - if it isn't: ";
	in >> station.efficiency;
	return in;
}

ostream& operator << (ostream& out, const CompressorStation& station) {
	if (station.name != "") {
		out << "Name: " << station.name
			<< "\tWorkshops: " << station.workshops
			<< "\tWorkshops are worked: " << station.busyWorkshops
			<< "\tEfficiency: " << station.efficiency << endl;
	}
	else {
		cout << "Add new compressor station at first" << endl;
	}
	return out;
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
			cin >> pipe;
			break;
		}
		case 2: {
			cin >> station;
			break;
		}
		case 3: {
			cout << pipe << station << endl;
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
			ofstream fout;
			fout.open("data.txt", ios::app);
			if (fout.is_open()) {
				SavePipeline(fout, pipe);
				SaveStation(fout, station);
				fout.close();
			}
			break;
		}
		case 7: {
			ifstream fin;
			fin.open("data.txt", ios::in);
			if (fin.is_open()) {
				pipe = LoadPipeline(fin);
				//station = LoadStation(fin);
				fin.close();
			}
			fin.open("data.txt", ios::in);
			if (fin.is_open()) {
				//pipe = LoadPipeline(fin);
				station = LoadStation(fin);
				fin.close();
			}
			break;
		}
		case 0:
			return 0;
		}
	}
	return 0;
}
