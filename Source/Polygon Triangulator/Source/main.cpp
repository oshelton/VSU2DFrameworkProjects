/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#include <SystemManager.h>
#include "AlgorithmState.h"

int main()
{
    SystemManager* manager = SystemManager::get();

    manager->addSystemState(AlgorithmState::get());

    manager->start("AlgorithmState", "Ear-Clipping Polygon Triangulator");

    delete manager;

    return 0;
}
