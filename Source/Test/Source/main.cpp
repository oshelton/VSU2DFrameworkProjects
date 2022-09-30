#include <SystemManager.h>
#include "MainState.h"
#include "SceneGraphTest.h"
#include "CameraTest.h"
#include "RenderTest.h"
#include "main.h"

bool homeButtonPushed(const CEGUI::EventArgs& e)
{
    SystemManager::get()->changeStateNextUpdate("MainState");
    return true;
}

int main()
{
    SystemManager* manager = SystemManager::get();

    manager->addSystemState(new MainState());
    manager->addSystemState(new SceneGraphTest());
    manager->addSystemState(new CameraTest());
    manager->addSystemState(new RenderTest());

    manager->start("MainState", "Framework Test Application");

    delete manager;
    return 0;
}
