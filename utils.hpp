#ifndef UTILS_H
#define UTILS_H
class Chronometer
{
	private:
		typedef std::chrono::high_resolution_clock Clock;
    	typedef std::chrono::milliseconds milliseconds;
    	// Clock::time_point t0 = Clock::now();
    	Clock::time_point start;
    	Clock::time_point end;
    	// milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
    	milliseconds elapsed;



    public:
        Chronometer();
        void tic();
        int toc();
};
#endif
