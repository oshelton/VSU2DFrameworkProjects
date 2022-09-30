#ifndef RENDERTEST_H_INCLUDED
#define RENDERTEST_H_INCLUDED

#include <string>
#include <SystemState.h>

class SceneNode;

class RenderTest : public SystemState
{
private:
    SceneNode* background;
    float u, v, width, height;

public:
    std::string getName(){ return "RenderTest";}

    void createScene();

    void clear();

    void FrameFunc();
};

#endif // RENDERTEST_H_INCLUDED
