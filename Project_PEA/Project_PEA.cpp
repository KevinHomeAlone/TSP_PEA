/*
	Author:
	Kevin Pieprzak
	https://github.com/KevinHomeAlone
*/
#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

int matrixSize = 0;

int** readFile(string fileName) {
	int** matrix = nullptr;
	ifstream file;
	file.open(fileName);
	//if something went wrong return false
	if (!file.good())
		return false;

	file >> matrixSize;
	//if matrix size is not 0 read matrix from file
	if (matrixSize) {
		//allocate matrix
		matrix = new int*[matrixSize];
		for (int i = 0; i < matrixSize; i++)
			matrix[i] = new int[matrixSize];

		for (int i = 0; i < matrixSize; i++) {
			for (int j = 0; j < matrixSize; j++) {
				file >> matrix[i][j];
			}
		}
	}
	file.close();
	return matrix;
}

void printMatrix(int** matrix, int matrixSize) {
	cout << endl << "    ";
	for (int i = 0; i < matrixSize; i++) {
		cout << setw(4) << i;
	}
	cout << endl;
	for (int i = 0; i < matrixSize; i++) {
		cout << "\n" << setw(4) << i;
		for (int j = 0; j < matrixSize; j++) {
			cout << setw(4) << matrix[i][j];
		}
	}
	cout << endl;
}

void displayMenu() {
	cout << endl;
	cout << "1.Import graph from file" << endl;
	cout << "2.Generate random graph" << endl;
	cout << "3.Dynamic Programming Solution" << endl;
	cout << "4.Show Graph" << endl;
	cout << "5.clrscr" << endl;
	cout << "0.Exit" << endl;
	cout << "Podaj opcje: ";
}

int main()
{
	//run random generator
	srand(time(NULL));
	char option;
	string fileName;
	int** matrix = nullptr;
	
	do {
		displayMenu();
		cin >> option;
		switch (option) {
		case '1':
			cout << "File name: ";
			cin >> fileName;
			matrix = readFile(fileName);
			//cout << matrix[0][0];
			break;

		case '2':
			break;

		case '3':
			break;
		case '4':
			printMatrix(matrix, matrixSize);
			break;
		case '5':
			system("cls");
			break;
		default:
			break;


		}


	} while (option != '0');

	return 0;
}
