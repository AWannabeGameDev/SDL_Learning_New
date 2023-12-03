#include <SDL.h>

class Timer {

private :

	Uint64 m_start;

public :

	Timer();

	float elapsed();

	void reset();

};