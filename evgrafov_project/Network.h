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
	const unordered_map<int, Pipeline>& getPipelines();
	const unordered_map<int, CompressorStation>& getStations();
	const Pipeline& getPipe(int id);
	const CompressorStation& getStation(int id);
	void AddNewPipe(const Pipeline& pipe);
	void AddNewStation(const CompressorStation& station);
	void ShowAllObjects();
	void EditPipeline(int ID);
	void EditStation();
	void SaveData();
	void LoadData();
	void DeletePipeline(int ID);
	void DeleteStation();
	void ClearPipelines();
	void ClearStations();
	void AddConnection();
	void Disconnection();
	void ShowNetwork();
	int getPipelineID();

	vector<vector<int>> CreateRibs();
	int StationsAmount();
	unordered_map<int, int> StepenyVershin();
	vector<vector<pair<int, double>>> CreateWeights();
	int SourceID();
	int SinkId();
	vector<vector<int>> CreateCapacities();
};
