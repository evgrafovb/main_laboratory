#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <unordered_set>
#include <set>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"
#include <unordered_map>

using namespace std;

unordered_map<int, Pipeline>& ClearPipes(unordered_map<int, Pipeline>& pipes) {
	pipes.clear();
	return pipes;
}

unordered_map<int, CompressorStation>& ClearStations(unordered_map<int, CompressorStation>& stations) {
	stations.clear();
	return stations;
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
	cerr << id << endl;
	return id;
}

void EditPipeline(unordered_map<int, Pipeline>& pipes, const int& id) {
	if (pipes[id].CSin == -1) {
		pipes[id].isRepaired = !(pipes[id].isRepaired);
	}
	else {
		cout << "This pipeline is in GTN. Disconnect it to edit it" << endl;
	}
}

void EditStation(unordered_map<int, CompressorStation>& stations) {
	cout << "Enter a compressor station's ID for editing: ";
	int id;
	id = CorrectIntID();
	if (CheckID(stations, id)) {
		if (stations[id].start == 0 && stations[id].end == 0) {
			string decision;
			cout << "Enter \"+\", if you want to start one workshop, enter \"-\" - if you want to stop one workshop: ";
			cin >> decision;
			if (decision == "+" && stations[id].busyWorkshops < stations[id].workshops) {
				stations[id].busyWorkshops++;
			}
			if (decision == "-" && stations[id].busyWorkshops > 0) {
				stations[id].busyWorkshops--;
			}
			cerr << decision << endl;
		}
		else {
			cout << "This CS is in GTN. Disconnect it to edit it" << endl;
		}
	}
	else {
		cout << "No compressor station with such ID" << endl;
	}
}

void SavePipeline(ofstream& fout, const Pipeline& pipe) {
	if (pipe.kilometre != "") {
		fout << pipe;
	}
}

void SaveStation(ofstream& fout, const CompressorStation& station) {
	if (station.name != "") {
		fout << station;
	}
}

Pipeline LoadPipeline(ifstream& fin) {
	Pipeline pipe;
	fin >> pipe;
	return pipe;
}

CompressorStation LoadStation(ifstream& fin) {
	CompressorStation station;
	fin >> station;
	return station;
}

void DeletePipe(unordered_map<int, Pipeline>& pipes, const int& id) {
	if (pipes[id].CSin == -1) {
		pipes.erase(id);
	}
	else {
		cout << "This pipeline is in GTN. Disconnect it to delete it" << endl;
	}
}

void DeleteStation(unordered_map<int, CompressorStation>& stations) {
	cout << "Enter a station's ID for deleting: ";
	int id;
	id = CorrectIntID();
	if (CheckID(stations, id)) {
		if (stations[id].start == 0 && stations[id].end == 0) {
			stations.erase(id);
		}
		else {
			cout << "This CS is in GTN. Disconnect it to delete it" << endl;
		}
	}
	else {
		cout << "No station with such ID" << endl;
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
unordered_set<int> FindPipelinesByFilter(const unordered_map<int, Pipeline>& pipes, PipelineFilter<type> f, type param) {
	unordered_set<int> result;
	for (auto& [id, pipe] : pipes) {
		if (f(pipe, param)) {
			result.insert(id);
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
unordered_set<int> FindStationsByFilter(const unordered_map<int, CompressorStation>& stations, StationFilter<type> f, type param) {
	unordered_set<int> result;
	for (auto& [id, station] : stations) {
		if (f(station, param)) {
			result.insert(id);
		}
	}
	if (!(size(result))) {
		cout << "No stations found" << endl;
	}
	return result;
}

void FindMenu() {
	cout << "1. Find pipelines by name" << endl
		<< "2. Find pipelines by repair status" << endl
		<< "Enter a number from 1 to 3: ";
}

void PrintFoundPipes(const int& id, unordered_map<int, Pipeline>& pipes) {
	cout << pipes[id];
}

unordered_set<int> PackEdit(unordered_map<int, Pipeline>& pipes) {
	unordered_set<int> pipesID{};
	FindMenu();
	switch (CorrectInput(1, 2)) {
	case 1: {
		string name;
		cout << "Input pileline name for searching: ";
		READ_LINE(cin, name);
		for (int id : FindPipelinesByFilter(pipes, CheckByName, name)) {
			PrintFoundPipes(id, pipes);
			pipesID.insert(id);
		}
		break;
	}
	case 2: {
		bool flag;
		cout << "Input station status for searching: ";
		flag = CorrectInput(false, true);
		for (int id : FindPipelinesByFilter(pipes, CheckByRepair, flag)) {
			PrintFoundPipes(id, pipes);
			pipesID.insert(id);
		}
		break;
	}
	}
	return pipesID;
}

int getPipelineID(unordered_map<int, Pipeline>& pipes) {
	int dia;
	int pipeID = 0;
	cout << "Enter a pipeline's diametre: ";
	dia = CorrectDiametre();
	for (auto& [id, pipe] : pipes) {
		if (dia == pipe.diametre && pipe.isRepaired == false && pipe.CSin == -1) {
			pipeID = pipe.getPipeID();
			break;
		}
	}
	if (!pipeID) {
		cout << "No such pipeline. Create new one:" << endl;
		Pipeline pipe;
		cout << "Type a pipeline name: ";
		READ_LINE(cin, pipe.kilometre);
		cout << "Enter a length: ";
		pipe.length = CorrectInput(0.1, 999.9);
		pipe.diametre = dia;
		pipe.isRepaired = false;
		pipes.insert(pair{ pipe.getPipeID(), pipe });
		pipeID = pipe.getPipeID();
	}
	return pipeID;
}

int getInCSID() {
	int in;
	cout << "Enter an in CS's id: ";
	in = CorrectIntID();
	return in;
}

int getOutCSID() {
	int out;
	cout << "Enter an out CS's id: ";
	out = CorrectIntID();
	return out;
}

void EditMenu() {
	cout << "1. Select pipelines by ID" << endl
		<< "2. Edit all found pipelines" << endl
		<< "3. Delete all found pipelines" << endl
		<< "4. Show all pipelines" << endl
		<< "0. Return to main MENU" << endl << endl
		<< "Enter a number from 0 to 4: ";
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
		<< "11. Find pipelines by repair status" << endl
		<< "12. Find stations by name" << endl
		<< "13. Find stations by percent of not working workshops" << endl
		<< "14. Pack editing of pipelines" << endl
		<< "15. Connect pipeline" << endl
		<< "16. Disconnect pipeline" << endl
		<< "17. Show Gas Transmission Network" << endl
		<< "18. Network's sort" << endl
		<< "0. Exit" << endl << endl
		<< "Enter a number from 0 to 18: ";
}

int main() {
	redirect_output_wrapper cerr_out(cerr);
	ofstream logfile("logging.txt");
	if (logfile)
		cerr_out.redirect(logfile);
	unordered_map<int, Pipeline> pipes;
	unordered_map<int, CompressorStation> stations;
	while (1) {
		PrintMenu();
		switch (CorrectInput(0, 18)) {
		case 1: {
			Pipeline pipe;
			cin >> pipe;
			pipes.insert(pair{ pipe.getPipeID(), pipe });
			break;
		}
		case 2: {
			CompressorStation station;
			cin >> station;
			stations.insert(pair{ station.getStationID(), station });
			break;
		}
		case 3: {
			for (auto& [id, pipe] : pipes) {
				cout << pipe << endl;
			}
			for (auto& [id, station] : stations) {
				cout << station << endl;
			}
			break;
		}
		case 4: {
			cout << "Enter a pipeline's ID for editing: ";
			int id;
			id = CorrectIntID();
			if (CheckID(pipes, id)) {
				EditPipeline(pipes, id);
			}
			else {
				cout << "No pipeline with such ID" << endl;
			}
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
			READ_LINE(cin, file_name);
			fout.open(file_name, ios::out);
			if (fout.is_open()) {
				fout << pipes.size() << endl;
				for (auto& [id, pipe] : pipes) {
					SavePipeline(fout, pipe);
				}
				fout << stations.size() << endl;
				for (auto& [id, station] : stations) {
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
				pipes = ClearPipes(pipes);
				stations = ClearStations(stations);
				int count_p;
				fin >> count_p;
				while (count_p--) {
					Pipeline pipe = LoadPipeline(fin);
					pipes.insert(pair{ pipe.getPipeID(), pipe });
					pipe.MaxID = pipe.getPipeID();

				}
				int count_s;
				fin >> count_s;
				while (count_s--) {
					CompressorStation station = LoadStation(fin);
					stations.insert(pair{ station.getStationID(), station });
					station.MaxID = station.getStationID();
				}
				fin.close();
			}
			break;
		}
		case 8: {
			cout << "Enter a pipeline's ID for deleting: ";
			int id;
			id = CorrectIntID();
			if (CheckID(pipes, id)) {
				DeletePipe(pipes, id);
			}
			else {
				cout << "No pipeline with such ID" << endl;
			}
			break;
		}
		case 9: {
			DeleteStation(stations);
			break;
		}
		case 10: {
			string name;
			cout << "Input pileline name for searching: ";
			READ_LINE(cin, name);
			for (int id : FindPipelinesByFilter(pipes, CheckByName, name)) {
				cout << pipes[id];
			}
			break;
		}
		case 11: {
			cout << "Input station status for searching: ";
			bool flag = CorrectInput(false, true);
			for (int id : FindPipelinesByFilter(pipes, CheckByRepair, flag)) {
				cout << pipes[id];
			}
			break;
		}
		case 12: {
			string name;
			cout << "Input station name for searching: ";
			READ_LINE(cin, name);
			for (int id : FindStationsByFilter(stations, CheckByName, name)) {
				cout << stations[id];
			}
			break;
		}
		case 13: {
			cout << "Input percent of unworking stations for searching: ";
			double percent = CorrectInput(0.0, 100.0);
			for (int id : FindStationsByFilter(stations, CheckByUnworkingWorkshops, percent)) {
				cout << stations[id];
			}
			break;
		}
		case 14: {
			unordered_set<int> pipesID = PackEdit(pipes);
			bool flag = true;
			while (flag) {
				EditMenu();
				switch (CorrectInput(0, 4)) {
				case 1: {
					pipesID.clear();
					while (1) {
						cout << "Input ID of pipeline or 0 to complete: ";
						int id;
						id = CorrectIntID();
						if (id) {
							if (CheckID(pipes, id)) {
								PrintFoundPipes(id, pipes);
								pipesID.insert(id);
							}
							else {
								cout << "No pipeline with such ID" << endl;
							}
						}
						else {
							break;
						}
					}
					break;
				}
				case 2: {
					for (const int& id : pipesID) {
						EditPipeline(pipes, id);
					}
					break;
				}
				case 3: {
					for (const int& id : pipesID) {
						DeletePipe(pipes, id);
					}
					break;
				}
				case 4: {
					for (auto& [id, pipe] : pipes) {
						cout << pipe << endl;
					}
					break;
				}
				case 0: {
					flag = false;
					break;
				}
				}
			}
			break;
		}
		case 15: {
			int pipeID = getPipelineID(pipes);
			int in = getInCSID();
			int out = getOutCSID();
			if (CheckID(stations, in) && CheckID(stations, out) && in != out && stations[in].busyWorkshops < stations[in].workshops && stations[out].busyWorkshops < stations[out].workshops) {
				stations[in].busyWorkshops++;
				stations[out].busyWorkshops++;
				stations[in].start++;
				stations[out].end++;
				pipes[pipeID].CSin = in;
				pipes[pipeID].CSout = out;
			}
			break;
		}
		case 16: {
			cout << "Enter a pipeline's ID for diconnection: ";
			int pipeID = CorrectIntID();
			if (CheckID(pipes, pipeID) && pipes[pipeID].CSin != -1) {
				stations[pipes[pipeID].CSin].start--;
				stations[pipes[pipeID].CSout].end--;
				pipes[pipeID].CSin = -1;
				pipes[pipeID].CSout = -1;

			}
			break;
		}
		case 17: {
			for (auto& [id, pipe] : pipes) {
				if (pipe.CSin != -1) {
					cout << pipe << endl;
				}
			}
			for (auto& [id, station] : stations) {
				if (station.start > 0 || station.end > 0) {
					cout << station << endl;
				}
			}
			break;
		}
		case 18: {

			break;
		}
		case 0:
			return 0;
		}
	}
	return 0;
}