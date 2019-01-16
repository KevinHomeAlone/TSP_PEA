/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include "Route.h"
#include <iostream>
#include <time.h>

using namespace std;

Route::Route() {

}

Route::~Route() {

}

Route::Route(float cost, const vector<int> path) {
	this->cost = cost;
	this->path = path;
}

Route &Route::generateInitSolution(const vector<vector<int>> mat) {
	for (int i = 0; i < mat.size(); i++) {
		path.push_back(i);
	}
	srand(time(NULL));
	for (int i = (mat.size() - 1); i >= 0; i--) {
		int j = rand() % mat.size();
		swap(path[i], path[j]);
	}
	updateCost(mat);
	return *this;
}

Route &Route::updateCost(const vector<vector<int>> mat) {
	cost = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		cost += mat[path[i]][path[i + 1]];
	}
	cost += mat[path[path.size() - 1]][path[0]];
	return *this;
}

Route &Route::swap(int i, int j) {
	int tmp = path[i];
	path[i] = path[j];
	path[j] = tmp;
	return *this;
}


std::ostream& operator<<(ostream& os, const Route& obj) {
	os << endl << "Path vector: " << endl;
	for (int i = 0; i < obj.path.size(); i++) {
		os << obj.path[i] << "    ";
	}
	os << obj.path[0];
	os << endl << "Path cost: " << obj.cost << endl;
	os << endl;
	return os;
}