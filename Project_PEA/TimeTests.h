/*
	Author:
	Kevin Pieprzak
*/
#pragma once
#include <vector>

using namespace std;

class TimeTests
{
public:
	static long dynamicLoopTime(vector<vector<int>>);
	static long averageOfDynamicTests(int, int);
	static void writeToFile(string, int, long);
	static void makeTests(vector<int>);
	TimeTests();
	~TimeTests();
};

