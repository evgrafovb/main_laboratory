#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"
#include <unordered_map>

using namespace std;

string FileName() {
	string file_name;
	cout << "Enter a file name: ";
	READ_LINE(cin, file_name);
	if (!(filesystem::exists(file_name))) {
		cout << "No such file in directory" << endl;
	}
	return file_name;
}

template <typename type>
bool CheckID(const unordered_map<int, type>& items, const int& id) {
	return (items.contains(id));
}

int CorrectIntID() {
	int id;
	while ((cin >> id).fail()) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter an integer: ";
	}
	return id;
}

void EditPipeline(unordered_map<int, Pipeline>& pipes) {
	cout << "Enter a pipeline's ID for editing: ";
	int id;
	id = CorrectIntID();
	if (CheckID(pipes, id)) {
		pipes[id].isRepaired = !(pipes[id].isRepaired);
	}
	else {
		cout << "No pipeline with such ID" << endl;
	}
}

void EditStation(unordered_map<int, CompressorStation>& stations) {
	cout << "Enter a compressor station's ID for editing: ";
	int id;
	id = CorrectIntID();
	if (CheckID(stations, id)) {
		string decision;
		cout << "Enter \"+\", if you want to start one workshop, enter \"-\" - if you want to stop one workshop: ";
		cin >> decision;
		if (decision == "+" && stations[id].busyWorkshops < stations[id].workshops) {
			stations[id].busyWorkshops++;
		}
		if (decision == "-" && stations[id].busyWorkshops > 0) {
			stations[id].busyWorkshops--;
		}
	}
	else {
		cout << "No compressor station with such ID" << endl;
	}
}

void SavePipeline(ofstream& fout, const Pipeline& pipe) {
	if (pipe.kilometre != "") {
		fout << pipe.kilometre << '\n'
			<< pipe.length << '\n'
			<< pipe.diametre << '\n'
			<< pipe.isRepaired << endl;
	}
}

void SaveStation(ofstream& fout, const CompressorStation& station) {
	if (station.name != "") {
		fout << station.name << '\n'
			<< station.workshops << '\n'
			<< station.busyWorkshops << '\n'
			<< station.efficiency << endl;
	}
}

Pipeline LoadPipeline(ifstream& fin) {
	Pipeline pipe;
	READ_LINE(fin, pipe.kilometre);
	fin >> pipe.length
		>> pipe.diametre
		>> pipe.isRepaired;
	return pipe;
}

CompressorStation LoadStation(ifstream& fin) {
	CompressorStation station;
	READ_LINE(fin, station.name);
	fin >> station.workshops
		>> station.busyWorkshops
		>> station.efficiency;
	return station;
}

template <typename type>
void Delete(unordered_map<int, type>& items) {
	cout << "Enter a item's ID for deleting: ";
	int id;
	id = CorrectIntID();
	if (CheckID(items, id)) {
		items.erase(id);
	}
	else {
		cout << "No item with such ID" << endl;
	}
}

template <typename type>
using PipelineFilter = bool(*)(const Pipeline& pipe, type param);

bool CheckByName(const Pipeline& pipe, string param) {
	return (pipe.kilometre.find(param) != string::npos);
}

bool CheckByRepair(const Pipeline& pipe, bool param) {
	return (pipe.isRepaired == param);
}

template <typename type>
vector<int> FindPipelinesByFilter(const unordered_map<int, Pipeline>& pipes, PipelineFilter<type> f, type param) {
	vector<int> result;
	result.reserve(size(pipes));
	for (auto& [id, pipe] : pipes) {
		if (f(pipe, param)) {
			result.push_back(id);
		}
	}
	if (!(size(result))) {
		cout << "No pipelines found" << endl;
	}
	return result;
}

template <typename type>
using StationFilter = bool(*)(const CompressorStation& station, type param);

bool CheckByName(const CompressorStation& station, string param) {
	return (station.name.find(param) != string::npos);
}

bool CheckByUnworkingWorkshops(const CompressorStation& station, double param) {
	return (double((station.workshops - station.busyWorkshops) * 100) / station.workshops) >= param;
}

template <typename type>
vector<int> FindStationsByFilter(const unordered_map<int, CompressorStation>& stations, StationFilter<type> f, type param) {
	vector<int> result;
	result.reserve(size(stations));
	for (auto& [id, station] : stations) {
		if (f(station, param)) {
			result.push_back(id);
		}
	}
	if (!(size(result))) {
		cout << "No stations found" << endl;
	}
	return result;
}

void PrintMenu() {
	cout << "1. Add a pipeline" << endl
		<< "2. Add a compressor station" << endl
		<< "3. Show all objects" << endl
		<< "4. Edit a pipeline" << endl
		<< "5. Edit a compressor station" << endl
		<< "6. Save to file" << endl
		<< "7. Load from file" << endl
		<< "8. Delete a pipeline" << endl
		<< "9. Delete a compressor station" << endl
		<< "10. Find pipelines by name" << endl
		<< "11. Find pipelines by repair status - TRUE" << endl
		<< "12. Find stations by name" << endl
		<< "13. Find stations by percent of not working workshops" << endl
		<< "14. Pack editing of pipelines" << endl
		<< "0. Exit" << endl << endl
		<< "Enter a number from 0 to 14: ";
}

int main() {
	unordered_map<int, Pipeline> pipes;
	unordered_map<int, CompressorStation> stations;
	while (1) {
		PrintMenu();
		switch (CorrectInput(0, 14)) {
		case 1: {
			Pipeline pipe;
			cin >> pipe;
			pipes.insert(pair{pipe.getPipeID(), pipe});
			break;
		}
		case 2: {
			CompressorStation station;
			cin >> station;
			stations.insert(pair{station.getStationID(), station});
			break;
		}
		case 3: {
			for (auto& [id, pipe] : pipes) {
				cout << "ID: " << id;
				cout << pipe << endl;
			}
			for (auto& [id, station] : stations) {
				cout << "ID: " << id;
				cout << station << endl;
			}
			break;
		}
		case 4: {
			EditPipeline(pipes);
			break;
		}
		case 5: {
			EditStation(stations);
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
				for (auto& [id, pipe] : pipes) {
					fout << id << endl;
					SavePipeline(fout, pipe);
				}
				fout << stations.size() << endl;
				for (auto& [id, station] : stations) {
					fout << id << endl;
					SaveStation(fout, station);
				}
				fout.close();
			}
			break;
		}
		case 7: {
			ifstream fin;
			Pipeline pipe;
			CompressorStation station;
			int p_id;
			int st_id;
			fin.open(FileName(), ios::in);
			if (fin.is_open()) {
				int count_p;
				fin >> count_p;
				while (count_p--) {
					fin >> p_id;
					pipe = LoadPipeline(fin);
					pipes.insert(pair{ p_id, pipe });
					pipe.MaxID = p_id;
				}
				int count_s;
				fin >> count_s;
				while (count_s--) {
					fin >> st_id;
					station = LoadStation(fin);
					stations.insert(pair{ st_id, station });
					station.MaxID = st_id;
				}
				fin.close();
			}
			break;
		}
		case 8: {
			Delete(pipes);
			break;
		}
		case 9: {
			Delete(stations);
			break;
		}
		case 10: {
			string name;
			cout << "Input pileline name for searching: ";
			cin >> name;
			for (int id : FindPipelinesByFilter(pipes, CheckByName, name)) {
				cout << "ID: " << id;
				cout << pipes[id];
			}
			break;
		}
		case 11: {
			for (int id : FindPipelinesByFilter(pipes, CheckByRepair, true)) {
				cout << "ID: " << id;
				cout << pipes[id];
			}
			break;
		}
		case 12: {
			string name;
			cout << "Input station name for searching: ";
			cin >> name;
			for (int id : FindStationsByFilter(stations, CheckByName, name)) {
				cout << "ID: " << id;
				cout << stations[id];
			}
			break;
		}
		case 13: {
			cout << "Input percent of unworking stations for searching: ";
			double percent = CorrectInput(0.0, 100.0);
			for (int id : FindStationsByFilter(stations, CheckByUnworkingWorkshops, percent)) {
				cout << "ID: " << id;
				cout << stations[id];
			}
			break;
		}
		case 14: {

			break;
		}
		case 0:
			return 0;
		}
	}
	return 0;
}
