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

int Network::StationsAmount() {
	int vershiny = 0;
	for (auto& [id, station] : stations) {
		if (station.getStationStart() > 0 || station.getStationEnd() > 0) {
			if (id > vershiny) {
				vershiny = id;
			}
		}
	}
	return vershiny + 1;
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

const unordered_map<int, Pipeline>& Network::getPipelines() {
	return pipes;
}

const unordered_map<int, CompressorStation>& Network::getStations() {
	return stations;
}

const Pipeline& Network::getPipe(int id) {
	if (CheckID(pipes, id)) {
		return pipes[id];
	}
}

const CompressorStation& Network::getStation(int id) {
	if (CheckID(stations, id)) {
		return stations[id];
	}
}

//void Network::TopologicalSort() {
//	auto rebra = CreateRibs();
//	auto stepeny_vershin = StepenyVershin();
//	int vershiny = stepeny_vershin.size();
//	vector<int> result;
//	queue<int> q;
//	for (auto& [id, stepen] : stepeny_vershin) {
//		if (stepen == 0) {
//			q.push(id);
//		}
//	}
//	while (!q.empty()) {
//		int vershina = q.front();
//		q.pop();
//		result.insert(result.begin(), vershina);
//		for (auto& pair : rebra) {
//			if (pair[1] == vershina) {
//				stepeny_vershin[pair[0]]--;
//				if (stepeny_vershin[pair[0]] == 0) {
//					q.push(pair[0]);
//				}
//			}
//		}
//	}
//	if (result.size() != vershiny) {
//		cout << "There is a cycle in GTN. Topological sort is imposssible" << endl;
//	}
//	else {
//		for (int vershina : result) {
//			cout << stations[vershina] << endl;
//		}
//	}
//}

vector<vector<pair<int, double>>> Network::CreateWeights() {
	vector<vector<pair<int, double>>> weights(StationsAmount());
	for (auto& [id, pipe] : pipes) {
		if (pipe.getPipeCSin() != -1) {
			weights[pipe.getPipeCSin()].push_back({ pipe.getPipeCSout(), pipe.getPipeLength() });
		}
	}
	return weights;
}

void Network::FindWay() {
	cout << "Enter source CS's ID to find the shortest distances: ";
	int stationID = CorrectIntID();
	if (CheckID(stations, stationID)) {
		auto weights = CreateWeights();
		int n = weights.size();
		vector<double> distances(n, INF);
		vector<bool> visited(n, false);
		distances[stationID] = 0;
		priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
		pq.push({ stationID, 0.0 });
		while (!pq.empty()) {
			int v1 = pq.top().first;
			pq.pop();
			visited[v1] = true;
			for (auto& rebro : weights[v1]) {
				int v2 = rebro.first;
				double weight = rebro.second;
				if (!visited[v2] && distances[v1] + weight < distances[v2]) {
					distances[v2] = distances[v1] + weight;
					pq.push({ v2, distances[v2] });
				}
			}
		}
		cout << "Vershina\tDistances from source" << endl;
		for (int i = 0; i < n; i++) {
			if (distances[i] != INF) {
				cout << i << "\t\t" << distances[i] << endl;
			}
		}
	}
}

vector<vector<int>> Network::CreateCapacities() {
	vector<vector<int>> capacities(StationsAmount());
	for (auto& [id, pipe] : pipes) {
		if (pipe.getPipeCSin() != -1) {
			capacities[pipe.getPipeCSin()][pipe.getPipeCSout()] = pipe.getPipeDiametre();
		}
	}
	return capacities;
}

//void Network::FindMaxFlow() {
//	cout << "Enter source CS's ID to find max flow: ";
//	int source = CorrectIntID();
//	cout << "Enter sink CS's ID to find max flow: ";
//	int sink = CorrectIntID();
//	if (CheckID(stations, source) && CheckID(stations, sink) && source != sink) {
//		vector<vector<int>> residualGraph(StationsAmount(), vector<int>(StationsAmount(), 0));
//		int n = StationsAmount();
//		//vector<vector<int>> residualGraph(n); // Residual graph to store the residual capacities
//		//vector<int> parent(n); // Array to store the augmented path
//
//		// Initialize the residual graph as the original graph
//		/*for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				residualGraph[i][j] = capacities[i][j];
//			}
//		}*/
//
//		int maxFlow = 0; // Initialize the maximum flow
//
//		// Augment the flow while there is an augmenting path in the residual graph
//		while (true)
//		{
//			vector<int> parent(n, -1);
//			vector<bool> used(n, false);
//			queue<int> q;
//
//			used[source] = true;
//			q.push(source);
//
//			while (!q.empty())
//			{
//				int v = q.front();
//				q.pop();
//				for (int i = 0; i < n; i++)
//				{
//					if (!used[i] && residualGraph[v][i] > 0)
//					{
//						parent[i] = v;
//						used[i] = true;
//						q.push(i);
//					}
//				}
//			}
//			if (!used[sink])
//				break;
//			int augFlow = INF;
//
//			int ptr = sink;
//			while (ptr != source)
//			{
//				augFlow = min(augFlow, residualGraph[parent[ptr]][ptr]);
//				ptr = parent[ptr];
//			}
//			ptr = sink;
//			while (ptr != source)
//			{
//				residualGraph[parent[ptr]][ptr] -= augFlow;
//				residualGraph[ptr][parent[ptr]] += augFlow;
//				ptr = parent[ptr];
//			}
//			maxFlow += augFlow;
//		}
//
//
//		cout << "Max flow: " << maxFlow << endl;
//	}
//}
