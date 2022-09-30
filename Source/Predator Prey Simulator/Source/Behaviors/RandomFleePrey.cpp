/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <hgevector.h>
#include <Utils.h>
#include "Predator.h"
#include "Prey.h"
#include "SimulationManager.h"
#include "PreyManager.h"
#include "Behaviors/RandomFleePrey.h"

using namespace std;

void RandomFleePrey::update(Prey* owner, const list<Predator*>& movedPredators, const list<Predator*>& stateChangedPredators)
{
    Utils* utils = Utils::get();

    Predator* nearestPredator = NULL;
    hgeVector nearestPosition(0, 0);
    hgeVector position = owner->getPosition();

    list<Predator*>::const_iterator iter1;

    for (iter1 = movedPredators.begin(); iter1 != movedPredators.end(); ++iter1)
    {
        if (owner->canSee(*iter1) || owner->canHear(*iter1))
        {
            SimulationManager::get()->getPreyManager()->preyNoticesPredator(owner, *iter1);

            if (nearestPredator == NULL)
            {
                nearestPredator = *iter1;
                nearestPosition = nearestPredator->getPosition();
            }
            else
            {
                if (utils->distanceBetween(position, (*iter1)->getPosition()) < utils->distanceBetween(position, nearestPosition))
                {
                    nearestPredator = *iter1;
                    nearestPosition = nearestPredator->getPosition();
                }
            }
        }
    }

    if (nearestPredator == NULL)
    {
        owner->setBehaviorState(PASSIVE);
        int rand = utils->getRandomInt(1, 2000);
        if (rand < 20)
            owner->setHeading(utils->getRandomInt(0, 359));

        if (utils->getRandomInt(0, 30) <= 5)
            owner->move(1.0);
    }
    else
    {
        if (utils->getRandomInt(0, 500) < 10)
        {
            double angle = utils->angleBetween(position, nearestPosition);
            owner->setHeading(-utils->getRandomInt(angle - 20, angle + 20));
        }

        double distance = utils->distanceBetween(position, nearestPosition);

        owner->move(1.0 + (1.0 - distance / owner->getHearingDistance()) / 2);
        owner->setBehaviorState(FLEEING);
    }
}
