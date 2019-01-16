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
#include <cstddef>

using namespace std;

int matrixSize = 0;

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
		//allocate matrix
		//matrix = new int*[matrixSize];
		//for (int i = 0; i < matrixSize; i++)
			//matrix[i] = new int[matrixSize];
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

void displayMenu() {
	std::cout << endl;
	std::cout << "1.Import graph from file" << endl;
	std::cout << "2.Generate random graph" << endl;
	std::cout << "3.Dynamic Programming Solution" << endl;
	std::cout << "4.Tabu Search Solution" << endl;
	std::cout << "5.Show Graph" << endl;
	std::cout << "6.Time tests" << endl;
	std::cout << "7.clrscr" << endl;
	std::cout << "0.Exit" << endl;
	std::cout << "Podaj opcje: ";
}

int main()
{
	//run random generator
	srand(time(NULL));
	char option;
	string fileName;
	vector<vector<int>> matrix;
	int solution;
	int generateSize;
	double time;
	vector<int> citiesQuantities{ 2,4,6,8,10,12,14 };
	int glMaxTime, glMaxIterations;
	bool globalIsDivesificationEnabled;
	
	
	do {
		displayMenu();
		cin >> option;
		switch (option) {
		case '1':
			std::cout << "File name: ";
			cin >> fileName;
			matrix = readFile(fileName);
			//std::cout << matrix[0][0];
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
		case '5':
			printMatrix(matrix);
			break;
		case '6':
			//TimeTests::makeTests(citiesQuantities);
			time = TimeTests::dynamicLoopTime(matrix);
			std::cout << endl << time << " microsecons\n";
			std::cout << "\n------------Tests Done.---------------\n" << endl;
			break;
		case '7':
			system("cls");
			break;
		default:
			break;
		}


	} while (option != '0');

	return 0;
}
