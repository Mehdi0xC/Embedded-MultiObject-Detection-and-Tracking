#include "chronometer.hpp"
#include <chrono>

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