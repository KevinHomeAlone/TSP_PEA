/*
	Author:
	Kevin Pieprzak
*/
#include <stdio.h>
#include <string>
#include <vector>
#include "Route.h"

using namespace std;

class TabuSolution {
private:
	vector<int> route;
	int shortestDistance = 99999;
public:
	TabuSolution();
	~TabuSolution();
	Route tabuSearch(const vector<vector<int>>, const unsigned int, const unsigned int, const unsigned int,
		const long long, const bool, const unsigned int, const bool);
	vector<vector<int>> a;
	Route r;
};

