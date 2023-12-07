#pragma once
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include <unordered_map>
#include <unordered_set>

class Network
{
	unordered_map<int, Pipeline> pipes;
	unordered_map<int, CompressorStation> stations;

public:
	unordered_map<int, Pipeline> getPipelines();
	unordered_map<int, CompressorStation> getStations();
	void AddNewPipe(const Pipeline& pipe);
	void AddNewStation(const CompressorStation& station);
	void ShowAllObjects();
	void EditPipeline(int ID);
	void EditStation();
	void SaveData();
	void LoadDate();
	void DeletePipeline(int ID);
	void DeleteStation();
	void ClearPipelines();
	void ClearStations();
	void AddConnection();
	void Disconnection();
	void ShowNetwork();
	int getPipelineID();
	vector<vector<int>> CreateRibs();
	unordered_map<int, int> StepenyVershin();
	void TopologicalSort();
	vector<vector<pair<int, double>>> CreateWeights();
	void FindWay();
	/*bool CheckByName(const Pipeline& pipe, string param);
	bool CheckByRepair(const Pipeline& pipe, bool param);
	void FindAllPipelinesByName();
	void FindAllPipelinesByRepair();*/

	

};

//template <typename type>
//using PipelineFilter = bool(*)(const Pipeline& pipe, type param);
//
//template <typename type>
//unordered_set<int> FindPipelinesByFilter(const unordered_map<int, Pipeline>& pipes, PipelineFilter<type> f, type param) {
//	unordered_set<int> result;
//	for (auto& [id, pipe] : pipes) {
//		if (f(pipe, param)) {
//			result.insert(id);
//		}
//	}
//	if (!(size(result))) {
//		cout << "No pipelines found" << endl;
//	}
//	return result;
//}