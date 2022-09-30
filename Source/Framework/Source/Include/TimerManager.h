/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef TIMERMANAGER_H_INCLUDED
#define TIMERMANAGER_H_INCLUDED

#include <string>
#include <map>
#include "dll.h"

class Timer;

/** Timer management Singleton class.
* This class is responsible for creating and managing Timers.
*/
class EXPORT_FRAME TimerManager
{
private:
    ///Map of Timers.
    std::map<std::string, Timer*> timers;

    ///Method used for altering the global pasage of time as it applies to Timers.
    double timeFactor;

    ///Singleton access pointer, returns a pointer to the TimerManager object.
    static TimerManager* manager;

    ///Constructor.
    TimerManager();

public:
    ///Deconstructor.
    ~TimerManager();

    /** Create a new Timer.
    * \param name Name of the Timer to be created.
    * \param manualUpdate True if the Timer's time is going to be updated manually through the addTimerTime method.
    * \remark If name is already in use nothing will happen.
    */
    void createTimer(const std::string& name, const bool& manualUpdate = false);

    /** Start a Timer
    * \param name The name of the Timer to start.
    * \remark Nothing will happen if no Timer named name exists.
    */
    void startTimer(const std::string& name);
    /** Pause a Timer
    * \param name The name of the Timer to pause.
    * \remark Nothing will happen if no Timer named name exists.
    */
    void pauseTimer(const std::string& name);
    /** Resume a Timer
    * \param name The name of the Timer to resume.
    * \remark Nothing will happen if no Timer named name exists.
    */
    void resumeTimer(const std::string& name);
    /** Stop a Timer
    * \param name The name of the Timer to stop.
    * \remark Nothing will happen if no Timer named name exists.
    */
    void stopTimer(const std::string& name);

    /** Get a Timer's value.
    * \param name The name of the Timer that we are retrieving the value of.
    * \remark 0 will be returned if no Timer named name exists.
    */
    const double getTimerTime(const std::string& name);

    /** Method for manually adding time to a Timer.
    * \param name The name of the Timer to add time to.
    * \param time The amount of time to add, in seconds.
    * \remark This will work on timers that are both manually and automatically updated.
    */
    void addTimerTime(const std::string& name, const double& time);

    ///Pause all timers.
    void pauseAllTimers();
    ///Resume all Timers.
    void resumeAllTimers();

    /** Destroy a Timer.
    * \param name The name of theTimer to destroy.
    * \remark If no Timer named name exists nothing will happen.
    */
    void destroyTimer(const std::string& name);

    ///Destroy all Timers.
    void clearTimers();

    ///Get the global time factor.
    const double getTimeFactor();
    /** Set the time factor.
    * \param factor The new time factor.
    * \remark Numbers <= 0 will not do anything.
    */
    void setTimeFactor(const double& factor);

    ///Update all Timers.
    void update();

    ///Singleton access method.
    static TimerManager* get();
};

#endif // TIMERMANAGER_H_INCLUDED
