/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include <chrono>
#include "DynamicSolution.h"
#include "TimeTests.h"
#include <iostream>
#include <fstream>
#include "RandomGenerator.h"

using namespace std;

TimeTests::TimeTests()
{
}


TimeTests::~TimeTests()
{
}

long TimeTests::dynamicLoopTime(vector<vector<int>> costsMatrix) {
	chrono::steady_clock::time_point startTime, endTime;
	startTime = chrono::steady_clock::now();

	DynamicSolution::solveLoop(costsMatrix);

	endTime = chrono::steady_clock::now();

	//std::cout << endl << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << " ns\n";

	return chrono::duration_cast<chrono::microseconds>(endTime-startTime).count();

}

long TimeTests::averageOfDynamicTests(int testsQuantity, int citiesQuantity) {
	long sum = 0;
	vector<vector<int>> randomGraph = RandomGenerator::generate(citiesQuantity);
	for (int i = 0; i < testsQuantity; i++) {
		sum += dynamicLoopTime(randomGraph);
		std::cout << i;
	}
	return sum / testsQuantity;
}

void TimeTests::writeToFile(string fileName, int citiesQuantity, long time) {
	ofstream myfile;
	myfile.open(fileName, std::ios_base::app);
	myfile << citiesQuantity << ";" << time << endl;
	myfile.close();
}

void TimeTests::makeTests(vector<int> cityQuantities) {
	long time;
	for (int i = 0; i < cityQuantities.size(); i++) {
		time = averageOfDynamicTests(30, cityQuantities[i]);
		writeToFile("results.csv", cityQuantities[i], time);
	}
}