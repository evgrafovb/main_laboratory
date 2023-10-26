#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"

using namespace std;

//template <typename type>
//type CorrectInput(type min, type max) {
//	type item;
//	while ((cin >> item).fail() || item < min || item > max) {
//		cin.clear();
//		cin.ignore(10000, '\n');
//		cout << "Enter a number from " << min << " to " << max << ": ";
//	}
//	return item;
//}
//
//string ReadLine() {
	//string full_name;
	//getline(cin >> ws, full_name);
	//return full_name;
//}

string FileName() {
	string file_name;
	cout << "Enter a file name: ";
	while ((cin >> file_name).fail() || !(filesystem::exists(file_name))) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter a valid file name: ";
	}
	return file_name;
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
	getline(fin >> ws, id);
	if (id == "PIPE") {
		getline(fin, pipe.kilometre);
		fin >> pipe.length
			>> pipe.diametre
			>> pipe.isRepaired;
	}
	return pipe;
}

CompressorStation LoadStation(ifstream& fin) {
	CompressorStation station;
	string id;
	getline(fin >> ws, id);
	if (id == "STATION") {
		getline(fin, station.name);
		fin >> station.workshops
			>> station.busyWorkshops
			>> station.efficiency;
	}
	return station;
}

//Pipeline& SelectPipe(vector<Pipeline>& pipes) {
//	cout << "Enter index: ";
//	unsigned int index = CorrectInput(1u, pipes.size());
//	return pipes[index-1];
//}

//istream& operator >> (istream& in, Pipeline& pipe) {
//	cout << "Type a pipeline name: ";
//	pipe.kilometre = ReadLine();
//	cout << "Enter a length: ";
//	pipe.length = CorrectInput(0.1, 999.9);
//	cout << "Enter a diametre: ";
//	pipe.diametre = CorrectInput(100, 1400);
//	cout << "Type \"1\", if a pipeline is repaired, type \"0\" - if it isn't: ";
//	in >> pipe.isRepaired;
//	return in;
//}
//
//ostream& operator << (ostream& out, const Pipeline& pipe) {
//	if (pipe.kilometre != "") {
//		out << "Name: " << pipe.kilometre
//			<< "\tLength: " << pipe.length
//			<< "\tDiametre: " << pipe.diametre
//			<< "\tIs repaired: " << pipe.isRepaired << endl;
//	}
//	return out;
//}

//istream& operator >> (istream& in, CompressorStation& station) {
//	cout << "Type a station name: ";
//	station.name = ReadLine();
//	cout << "Enter an amount of workshops: ";
//	station.workshops = CorrectInput(1, 100);
//	cout << "Enter an amount of busy workshops: ";
//	station.busyWorkshops = CorrectInput(0, station.workshops);
//	cout << "Enter \"A\", if a station is efficient, enter \"B\" - if it isn't: ";
//	in >> station.efficiency;
//	return in;
//}
//
//ostream& operator << (ostream& out, const CompressorStation& station) {
//	if (station.name != "") {
//		out << "Name: " << station.name
//			<< "\tWorkshops: " << station.workshops
//			<< "\tWorkshops are worked: " << station.busyWorkshops
//			<< "\tEfficiency: " << station.efficiency << endl;
//	}
//	return out;
//}

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
	vector<Pipeline> pipes;
	vector<CompressorStation> stations;
	pipes.reserve(10);
	stations.reserve(10);

	while (1) {
		PrintMenu();
		switch (CorrectInput(0, 7)) {
		case 1: {
			Pipeline pipe;
			cin >> pipe;
			pipes.push_back(pipe);
			break;
		}
		case 2: {
			CompressorStation station;
			cin >> station;
			stations.push_back(station);
			break;
		}
		case 3: {
			for (Pipeline pipe : pipes) {
				cout << pipe << endl;
			}
			for (CompressorStation station : stations) {
				cout << station << endl;
			}
			break;
		}
		case 4: {
			for (int i = 0; i < pipes.size(); i++) {
				EditPipeline(pipes[i]);
			}
			break;
		}
		case 5: {
			for (int i = 0; i < stations.size(); i++) {
				EditStation(stations[i]);
			}
			break;
		}
		case 6: {
			ofstream fout;
			string file_name;
			cout << "Enter a file name: ";
			cin >> file_name;
			fout.open(file_name, ios::out);
			if (fout.is_open()) {
				fout << pipes.size() << endl;
				for (Pipeline pipe : pipes) {
					SavePipeline(fout, pipe);
				}
				fout << stations.size() << endl;
				for (CompressorStation station : stations) {
					SaveStation(fout, station);
				}
				fout.close();
			}
			break;
		}
		case 7: {
			ifstream fin;
			fin.open(FileName(), ios::in);
			if (fin.is_open()) {
				int count_p;
				fin >> count_p;
				while (count_p--)
					pipes.push_back(LoadPipeline(fin));
				int count_s;
				fin >> count_s;
				while(count_s--)
					stations.push_back(LoadStation(fin));
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
