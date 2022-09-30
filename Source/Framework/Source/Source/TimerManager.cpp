/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "Utils.h"
#include "Timer.h"
#include "TimerManager.h"

using namespace std;

TimerManager* TimerManager::manager(NULL);

TimerManager::TimerManager() : timeFactor(1){}

TimerManager::~TimerManager()
{
    clearTimers();
    manager = NULL;
}

void TimerManager::createTimer(const string& name, const bool& manualUpdate)
{
    if (timers.find(name) == timers.end())
        timers[name] = new Timer(manualUpdate);
    else
        Utils::get()->writeToLog("Timer with name " + name + " already exists, ignoring.");
}

void TimerManager::startTimer(const string& name)
{
    if (timers.find(name) != timers.end())
        timers[name]->start();
}

void TimerManager::pauseTimer(const string& name)
{
    if (timers.find(name) != timers.end())
        timers[name]->pause();
}

void TimerManager::resumeTimer(const string& name)
{
    if (timers.find(name) != timers.end())
        timers[name]->resume();
}

void TimerManager::stopTimer(const string& name)
{
    if (timers.find(name) != timers.end())
        timers[name]->stop();
}

const double TimerManager::getTimerTime(const string& name)
{
    if (timers.find(name) != timers.end())
        return timers[name]->getTime();
    else
        return 0;
}

void TimerManager::addTimerTime(const string& name, const double& time)
{
    if (timers.find(name) != timers.end())
        timers[name]->update(time);
}

void TimerManager::pauseAllTimers()
{
    map<string, Timer*>::const_iterator iter;
    for (iter = timers.begin(); iter != timers.end(); ++iter)
        iter->second->pause();
}

void TimerManager::resumeAllTimers()
{
    map<string, Timer*>::const_iterator iter;
    for (iter = timers.begin(); iter != timers.end(); ++iter)
        iter->second->resume();
}

void TimerManager::destroyTimer(const string& name)
{
    if (timers.find(name) != timers.end())
    {
        delete timers[name];
        timers.erase(name);
    }
    else
        Utils::get()->writeToLog("Timer with name " + name + " does not exist, ignoring.");
}

void TimerManager::clearTimers()
{
    map<string, Timer*>::iterator iter;
    for (iter = timers.begin(); iter != timers.end(); ++iter)
    {
        Timer* tmp = iter->second;
        delete tmp;
    }
    timers.clear();
}

const double TimerManager::getTimeFactor()
{
    return timeFactor;
}

void TimerManager::setTimeFactor(const double& factor)
{
    if (factor > 0)
        timeFactor = factor;
}

void TimerManager::update()
{
    map<string, Timer*>::const_iterator iter;
    for (iter = timers.begin(); iter != timers.end(); ++iter)
    {
        if (!iter->second->isManuallyUpdated())
            iter->second->update(Utils::get()->getDTime() * timeFactor);
    }
}

TimerManager* TimerManager::get()
{
    if (manager == NULL)
        manager = new TimerManager();

    return manager;
}
