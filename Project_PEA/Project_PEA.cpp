/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>
#include "DynamicSolution.h"
#include "TimeTests.h"
#include "RandomGenerator.h"
#include "TabuSolution.h"
#include "GeneticSolution.h"
#include <cstddef>
#include "Timer.h"

using namespace std;

int matrixSize = 0;
char option;
string fileName;
vector<vector<int>> matrix;
int solution;
int generateSize;

vector<vector<int>> readFile(string fileName) {
	vector<vector<int>> matrix;
	ifstream file;
	file.open(fileName);
	//if something went wrong return false
	if (!file.good())
		return matrix;

	file >> matrixSize;
	//if matrix size is not 0 read matrix from file
	if (matrixSize) {
		matrix.resize(matrixSize);
		for (int i = 0; i < matrix.size(); i++)
			matrix[i].resize(matrixSize);

		for (int i = 0; i < matrixSize; i++) {
			for (int j = 0; j < matrixSize; j++) {
				file >> matrix[i][j];
			}
		}
	}
	file.close();
	return matrix;
}

void printMatrix(vector<vector<int>> matrix) {
	std::cout << endl << "    ";
	for (int i = 0; i < matrixSize; i++) {
		std::cout << setw(4) << i;
	}
	std::cout << endl;
	for (int i = 0; i < matrix.size(); i++) {
		std::cout << "\n" << setw(4) << i;
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << setw(4) << matrix[i][j];
		}
	}
	std::cout << endl;
}

void displayGeneticMenu() {
	std::cout << endl;
	std::cout << "------GENETIC SOLUTION FOR TSP-------" << endl;
	std::cout << "1.Import graph from file" << endl;
	std::cout << "2.Generate random graph" << endl;
	std::cout << "3.Set population size" << endl;
	std::cout << "4.Set crossover probability" << endl;
	std::cout << "5.Set mutation probability" << endl;
	std::cout << "6.Set stop time" << endl;
	std::cout << "7.Mutation type" << endl;
	std::cout << "8.Genetic Solve" << endl;
	std::cout << "9.Show Graph" << endl;
	std::cout << "0.Exit" << endl;
	std::cout << "Podaj opcje: ";
}

void displayMenu() {
	std::cout << endl;
	std::cout << "1.Import graph from file" << endl;
	std::cout << "2.Generate random graph" << endl;
	std::cout << "3.Dynamic Programming Solution" << endl;
	std::cout << "4.Tabu Search Solution" << endl;
	std::cout << "5.Genetic Solution" << endl;
	std::cout << "6.Show Graph" << endl;
	std::cout << "7.Time tests" << endl;
	std::cout << "8.clrscr" << endl;
	std::cout << "0.Exit" << endl;
	std::cout << "Podaj opcje: ";
}

void geneticSolve(float geneticMutationProb, float geneticCrossoverProb, int timeToStop, int populationSize, int mutationType) {
	GeneticSolution *geneticSolution = new GeneticSolution(geneticMutationProb, geneticCrossoverProb);
	vector<vector<int>> pop;
	double best_way = 99999.999;
	double current_way = 0;
	cout << endl;
	pop = geneticSolution->createPopulation(populationSize, matrix.size());
	Timer timer = Timer();
	timer.start();

	do {
		current_way = geneticSolution->evolve(matrix, populationSize, matrix.size(), pop, mutationType);
		if (current_way < best_way) {
			best_way = current_way;
		}
		if (timer.readSeconds() > timeToStop) {
			break;
		}
	} while (true);
	cout << "Najkrotsza znaleziona droga: " << best_way << endl;
	/*for (int i = 0; i < geneticSolution->population[0].size(); i++) {
		cout << geneticSolution->population[0][i];
		if (i < geneticSolution->population[0].size() - 1) {
			cout << "-";
		}
	}*/
}

int geneticMain() {
	vector<int> citiesQuantities{ 2,4,6,8,10,12,14 };
	int glMaxTime, glMaxIterations;
	bool globalIsDivesificationEnabled;
	float geneticCrossoverProb = 0.8;
	float geneticMutationProb = 0.1;
	int populationSize = 100;
	int timeToStop = 10;
	int mutationType = 1;
	char optionMutationType;
	char optionGen;

	do {
		displayGeneticMenu();
		cin >> optionGen;
		switch (optionGen) {
		case '1':
			std::cout << "File name: ";
			cin >> fileName;
			matrix = readFile(fileName);
			break;

		case '2':
			std::cout << "Cities quantity: ";
			cin >> generateSize;
			matrix = RandomGenerator::generate(generateSize);
			break;
		case '3':
			std::cout << "Population Size ( " << populationSize << " ): ";
			cin >> populationSize;
			break;
		case '4':
			std::cout << "Crossover Probability ( " << geneticCrossoverProb << " ): ";
			cin >> geneticCrossoverProb;
			break;
		case '5':
			std::cout << "Mutation Probability ( " << geneticMutationProb << " ): ";
			cin >> geneticMutationProb;
			break;
		case '6':
			std::cout << "Stop Time ( " << timeToStop << " s): ";
			cin >> timeToStop;
			break;
		case '7':
			std::cout << "1 - Scramble\n2 - Swap\n3 - Inverse\nMutation Type ( " << mutationType << " ): ";
			std::cin >> optionMutationType;
			switch (optionMutationType)
			{
			case '1':
				mutationType = 1;
				break;
			case '2':
				mutationType = 2;
				break;
			case '3':
				mutationType = 3;
				break;
			default:
				break;
			}
			break;
		case '8': {
			cout << endl;
			geneticSolve(geneticMutationProb, geneticCrossoverProb, timeToStop, populationSize, mutationType);
			cout << endl;
			//mutations testing
			/*GeneticSolution *geneticSolution = new GeneticSolution(geneticMutationProb, geneticCrossoverProb);
			vector<int> way = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			geneticSolution->mutateScramble(way);
			cout << endl;
			for (int i = 0; i < way.size(); i++){
				cout << way[i];
				if (i < way.size() - 1)
					cout << " , ";
			}
			cout << endl;*/
			break;
		}
		case '9':
			printMatrix(matrix);
			break;
		default:
			break;
		}
	} while (optionGen != '0');
}

int main()
{
	srand(time(NULL));
	double time;
	
	do {
		displayMenu();
		cin >> option;
		switch (option) {
		case '1':
			std::cout << "File name: ";
			cin >> fileName;
			matrix = readFile(fileName);
			break;

		case '2':
			std::cout << "Cities quantity: ";
			cin >> generateSize;
			matrix = RandomGenerator::generate(generateSize);
			break;

		case '3':
			solution = DynamicSolution::solveLoop(matrix);
			std::cout << solution;
			break;
		case '4': {
			unsigned int tabuSize = 3 * matrix.size(), cadency = 3 * matrix.size(), maxIterations = 40000, maxTime = 60000,
				maxIterationsWithoutImprovement = maxIterations / 20;
			bool isDiversificationOn = true;
			char optionTabu;
			std::cout << "Change parameters? (y/n) : ";
			cin >> optionTabu;
			if (optionTabu == 'y' || optionTabu == 'Y') {
				std::cout << "\nMax Time (ms): ";
				cin >> maxTime;
				std::cout << "\nMax Iterations: ";
				cin >> maxIterations;
				char optionDiversification;
				std::cout << "\nDiversification (y/n): ";
				cin >> optionDiversification;
				if (optionDiversification == 'y' || optionDiversification == 'Y') {
					isDiversificationOn = true;
				}
				else {
					isDiversificationOn = false;
				}
			}
			
			auto sol = new TabuSolution();
			auto path = sol->tabuSearch(matrix, tabuSize, cadency, maxIterations, maxTime, isDiversificationOn, maxIterationsWithoutImprovement, true);
			std::cout << path << endl;
			break; }
		case '5': {
			geneticMain();
			break;
		}
		case '6':
			printMatrix(matrix);
			break;
		case '7':
			//TimeTests::makeTests(citiesQuantities);
			time = TimeTests::dynamicLoopTime(matrix);
			std::cout << endl << time << " microsecons\n";
			std::cout << "\n------------Tests Done.---------------\n" << endl;
			break;
		case '8':
			system("cls");
			break;
		default:
			break;
		}


	} while (option != '0');

	return 0;
	
}
