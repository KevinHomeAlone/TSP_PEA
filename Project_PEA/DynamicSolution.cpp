#include "pch.h"
#include "DynamicSolution.h"
#include <vector>
#include <algorithm>

using namespace std;

DynamicSolution::DynamicSolution()
{
}


DynamicSolution::~DynamicSolution()
{
}

int DynamicSolution::solve(vector<vector<int>> matrix) {

	vector<int> test;
	//solvedPaths.resize(1);



	return recc(matrix, test, 2);
}

int DynamicSolution::recc(vector<vector<int>> costsMatrix, vector<int> nodesSet, int node) {
	vector<int> tempSolution;
	if (nodesSet.size() == 0) {
		tempSolution.resize(3);
		tempSolution[0] = node;
		tempSolution[1] = 0;
		tempSolution[2] = costsMatrix[node][0];
		//solvedPaths[0].insert(tempSolution);

	}
	return tempSolution[2];
}
