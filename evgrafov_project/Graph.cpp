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

Graph::Graph(vector<vector<pair<int, double>>>& w, int& source, int& sink) {
	weights = w;
	sourceID = source;
	sinkID = sink;
}
Graph::Graph(vector<vector<int>>& cap, int& source, int& sink) {
	capacities = cap;
	sourceID = source;
	sinkID = sink;
}

vector<int> Graph::TopologicalSort() {
	int vershiny = stepeny.size();
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
		for (auto& pair : ribs) {
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

vector<int> Graph::FindWay() {
	if (sourceID && sinkID) {
		int n = weights.size();
		vector<int> parent(n, -1);
		vector<double> distances(n, INF);
		distances[sourceID] = 0;
		priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
		pq.push({ sourceID, 0.0 });
		while (!pq.empty()) {
			int v1 = pq.top().first;
			double dist = pq.top().second;
			pq.pop();
			if (dist > distances[v1]) {
				continue;
			}
			for (auto& rebro : weights[v1]) {
				int v2 = rebro.first;
				double weight = rebro.second;
				if (distances[v1] + weight < distances[v2]) {
					distances[v2] = distances[v1] + weight;
					parent[v2] = v1;
					pq.push({ v2, distances[v2] });
				}
			}
		}
		if (distances[sinkID] != INF) {
			cout << "The shortest distance: " << distances[sinkID] << endl;
		}
		else {
			cout << "There is no way" << endl;
			parent.resize(0);
		}
		return parent;
	}
}

void Graph::ShowShortestWay(const vector<int>& result, int vershina) {
	if (sourceID && sinkID && result.size()) {
		if (result[vershina] == -1) {
			cout << vershina << endl;
			return;
		}
		ShowShortestWay(result, result[vershina]);
		cout << vershina << endl;
	}
}

bool Graph::bfs(vector<vector<int>>& graph, int source, int sink, vector<int>& parent) {
	vector<bool> visited(graph.size(), false);
	queue<int> q;
	q.push(source);
	visited[source] = true;
	parent[source] = -1;
	while (!q.empty()) {
		int v1 = q.front();
		q.pop();

		for (int v2 = 0; v2 < graph.size(); v2++) {
			if (!visited[v2] && graph[v1][v2] > 0) {
				q.push(v2);
				parent[v2] = v1;
				visited[v2] = true;
			}
		}
	}
	return visited[sink];
}

int Graph::FindMaxFlow() {
	if (sourceID && sinkID) {
		int n = capacities.size();
		vector<int> parent(n);
		int maxFlow = 0;
		while (bfs(capacities, sourceID, sinkID, parent)) {
			int pathFlow = INF;
			for (int v2 = sinkID; v2 != sourceID; v2 = parent[v2]) {
				int v1 = parent[v2];
				pathFlow = min(pathFlow, capacities[v1][v2]);
			}
			for (int v2 = sinkID; v2 != sourceID; v2 = parent[v2]) {
				int v1 = parent[v2];
				capacities[v1][v2] -= pathFlow;
				capacities[v2][v1] += pathFlow;
			}
			maxFlow += pathFlow;
		}
		return maxFlow;
	}
	else {
		return 0;
	}
}

void Graph::ShowMaxFlow(const int& maxFlow) {
	if (sourceID && sinkID && maxFlow) {
		cout << "Max flow: " << maxFlow << endl;
	}
}
