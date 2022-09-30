/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <math.h>
#include <Utils.h>
#include <TimerManager.h>
#include "Predator.h"
#include "prey.h"
#include "Behaviors/GenericPredatorBehavior.h"

using namespace std;

void GenericPredatorBehavior::update(Predator* owner, const list<Prey*>& movedPrey, const list<Prey*>& stateChangedPrey)
{
    Utils* utils = Utils::get();

    if (movedPrey.size() > 0)
    {
        Prey* nearestPrey = NULL;
        list<Prey*>::const_iterator iter1;

        for (iter1 = movedPrey.begin(); iter1 != movedPrey.end(); ++iter1)
        {
            if (owner->canSee(*iter1) || owner->canHear(*iter1))
            {
                if (nearestPrey == NULL)
                    nearestPrey = *iter1;
                else
                {
                    if (utils->distanceBetween(owner->getPosition(), (*iter1)->getPosition()) < utils->distanceBetween(owner->getPosition(), nearestPrey->getPosition()))
                        nearestPrey = *iter1;
                }
            }
        }


        if (nearestPrey != NULL)
        {
            owner->setHeading(utils->angleDegrees(utils->angleBetween(owner->getPosition(), nearestPrey->getPosition())));
            owner->setBehaviorState(PURSUING);
            if (utils->distanceBetween(owner->getPosition(), nearestPrey->getPosition()) <= owner->getMaxAttackDistance())
            {
                if (utils->getRandomDouble(0.0, 1.0) < pow(M_E, -50 * (utils->distanceBetween(owner->getPosition(), nearestPrey->getPosition())  / owner->getMaxAttackDistance())))
                    owner->attack(nearestPrey);
            }

            if (owner->getCurrentBehaviorState() == PURSUING && owner->getHungerFactor() > 1)
                owner->move(1.8);
            else if (owner->getCurrentBehaviorState() == PURSUING)
                owner->move(1.3);
            else
                owner->move(1.0);

            return;
        }
    }

    owner->setBehaviorState(PASSIVE);
    int rand = utils->getRandomInt(1, 1000);
    switch (rand)
    {
    case 1:
        owner->setHeading(0);
        break;
    case 2:
        owner->setHeading(90);
        break;
    case 3:
        owner->setHeading(180);
        break;
    case 4:
        owner->setHeading(270);
        break;
    }

    if (utils->getRandomInt(0, 15) <= 9)
    {
        if (owner->getHungerFactor() > 1)
            owner->move(1.2);
        else
            owner->move(1.0);
    }
}
