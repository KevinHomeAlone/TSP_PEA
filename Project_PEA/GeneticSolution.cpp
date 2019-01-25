/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include "GeneticSolution.h"


GeneticSolution::GeneticSolution(float mutationProb, float crossoverProb)
{
	this->mutationProb = mutationProb;
	this->crossoverProb = crossoverProb;
}


GeneticSolution::~GeneticSolution()
{
}

using namespace std;

void GeneticSolution::permutation(vector<vector<int>>& routes, int size, int cities) {
	int*perm = new int[cities];
	vector<int> temp;
	for (int i = 0; i < size; i++) {
		for (int c = 0; c < cities; c++)
		{
			bool check;
			int random = 0;
			do {
				random = rand() % cities;
				check = true;
				for (int j = 0; j < c; j++) {
					if (random == perm[j]) {
						check = false;
						break;
					}
				}

			} while (!check);
			perm[c] = random;

			temp.push_back(perm[c]);
		}
		routes.push_back(temp);
		temp.clear();
	}
	delete[]perm;
}



double GeneticSolution::route(vector<vector<int>> matrix, int cities, vector<int> perm) {
	double cost = 0;

	for (int i = 0; i < cities - 1; i++)
	{
		cost += matrix[perm[i]][perm[i + 1]];
	}
	cost += matrix[perm[cities - 1]][perm[0]];//droga od ostatniego do pierwszego miasta

	return cost;
}

vector<vector<int>> GeneticSolution::createPopulation(int size, int cities) {

	std::vector<vector<int>> population;
	/*tworze populacje skladajaca sie z wielkosc losowych drog*/
	permutation(population, size, cities);
	return population;
}

void GeneticSolution::merge(vector<vector<int>> matrix, int cities, vector<vector<int>> &population, vector<vector<int>>& hlp, int beg, int mid, int end) {

	int i, j, q;
	for (i = beg; i <= end; i++)
		hlp[i] = population[i];  // Skopiowanie danych do tablicy pomocniczej
	i = beg;
	j = mid + 1;
	q = beg;                 // Ustawienie wskaznikow tablic
	while (i <= mid && j <= end) {         // Przenoszenie danych z sortowaniem ze zbiorów pomocniczych do tablicy glownej
		if (route(matrix, cities, hlp[i]) < route(matrix, cities, hlp[j]))
			population[q++] = hlp[i++];
		else
			population[q++] = hlp[j++];
	}
	while (i <= mid)
		population[q++] = hlp[i++]; // Przeniesienie nieskopiowanych danych ze zbioru pierwszego w przypadku, gdy drugi zbior sie skonczyl

}

void GeneticSolution::mergesort(vector<vector<int>> matrix, int cities, vector<vector<int>> &population, vector<vector<int>>& hlp, int beg, int end) {
	int mid;
	if (beg < end) {
		mid = (beg + end) / 2;
		mergesort(matrix, cities, population, hlp, beg, mid);    // Dzielenie lewej czesci
		mergesort(matrix, cities, population, hlp, mid + 1, end);   // Dzielenie prawej czesci
		merge(matrix, cities, population, hlp, beg, mid, end);   // Laczenie czesci lewej i prawej
	}
	this->population = population;

}

double GeneticSolution::evolve(vector<vector<int>> matrix, int size, int cities, vector<vector<int>>& population, int mutationType) {
	vector<int> parent1(cities);
	vector<int> parent2(cities);
	vector<int> child1(cities);
	vector<int> child2(cities);


	for (int i = 0; i < size; i++) {
		//krzyzuje osobniki i powstale w wyniku krzyzowki dzieci wpisuje na koncu populacji
		if (((double)rand() / (RAND_MAX)) <= crossoverProb) {
			parent1 = tournamentSelection(matrix, size, cities, population, 5);
			parent2 = tournamentSelection(matrix, size, cities, population, 5);
			child1 = crossover(cities, parent1, parent2);
			child2 = crossover(cities, parent2, parent1);

			//mutuje powstale osobniki
			if (((double)rand() / (RAND_MAX)) <= mutationProb) {
				if (mutationType == 1) {
					mutateScramble(child1);
					mutateScramble(child2);
				}
				else if (mutationType == 2) {
					mutateSwap(child1);
					mutateSwap(child2);
				}
				else {
					mutateInverse(child1);
					mutateInverse(child2);
				}
			}
			population.push_back(child1);
			population.push_back(child2);
		}
	}


	vector<vector<int>> hlp(population.size());
	//sortuje trasy po ich wartosciach malejaco
	mergesort(matrix, cities, population, hlp, 0, population.size() - 1);

	//i usuwamy najgorsze z nich, aby w efekcie populacja po krzyzowaniu i mutacji byla wielkosci poczatkowej
	do {
		population.pop_back();
	} while (population.size() > size);

	//po sortowaniu najlepszy osobnik znajduje sie na pierwszej pozycji
	double best_route = route(matrix, cities, population[0]);
	return best_route;
}

vector<int> GeneticSolution::findBest(vector<vector<int>> matrix, int cities, int size, vector<vector<int>> routes) {
	vector<int> best(cities);

	for (int i = 0; i < cities; i++) {
		best[i] = routes[0][i];
	}
	for (int i = 0; i < size; i++) {
		if (route(matrix, cities, best) > route(matrix, cities, routes[i])) {
			best = routes[i];

		}
	}
	return best;
}

vector<int> GeneticSolution::tournamentSelection(vector<vector<int>> matrix, int size, int cities, vector<vector<int>> routes, int tournament_size) {
	int rand_id;
	vector<int> way(cities);
	vector<vector<int>> routes1(tournament_size, std::vector<int>(cities));

	for (int i = 0; i < tournament_size; i++) {
		rand_id = rand() % size;
		for (int j = 0; j < cities; j++) {
			routes1[i][j] = routes[rand_id][j];

		}
	}

	way = findBest(matrix, cities, tournament_size, routes1);

	return way;


}

vector<int> GeneticSolution::crossover(int cities, vector<int> parent1, vector<int> parent2) {
	int  *position = new int[cities];
	bool *city_id = new bool[cities];
	int start;
	int end;
	start = rand() % cities;
	end = rand() % cities;
	if (start > end) {
		int temp = start;
		start = end;
		end = temp;
	}

	for (int i = 0; i < cities; i++) {
		city_id[i] = false;
		if (i >= start && i <= end)
			position[i] = parent1[i];
		else
			position[i] = parent2[i];
	}

	vector<int>child(cities);
	for (int i = 0; i < cities; i++) {
		if (!city_id[position[i]]) {
			child[i] = position[i];
			city_id[position[i]] = true;
		} else {
			for (int j = 0; j < cities; j++) {
				int index = parent2[j];
				if (!city_id[index]) {
					child[i] = index;
					city_id[index] = true;
					break;
				}
			}
		}
	}

	return child;
	delete[]position;
	delete[]city_id;

}
//----------------------------------------MUTACJE--------------------------------------------------
void GeneticSolution::mutateScramble(vector<int> &way) {
	int city1, city2, temp;
	city1 = rand() % way.size();
	city2 = rand() % way.size();
	//upewniamy sie ze wylosowane miasta nie są tym samy miastem
	while (city1 == city2) {
		city2 = rand() % (way.size());
	}
	//city2 ma byc wieksze
	if (city1 > city2) {
		temp = city1;
		city1 = city2;
		city2 = temp;
	}
	for (int i = city1; i <= city2; i++) {
		int j = (rand() % (city2 - city1)) + city1;
		temp = way[i];
		way[i] = way[j];
		way[j] = temp;
	}

}

void GeneticSolution::mutateSwap(vector<int> &way) {
	int city1, city2, temp;
	city1 = rand() % way.size();
	city2 = rand() % way.size();
	//upewniamy sie ze wylosowane miasta nie są tym samy miastem
	while (city1 == city2) {
		city2 = rand() % (way.size());
	}
	temp = way[city1];
	way[city1] = way[city2];
	way[city2] = temp;
}

void GeneticSolution::mutateInverse(vector<int> &way) {
	int city1, city2, temp;
	city1 = rand() % way.size();
	city2 = rand() % way.size();
	//upewniamy sie ze wylosowane miasta nie są tym samy miastem
	while (city1 == city2) {
		city2 = rand() % way.size();
	}
	//city2 ma byc wieksze
	if (city1 > city2) {
		temp = city1;
		city1 = city2;
		city2 = temp;
	}
	int inverseCount = (city2 - city1) / 2;
	while(city1 < city2) {
		temp = way[city1];
		way[city1] = way[city2];
		way[city2] = temp;
		city1++;
		city2--;
	}

}