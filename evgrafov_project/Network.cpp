#include "Network.h"
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include <queue>

int Network::getPipelineID(unordered_map<int, Pipeline>& pipes) {
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

vector<int> Network::TopologicalSort(vector<vector<int>>& rebra, unordered_map<int, int>& stepeny_vershin) {
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
		result.resize(0);
	}
	return result;
}
