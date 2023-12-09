#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <set>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"
#include "Network.h"
#include "Graph.h"
#include <unordered_map>
#include <queue>

using namespace std;

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
	return (double((station.getStationWorks() - station.getStationBusyWorks()) * 100) / station.getStationWorks()) >= param;
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

void FindAllStationsByName(Network& net) {
	string name;
	cout << "Enter station name for searching: ";
	READ_LINE(cin, name);
	for (int id : FindStationsByFilter(net.getStations(), CheckByName, name)) {
		cout << net.getStation(id);
	}
}

void FindAllStationsByBusyWorkshops(Network& net) {
	cout << "Enter percent of unworking stations for searching: ";
	double percent = CorrectInput(0.0, 100.0);
	for (int id : FindStationsByFilter(net.getStations(), CheckByUnworkingWorkshops, percent)) {
		cout << net.getStation(id);
	}
}

void FindMenu() {
	cout << "1. Find pipelines by name" << endl
		<< "2. Find pipelines by repair status" << endl
		<< "Enter a number from 1 to 2: ";
}

unordered_set<int> PackEdit(Network& net) {
	unordered_set<int> pipesID{};
	FindMenu();
	switch (CorrectInput(1, 2)) {
	case 1: {
		string name;
		cout << "Input pileline name for searching: ";
		READ_LINE(cin, name);
		for (int id : FindPipelinesByFilter(net.getPipelines(), CheckByName, name)) {
			cout << net.getPipe(id);
			pipesID.insert(id);
		}
		break;
	}
	case 2: {
		bool flag;
		cout << "Input station status for searching: ";
		flag = CorrectInput(false, true);
		for (int id : FindPipelinesByFilter(net.getPipelines(), CheckByRepair, flag)) {
			cout << net.getPipe(id);
			pipesID.insert(id);
		}
		break;
	}
	}
	return pipesID;
}

unordered_set<int> SelectPipesID(Network& net) {
	unordered_set<int> pipesID;
	while (1) {
		cout << "Input ID of pipeline or 0 to complete: ";
		int id;
		id = CorrectIntID();
		if (id) {
			if (CheckID(net.getPipelines(), id)) {
				cout << net.getPipe(id);
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
	return pipesID;
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
		<< "10. Find stations by name" << endl
		<< "11. Find stations by percent of not working workshops" << endl
		<< "12. Pack editing of pipelines" << endl
		<< "13. Connect pipeline" << endl
		<< "14. Disconnect pipeline" << endl
		<< "15. Show all objects in Gas Transmission Network" << endl
		<< "16. Network's sort" << endl
		<< "17. Find the shortest way" << endl
		<< "18. Calculate max stream" << endl
		<< "0. Exit" << endl << endl
		<< "Enter a number from 0 to 18: ";
}

int main() {
	redirect_output_wrapper cerr_out(cerr);
	ofstream logfile("logging.txt");
	if (logfile)
		cerr_out.redirect(logfile);
	Network net;
	while (1) {
		PrintMenu();
		switch (CorrectInput(0, 18)) {
		case 1: {
			Pipeline pipe;
			cin >> pipe;
			net.AddNewPipe(pipe);
			break;
		}
		case 2: {
			CompressorStation station;
			cin >> station;
			net.AddNewStation(station);
			break;
		}
		case 3: {
			net.ShowAllObjects();
			break;
		}
		case 4: {
			net.EditPipeline(0);
			break;
		}
		case 5: {
			net.EditStation();
			break;
		}
		case 6: {
			net.SaveData();
			break;
		}
		case 7: {
			net.LoadData();
			break;
		}
		case 8: {
			net.DeletePipeline(0);
			break;
		}
		case 9: {
			net.DeleteStation();
			break;
		}
		case 10: {
			FindAllStationsByName(net);
			break;
		}
		case 11: {
			FindAllStationsByBusyWorkshops(net);
			break;
		}
		case 12: {
			unordered_set<int> pipesID = PackEdit(net);
			bool flag = true;
			while (flag) {
				EditMenu();
				switch (CorrectInput(0, 4)) {
				case 1: {
					pipesID = SelectPipesID(net);
					break;
				}
				case 2: {
					for (const int& id : pipesID) {
						net.EditPipeline(id);
					}
					break;
				}
				case 3: {
					for (const int& id : pipesID) {
						net.DeletePipeline(id);
					}
					break;
				}
				case 4: {
					for (auto& [id, pipe] : net.getPipelines()) {
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
		case 13: {
			net.AddConnection();
			break;
		}
		case 14: {
			net.Disconnection();
			break;
		}
		case 15: {
			net.ShowNetwork();
			break;
		}
		case 16: {
			auto rebra = net.CreateRibs();
			auto stepeny_vershin = net.StepenyVershin();
			Graph g(rebra, stepeny_vershin);
			g.ShowTopologicalSort(g.TopologicalSort());
			break;
		}
		case 17: {
			auto weights = net.CreateWeights();
			auto SourceID = net.SourceID();
			auto SinkID = net.SinkId();
			Graph g(weights, SourceID, SinkID);
			g.ShowShortestWay(g.FindWay(), SinkID);
			break;
		}
		case 18: {
			auto capacities = net.CreateCapacities();
			auto SourceID = net.SourceID();
			auto SinkId = net.SinkId();
			Graph g(capacities, SourceID, SinkId);
			g.ShowMaxFlow(g.FindMaxFlow());
			break;
		}
		case 0:
			return 0;
		}
	}
	return 0;
}