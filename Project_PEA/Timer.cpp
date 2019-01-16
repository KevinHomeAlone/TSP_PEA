/*
	Author:
	Kevin Pieprzak
*/
#include "pch.h"
#include "Timer.h"
#include <iostream>

Timer::Timer() {
}


Timer::~Timer() {
}

void Timer::start() {
	begin = std::chrono::high_resolution_clock::now();
}


void Timer::stop() {
	end = std::chrono::high_resolution_clock::now();
}

long long Timer::read() {
	auto dur = end - begin;
	time = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	return time;
}