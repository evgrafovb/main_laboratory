#pragma once
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Network.h"

class Graph
{
	vector<vector<int>> ribs;
	unordered_map<int, int> stepeny;
public:
	Graph(vector<vector<int>>& rebra, unordered_map<int, int>& stepeny_vershin);
//	vector<vector<int>> CreateRibs(unordered_map<int, Pipeline>& pipes);
//	int StationsAmount(unordered_map<int, CompressorStation>& stations);
//	unordered_map<int, int> StepenyVershin(unordered_map<int, CompressorStation>& stations);
	vector<int> TopologicalSort();
	void ShowTopologicalSort(const vector<int>& result);
//	vector<vector<pair<int, double>>> CreateWeights(unordered_map<int, Pipeline>& pipes);
//	void FindWay();
//	vector<vector<int>> CreateCapacities(unordered_map<int, Pipeline>& pipes);
//	void FindMaxFlow();
};

