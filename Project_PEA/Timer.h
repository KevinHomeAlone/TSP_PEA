/*
	Author:
	Kevin Pieprzak
*/
#pragma once
#include <chrono>

class Timer {
public:
	Timer();
	~Timer();
	void start();
	void stop();
	long long read();
	int readSeconds();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
	//    long long begin;
	//    long long end;
	long long time;
	
};

