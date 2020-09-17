#ifndef UTILS_H
#define UTILS_H

#include <chrono>
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

