#include "utils.hpp"
#include <iostream>
#include <chrono>


Chronometer::Chronometer()
{
	// start = 0;
 //    end = 0;
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


