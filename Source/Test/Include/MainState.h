#ifndef TESTSTATE1_H_INCLUDED
#define TESTSTATE1_H_INCLUDED

#include <string>
#include <SystemState.h>

class MainState : public SystemState
{
public:
    std::string getName(){ return "MainState";}

    void createScene();

    void clear();

    void FrameFunc();
};

#endif // TESTSTATE1_H_INCLUDED
