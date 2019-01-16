#include "pch.h"
#include "DynamicSolution.h"
#include <vector>
#include <algorithm>
#include<iostream>
#include <bitset>

using namespace std;

DynamicSolution::DynamicSolution()
{
}


DynamicSolution::~DynamicSolution()
{
}


int DynamicSolution::solveLoop(vector<vector<int>> costMatrix) {
	int citiesCount = costMatrix.size();

	vector<vector<int>> best;
	best.resize(1 << (citiesCount - 1));
	//std::cout << "citiesCount : " << citiesCount << endl;
	//std::cout << "1 << (citiesCount - 1) :  " << (1 << (citiesCount - 1)) << endl;
	for (int i = 0; i < (1 << (citiesCount - 1)); i++) {
		best[i].resize(citiesCount);
		for (int j = 0; j < citiesCount; j++) {
			best[i][j] = INT_MAX;
		}
	}

	for (int visited = 1; visited < (1 << (citiesCount - 1)); ++visited) {
		for (int last = 0; last < (citiesCount - 1); ++last) {

			if (!(visited & (1 << last))) continue;

			if (visited == (1 << last)) {
				best[visited][last] = costMatrix[citiesCount - 1][last];
			}else {
				int prev_visited = visited ^ (1 << last);
				for (int prev = 0; prev < citiesCount - 1; ++prev) {
					if (!(prev_visited & 1 << prev)) continue;
					best[visited][last] = min(
						best[visited][last],
						costMatrix[last][prev] + best[prev_visited][prev]
					);
				}
			}
		}
	}

	int cheapestPathCost = INT_MAX;
	for (int last = 0; last < citiesCount - 1; ++last) {
		cheapestPathCost = min(
			cheapestPathCost,
			costMatrix[last][citiesCount - 1] + best[(1 << (citiesCount - 1)) - 1][last]
		);
		bitset<8> x(best[(1 << (citiesCount - 1)) - 1][last]);
		std::cout << endl << x << endl;
	}

	return cheapestPathCost;
}
