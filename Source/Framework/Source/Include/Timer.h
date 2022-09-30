/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

///Timer utility class.
class Timer
{
private:
    ///The Timer's current elapsed time since it was created, in milliseconds.
    double value;

    ///Used to determine if the Timer has been started.
    bool started;
    ///Used to determine if the Timer has been started but should not add time.
    bool paused;

    ///Used to determine if the Timer is manually updated, in which case the update method must be called manually.
    bool manualUpdate;

public:
    ///Constructor.
    Timer(const bool& manualUpdate);

    ///Start the timer.
    void start();
    ///Stop the timer (reset its time to 0 and it will not receive any updates until it has been started again.
    void stop();

    ///Pause the timer, it will no longer update its internal time.  This will not do anything if the Timer has not been started.
    void pause();
    ///Resume the Timer.  This will resume a paused Timer
    void resume();

    ///Get whether or not the Timer is manually updated, if it is the start, pause, and unpause methods will not do anything.
    const bool& isManuallyUpdated();

    ///Get the current elapsed time.
    double getTime();

    ///Add the latest frame differential time to the Timer.
    void update(double delta);
};

#endif // TIMER_H_INCLUDED
