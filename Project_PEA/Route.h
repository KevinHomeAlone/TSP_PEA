/*
	Author:
	Kevin Pieprzak
*/
#pragma once

#include <stdio.h>
#include <vector>

using namespace std;

class Route
{
public:
	Route();
	~Route();
	Route(float, const vector<int>);
	vector<int> path;
	int cost;
	int calcCost(const vector<vector<int>>, bool);
	Route& swap(int, int);
	Route& reverse(int, int);
	Route& generateInitSolution(const vector<vector<int>>);
	Route& updateCost(const vector<vector<int>>);
	bool nextPermutation();
	friend ostream& operator<<(ostream&, const Route&);
};

