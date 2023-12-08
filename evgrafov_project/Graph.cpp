#include "Graph.h"
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Network.h"
#include <queue>

Graph::Graph(vector<vector<int>>& rebra, unordered_map<int, int>& stepeny_vershin) {
	ribs = rebra;
	stepeny = stepeny_vershin;
}

//vector<vector<int>> Graph::CreateRibs(unordered_map<int, Pipeline>& pipes) {
//	vector<vector<int>> rebra;
//	for (auto& [id, pipe] : pipes) {
//		if (pipe.getPipeCSin() != -1) {
//			rebra.push_back({ pipe.getPipeCSin(), pipe.getPipeCSout() });
//		}
//	}
//	return rebra;
//}
//
//int Graph::StationsAmount(unordered_map<int, CompressorStation>& stations) {
//	int vershiny = 0;
//	for (auto& [id, station] : stations) {
//		if (station.getStationStart() > 0 || station.getStationEnd() > 0) {
//			if (id > vershiny) {
//				vershiny = id;
//			}
//		}
//	}
//	return vershiny + 1;
//}
//
//unordered_map<int, int> Graph::StepenyVershin(unordered_map<int, CompressorStation>& stations) {
//	unordered_map<int, int> stepeny_vershin;
//	for (auto& [id, station] : stations) {
//		if (station.getStationStart() > 0 || station.getStationEnd() > 0) {
//			stepeny_vershin.insert(pair{ id, station.getStationStart() });
//		}
//	}
//	return stepeny_vershin;
//}
//
vector<int> Graph::TopologicalSort() {
	auto vershiny = stepeny.size();
	auto rebra = ribs;
	vector<int> result;
	queue<int> q;
	for (auto& [id, stepen] : stepeny) {
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
				stepeny[pair[0]]--;
				if (stepeny[pair[0]] == 0) {
					q.push(pair[0]);
				}
			}
		}
	}
	return result;
}
void Graph::ShowTopologicalSort(const vector<int>& result) {
	if (result.size() != stepeny.size()) {
		cout << "There is a cycle in GTN. Topological sort is imposssible" << endl;
	}
	else {
		for (int vershina : result) {
			cout << vershina << endl;
		}
	}
}
//
//vector<vector<pair<int, double>>> Graph::CreateWeights(unordered_map<int, Pipeline>& pipes) {
//	vector<vector<pair<int, double>>> weights(StationsAmount());
//	for (auto& [id, pipe] : pipes) {
//		if (pipe.getPipeCSin() != -1) {
//			weights[pipe.getPipeCSin()].push_back({ pipe.getPipeCSout(), pipe.getPipeLength() });
//		}
//	}
//	return weights;
//}
//
//void Graph::FindWay() {
//	cout << "Enter source CS's ID to find the shortest distances: ";
//	int stationID = CorrectIntID();
//	if (CheckID(stations, stationID)) {
//		auto weights = CreateWeights();
//		int n = weights.size();
//		vector<double> distances(n, INF);
//		vector<bool> visited(n, false);
//		distances[stationID] = 0;
//		priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
//		pq.push({ stationID, 0.0 });
//		while (!pq.empty()) {
//			int v1 = pq.top().first;
//			pq.pop();
//			visited[v1] = true;
//			for (auto& rebro : weights[v1]) {
//				int v2 = rebro.first;
//				double weight = rebro.second;
//				if (!visited[v2] && distances[v1] + weight < distances[v2]) {
//					distances[v2] = distances[v1] + weight;
//					pq.push({ v2, distances[v2] });
//				}
//			}
//		}
//		cout << "Vershina\tDistances from source" << endl;
//		for (int i = 0; i < n; i++) {
//			if (distances[i] != INF) {
//				cout << i << "\t\t" << distances[i] << endl;
//			}
//		}
//	}
//}
//
//vector<vector<int>> Graph::CreateCapacities(unordered_map<int, Pipeline>& pipes) {
//	vector<vector<int>> capacities(StationsAmount());
//	for (auto& [id, pipe] : pipes) {
//		if (pipe.getPipeCSin() != -1) {
//			capacities[pipe.getPipeCSin()][pipe.getPipeCSout()] = pipe.getPipeDiametre();
//		}
//	}
//	return capacities;
//}
//
//void Graph::FindMaxFlow() {
//	//cout << "Enter source CS's ID to find max flow: ";
//	//int source = CorrectIntID();
//	//cout << "Enter sink CS's ID to find max flow: ";
//	//int sink = CorrectIntID();
//	//if (CheckID(stations, source) && CheckID(stations, sink) && source != sink) {
//	//	vector<vector<int>> residualGraph(StationsAmount(), vector<int>(StationsAmount(), 0));
//	//	int n = StationsAmount();
//	//	//vector<vector<int>> residualGraph(n); // Residual graph to store the residual capacities
//	//	//vector<int> parent(n); // Array to store the augmented path
//
//	//	// Initialize the residual graph as the original graph
//	//	/*for (int i = 0; i < n; i++) {
//	//		for (int j = 0; j < n; j++) {
//	//			residualGraph[i][j] = capacities[i][j];
//	//		}
//	//	}*/
//
//	//	int maxFlow = 0; // Initialize the maximum flow
//
//	//	// Augment the flow while there is an augmenting path in the residual graph
//	//	while (true)
//	//	{
//	//		vector<int> parent(n, -1);
//	//		vector<bool> used(n, false);
//	//		queue<int> q;
//
//	//		used[source] = true;
//	//		q.push(source);
//
//	//		while (!q.empty())
//	//		{
//	//			int v = q.front();
//	//			q.pop();
//	//			for (int i = 0; i < n; i++)
//	//			{
//	//				if (!used[i] && residualGraph[v][i] > 0)
//	//				{
//	//					parent[i] = v;
//	//					used[i] = true;
//	//					q.push(i);
//	//				}
//	//			}
//	//		}
//	//		if (!used[sink])
//	//			break;
//	//		int augFlow = INF;
//
//	//		int ptr = sink;
//	//		while (ptr != source)
//	//		{
//	//			augFlow = min(augFlow, residualGraph[parent[ptr]][ptr]);
//	//			ptr = parent[ptr];
//	//		}
//	//		ptr = sink;
//	//		while (ptr != source)
//	//		{
//	//			residualGraph[parent[ptr]][ptr] -= augFlow;
//	//			residualGraph[ptr][parent[ptr]] += augFlow;
//	//			ptr = parent[ptr];
//	//		}
//	//		maxFlow += augFlow;
//	//	}
//
//
//	//	cout << "Max flow: " << maxFlow << endl;
//	//}
//}
