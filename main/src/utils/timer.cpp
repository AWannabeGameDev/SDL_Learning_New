#include "timer.h"
#include <iostream>

Timer::Timer() :

	m_start(SDL_GetTicks64()) {}

float Timer::elapsed() {

	return (SDL_GetTicks64() - m_start) / 1000.f;

}

void Timer::reset() {

	m_start = SDL_GetTicks64();

}