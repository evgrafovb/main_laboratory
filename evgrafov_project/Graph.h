#pragma once
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Network.h"

class Graph
{
	vector<vector<int>> ribs;
	unordered_map<int, int> stepeny;
	vector<vector<pair<int, double>>> weights;
	vector<vector<int>> capacities;
	int sourceID;
	int sinkID;
public:
	Graph(vector<vector<int>>& rebra, unordered_map<int, int>& stepeny_vershin);
	Graph(vector<vector<pair<int, double>>>& w, int& source, int& sink);
	Graph(vector<vector<int>>& cap, int& source, int& sink);
	vector<int> TopologicalSort();
	void ShowTopologicalSort(const vector<int>& result);
	vector<int> FindWay();
	void ShowShortestWay(const vector<int>& result, int vershina);
	bool bfs(vector<vector<int>>& graph, int source, int sink, vector<int>& parent);
	int FindMaxFlow();
	void ShowMaxFlow(const int& maxFlow);
};
