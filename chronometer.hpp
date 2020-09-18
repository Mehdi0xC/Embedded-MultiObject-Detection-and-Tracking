#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <chrono>
#include <vector>
#include "config.hpp"

class Chronometer
{
private:
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point start;
	Clock::time_point end;
	milliseconds elapsed;

public:
	Chronometer();
	void tic();
	int toc();
};

#endif

