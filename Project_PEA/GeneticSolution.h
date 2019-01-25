/*
	Author:
	Kevin Pieprzak
*/
#pragma once
#include <vector>

using namespace std;
class GeneticSolution
{
public:
	GeneticSolution(float, float);
	~GeneticSolution();
	float mutationProb;
	float crossoverProb;
	vector<vector<int>> population;
	__int64 counter;
	double frequency;
	void start();
	double stop();
	double evolve(vector<vector<int>> matrix, int size, int cities, vector<vector<int>>& population, int mutationType);
	vector<vector<int>> createPopulation(int size, int cities);
	void merge(vector<vector<int>> matrix, int cities, vector<vector<int>> &population, vector<vector<int>>& hlp, int beg, int mid, int end);
	void mergesort(vector<vector<int>> matrix, int cities, vector<vector<int>> &population, vector<vector<int>>& hlp, int beg, int end);
	std::vector<int> findBest(vector<vector<int>> matrix, int cities, int size, vector<vector<int>> routes);
	void permutation(vector<vector<int>>& routes, int size, int cities);
	std::vector<int>tournamentSelection(vector<vector<int>> matrix, int size, int cities, vector<vector<int>> routes, int tournament_size);
	double route(vector<vector<int>> matrix, int cities, vector<int> perm);
	std::vector<int> crossover(int cities, vector<int> parent1, vector<int> parent2);
	void mutateScramble(vector<int> &way);
	void mutateSwap(vector<int> &way);
	void mutateInverse(vector<int> &way);
};

