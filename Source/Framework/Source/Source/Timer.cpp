/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "TimerManager.h"
#include "Timer.h"

using namespace std;

Timer::Timer(const bool& manualUpdate) : value(0), started(false), paused(false)
{
    this->manualUpdate = manualUpdate;
    if (manualUpdate)
        started = true;
}

void Timer::start()
{
    if (!manualUpdate)
        started = true;
}

void Timer::stop()
{
    if (!manualUpdate)
        started = false;
    paused = false;
    value = 0;
}

void Timer::pause()
{
    if (started && !manualUpdate)
        paused = true;
}

void Timer::resume()
{
    if (paused && !manualUpdate)
        paused = false;
}

const bool& Timer::isManuallyUpdated()
{
    return manualUpdate;
}

double Timer::getTime()
{
    return value;
}

void Timer::update(double delta)
{
    if (manualUpdate || (started && !paused))
        value += delta;
}
