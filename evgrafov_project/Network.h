#pragma once
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include <unordered_map>


class Network
{
	//unordered_map<int, Pipeline> pipes;
	//unordered_map<int, CompressorStation> stations;

public:
	int getPipelineID(unordered_map<int, Pipeline>& pipes);
	vector<int> TopologicalSort(vector<vector<int>>& rebra, unordered_map<int, int>& stepeny_vershin);
};

