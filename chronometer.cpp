#include "chronometer.hpp"
#include <iostream>
#include <chrono>
#include <random>



Chronometer::Chronometer()
{

}

void Chronometer::tic()
{
	start = Clock::now();
}
int Chronometer::toc()
{
	end = Clock::now();
	elapsed = std::chrono::duration_cast<milliseconds>(end - start);
	return elapsed.count();
}