/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include "TabuSolution.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

TabuSolution::TabuSolution()
{
}


TabuSolution::~TabuSolution()
{
}

Route TabuSolution::tabuSearch(const vector<vector<int>> mat, const unsigned int tabuSize, const unsigned int cadency,
	const unsigned int maxIterations, const long long maxTime, const bool diversification,
	const unsigned int maxIterationsWithoutImprovement, const bool showStopReason) {
	Route currentRoute;
	currentRoute.generateInitSolution(mat);
	Route bestRoute;
	Timer timer;
	bool timeExceeded = false, maxIterationsExceeded = false;
	unsigned int iterationCounter = 0, iterationCounterWithoutImprovement = 0;
	vector<tuple<unsigned int, unsigned int, unsigned int>> tabuList;
	tabuList.reserve(tabuSize);

	timer.start();

	while (!timeExceeded && !maxIterationsExceeded) {
		bool shouldStop = false;
		while (!shouldStop) {
			Route nextRoute;
			tuple<unsigned int, unsigned int, unsigned int> tabuElement, *savedMove = nullptr;
			get<0>(tabuElement) = cadency;
			bool shouldIncreaseCadency = false;
			// zamiany
			for (unsigned int i = 1; i < mat.size(); i++) {
				for (unsigned int j = i + 1; j < mat.size(); j++) {
					Route neighbourRoute = currentRoute.swap(i, j);
					neighbourRoute.updateCost(mat);
					// sprawdz tabu
					bool isTabu = false;
					for (unsigned int k = 0; k < tabuList.size(); k++) {
						if ((get<1>(tabuList[k]) == neighbourRoute.path[i] && get<2>(tabuList[k]) == neighbourRoute.path[j])
							|| (get<1>(tabuList[k]) == neighbourRoute.path[j] && get<2>(tabuList[k]) == neighbourRoute.path[i])) {
							savedMove = &tabuList[k];
							isTabu = true;
						}
					}
					// kryterium aspiracji
					if ((isTabu && neighbourRoute.cost >= bestRoute.cost) && nextRoute.path.size() != 0) {
						continue;
					}

					// dodaje do elementu listy tabu i ustawiamy obecnie najlepszy

					if (nextRoute.cost > neighbourRoute.cost || nextRoute.path.size() == 0) {
						nextRoute = neighbourRoute;
						shouldIncreaseCadency = false;
						if (isTabu) shouldIncreaseCadency = true;
						get<1>(tabuElement) = nextRoute.path[i];
						get<2>(tabuElement) = nextRoute.path[j];
					}
				}
			}
			currentRoute = nextRoute;
			// nowa najlepsza sciezka resetuje ilosc iteracji bez poprawy
			if (bestRoute.cost > currentRoute.cost || bestRoute.path.size() == 0) {
				bestRoute = currentRoute;
				iterationCounterWithoutImprovement = 0;
			}
			else {
				iterationCounterWithoutImprovement++;
			}

			// zmniejszanie kadencji elementów
			for (unsigned int i = 0; i < tabuList.size(); i++) {
				get<0>(tabuList[i])--;
				// usuniecie elementu jesli kadencja = 0 (cofa i zeby nie przeoczyc elementow)
				if (get<0>(tabuList[i]) == 0) {
					tabuList.erase(tabuList.begin() + 1);
					i--;
				}
			}

			// dopisanie ostatniego ruchu do listy tabu, jesli jest pelna, usuwa element o najmniejszej kadencji
			if (tabuList.size() >= tabuSize) {
				// szuka najmniejszej kadencji
				unsigned int minimum = numeric_limits<unsigned int>::max();
				int minIndex = -1;
				for (unsigned int i = 0; i < tabuList.size(); i++) {
					if (get<0>(tabuList[i]) < minimum) {
						minimum = get<0>(tabuList[i]);
						minIndex = i;
					}
				}
				//usuwa element o najmniejszej kadencji
				tabuList.erase(tabuList.begin() + minIndex);
			}

			// dodanie ruchu do listy tabu
			// jesli jest juz na liscie (i przeszlo kryterium aspiracji) to zwiekszamy kadencje o 1

			if (shouldIncreaseCadency && savedMove != nullptr) {
				get<0>(*savedMove) = cadency;
			}
			else {
				tabuList.push_back(tabuElement);
			}

			// dodanie iteracji
			iterationCounter++;

			timer.stop();
			// jesli przekroczenie czasu -> stop
			if (timer.read() > maxTime) {
				timeExceeded = true;
				shouldStop = true;
				break;
			}

			// jesli przekroczenie liczby iteracji -> stop
			if (iterationCounter > maxIterations) {
				maxIterationsExceeded = true;
				shouldStop = true;
				break;
			}

			// jesli wlaczona dywersyfikacja i przekroczylismy ilosc iteracji bez poprawy -> stop
			if (diversification && iterationCounterWithoutImprovement >= maxIterationsWithoutImprovement) {
				shouldStop = true;
				break;
			}
		}

		if (diversification && !timeExceeded && !maxIterationsExceeded) {
			currentRoute.generateInitSolution(mat);
			tabuList.clear();
		}

		iterationCounterWithoutImprovement = 0;
	}

	if (showStopReason) {
		if (timeExceeded) std::cout << "Time exceeded\n";
		if (maxIterationsExceeded) std::cout << "Max iteration exceeded";
	}

	return bestRoute;
}
