#include "Network.h"
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include <queue>

void Network::AddNewPipe(const Pipeline& pipe) {
	pipes.insert(pair{ pipe.getPipeID(), pipe });
}

void Network::AddNewStation(const CompressorStation& station) {
	stations.insert(pair{ station.getStationID(), station });
}

void Network::ShowAllObjects() {
	for (auto& [id, pipe] : pipes) {
		cout << pipe << endl;
	}
	for (auto& [id, station] : stations) {
		cout << station << endl;
	}
}

void Network::EditPipeline(int ID) {
	int id = ID;
	if (ID == 0) {
		cout << "Enter a pipeline's ID for editing: ";
		id = CorrectIntID();
	}
	if (CheckID(pipes, id)) {
		if (pipes[id].getPipeCSin() == -1) {
			pipes[id].isRepaired = !(pipes[id].isRepaired);
		}
		else {
			cout << "This pipeline is in GTN. Disconnect it to edit it" << endl;
		}
	}
	else {
		cout << "No pipeline with such ID" << endl;
	}
}

void Network::EditStation() {
	cout << "Enter a compressor station's ID for editing: ";
	int id = CorrectIntID();
	if (CheckID(stations, id)) {
		if (stations[id].getStationStart() == 0 && stations[id].getStationEnd() == 0) {
			string decision;
			cout << "Enter \"+\", if you want to start one workshop, enter \"-\" - if you want to stop one workshop: ";
			cin >> decision;
			if (decision == "+") {
				stations[id].StartWorkshop();
			}
			if (decision == "-") {
				stations[id].FinishWorkshop();
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

void Network::SaveData() {
	ofstream fout;
	fout.open(FileName(), ios::out);
	if (fout.is_open()) {
		fout << pipes.size() << endl;
		for (auto& [id, pipe] : pipes) {
			if (pipe.kilometre != "") {
				fout << pipe;
			}
		}
		fout << stations.size() << endl;
		for (auto& [id, station] : stations) {
			if (station.name != "") {
				fout << station;
			}
		}
		fout.close();
	}
}

void Network::LoadDate() {
	ifstream fin;
	fin.open(FileName(), ios::in);
	if (fin.is_open()) {
		ClearPipelines();
		ClearStations();
		int count_p;
		fin >> count_p;
		while (count_p--) {
			Pipeline pipe;
			fin >> pipe;
			pipes.insert(pair{ pipe.getPipeID(), pipe });
			pipe.SetMaxID();
		}
		int count_s;
		fin >> count_s;
		while (count_s--) {
			CompressorStation station;
			fin >> station;
			stations.insert(pair{ station.getStationID(), station });
			station.SetMaxID();
		}
		fin.close();
	}
}

void Network::DeletePipeline(int ID) {
	int id = ID;
	if (ID == 0) {
		cout << "Enter a pipeline's ID for deleting: ";
		id = CorrectIntID();
	}
	if (CheckID(pipes, id)) {
		if (pipes[id].getPipeCSin() == -1) {
			pipes.erase(id);
		}
		else {
			cout << "This pipeline is in GTN. Disconnect it to delete it" << endl;
		}
	}
	else {
		cout << "No pipeline with such ID" << endl;
	}
}

void Network::DeleteStation() {
	cout << "Enter a station's ID for deleting: ";
	int id = CorrectIntID();
	if (CheckID(stations, id)) {
		if (stations[id].getStationStart() == 0 && stations[id].getStationEnd() == 0) {
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

void Network::ClearPipelines() {
	pipes.clear();
}

void Network::ClearStations() {
	stations.clear();
}

void Network::AddConnection() {
	int pipeID = getPipelineID();
	cout << "Enter input station's ID: ";
	int in = CorrectIntID();
	cout << "Enter output station's ID: ";
	int out = CorrectIntID();
	if (CheckID(stations, in) && CheckID(stations, out) && in != out) {
		stations[in].StartWorkshop();
		stations[out].StartWorkshop();
		stations[in].StartAmountIncrease();
		stations[out].EndAmountIncrease();
		pipes[pipeID].setPipeCSin(in);
		pipes[pipeID].setPipeCSout(out);
	}
}

void Network::Disconnection() {
	cout << "Enter a pipeline's ID for diconnection: ";
	int pipeID = CorrectIntID();
	if (CheckID(pipes, pipeID) && pipes[pipeID].getPipeCSin() != -1) {
		stations[pipes[pipeID].getPipeCSin()].StartAmountDicrease();
		stations[pipes[pipeID].getPipeCSout()].EndAmountDicrease();
		pipes[pipeID].setPipeCSin(-1);
		pipes[pipeID].setPipeCSout(-1);
	}
}

void Network::ShowNetwork() {
	for (auto& [id, pipe] : pipes) {
		if (pipe.getPipeCSin() != -1) {
			cout << pipe << endl;
		}
	}
	for (auto& [id, station] : stations) {
		if (station.getStationStart() > 0 || station.getStationEnd() > 0) {
			cout << station << endl;
		}
	}
}

int Network::getPipelineID() {
	int dia;
	int pipeID = 0;
	cout << "Enter a pipeline's diametre: ";
	dia = CorrectDiametre();
	for (auto& [id, pipe] : pipes) {
		if (pipe.getPipeDiametre() == dia && pipe.isRepaired == false && pipe.getPipeCSin() == -1) {
			pipeID = pipe.getPipeID();
			break;
		}
	}
	if (!pipeID) {
		cout << "No such pipeline. Create new one:" << endl;
		Pipeline pipe = Pipeline::CreatePipe(dia);
		pipes.insert(pair{ pipe.getPipeID(), pipe });
		pipeID = pipe.getPipeID();
	}
	return pipeID;
}

vector<vector<int>> Network::CreateRibs() {
	vector<vector<int>> rebra;
	for (auto& [id, pipe] : pipes) {
		if (pipe.getPipeCSin() != -1) {
			rebra.push_back({ pipe.getPipeCSin(), pipe.getPipeCSout() });
		}
	}
	return rebra;
}

unordered_map<int, int> Network::StepenyVershin() {
	unordered_map<int, int> stepeny_vershin;
	for (auto& [id, station] : stations) {
		if (station.getStationStart() > 0 || station.getStationEnd() > 0) {
			stepeny_vershin.insert(pair{ id, station.getStationStart() });
		}
	}
	return stepeny_vershin;
}

unordered_map<int, Pipeline> Network::getPipelines() {
	return pipes;
}

unordered_map<int, CompressorStation> Network::getStations() {
	return stations;
}

void Network::TopologicalSort() {
	auto rebra = CreateRibs();
	auto stepeny_vershin = StepenyVershin();
	int vershiny = stepeny_vershin.size();
	vector<int> result;
	queue<int> q;
	for (auto& [id, stepen] : stepeny_vershin) {
		if (stepen == 0) {
			q.push(id);
		}
	}
	while (!q.empty()) {
		int vershina = q.front();
		q.pop();
		result.insert(result.begin(), vershina);
		for (auto& pair : rebra) {
			if (pair[1] == vershina) {
				stepeny_vershin[pair[0]]--;
				if (stepeny_vershin[pair[0]] == 0) {
					q.push(pair[0]);
				}
			}
		}
	}
	if (result.size() != vershiny) {
		cout << "There is a cycle in GTN. Topological sort is imposssible" << endl;
	}
	else {
		for (int vershina : result) {
			cout << stations[vershina] << endl;
		}
	}
}

//bool Network::CheckByName(const Pipeline& pipe, string param) {
//	return (pipe.kilometre.find(param) != string::npos);
//}
//
//bool Network::CheckByRepair(const Pipeline& pipe, bool param) {
//	return (pipe.isRepaired == param);
//}
//
//void Network::FindAllPipelinesByName() {
//	string name;
//	cout << "Enter pileline name for searching: ";
//	READ_LINE(cin, name);
//	unordered_set<int> result = FindPipelinesByFilter(pipes, CheckByName, name);
//	for (int id : result) {
//		cout << pipes[id];
//	}
//}
//
//void Network::FindAllPipelinesByRepair() {
//	cout << "Enter station status for searching: ";
//	bool flag = CorrectInput(false, true);
//	unordered_set<int> result = FindPipelinesByFilter(pipes, CheckByRepair, flag);
//	for (int id : result) {
//		cout << pipes[id];
//	}
//}
