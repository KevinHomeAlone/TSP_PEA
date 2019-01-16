/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include "RandomGenerator.h"

using namespace std;


RandomGenerator::RandomGenerator()
{
}


RandomGenerator::~RandomGenerator()
{
}

vector<vector<int>> RandomGenerator::generate(int citiesQuantity) {
	vector<vector<int>> matrix;
	matrix.resize(citiesQuantity);
	for (int i = 0; i < citiesQuantity; i++)
		matrix[i].resize(citiesQuantity);
	for (int i = 0; i < citiesQuantity; i++) {
		for (int j = 0; j < citiesQuantity; j++) {
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = rand() % 100;
		}
	}

	return matrix;
}