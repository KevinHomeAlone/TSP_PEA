#pragma once
#include <vector>

using namespace std;

class DynamicSolution
{
public:
	//static vector<vector<vector<int>>> solvedPaths;
	DynamicSolution();
	~DynamicSolution();
	//static int solve(vector<vector<int>>);
	//static int recc(vector<vector<int>>, vector<int>, int);
	static int solveLoop(vector<vector<int>>);
};

