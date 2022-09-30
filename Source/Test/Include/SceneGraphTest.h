#ifndef SCENEGRAPHTEST_H_INCLUDED
#define SCENEGRAPHTEST_H_INCLUDED

#include <string>
#include <SystemState.h>

class SceneNode;

class SceneGraphTest : public SystemState
{
private:
    SceneNode* sun, *planet1, *planet2, *moon1, *moon2, *moon3, *moon4;

public:
    std::string getName(){ return "SceneGraphTest";}

    void createScene();

    void clear();

    void FrameFunc();
};

#endif // SCENEGRAPHTEST_H_INCLUDED
