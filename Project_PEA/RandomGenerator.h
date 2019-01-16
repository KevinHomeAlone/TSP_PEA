#pragma once
#include <vector>

using namespace std;

class RandomGenerator
{
public:
	static vector<vector<int>> generate(int);
	RandomGenerator();
	~RandomGenerator();
};

