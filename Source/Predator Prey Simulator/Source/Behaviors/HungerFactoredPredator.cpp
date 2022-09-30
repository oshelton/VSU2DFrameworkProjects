/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <hgevector.h>
#include <Utils.h>
#include "Predator.h"
#include "Prey.h"
#include "Behaviors/HungerFactoredPredator.h"

using namespace std;

void HungerFactoredPredator::update(Predator* owner, const list<Prey*>& movedPrey, const list<Prey*>& stateChangedPrey)
{
    Utils* utils = Utils::get();

    Prey* optimalPrey = NULL;
    hgeVector optimalPosition(0, 0);
    hgeVector position = owner->getPosition();
    double optimalWeight = 0;

    list<Prey*>::const_iterator iter1;

    for (iter1 = movedPrey.begin(); iter1 != movedPrey.end(); ++iter1)
    {
        if (owner->canSee(*iter1) || owner->canHear(*iter1))
        {
            if (optimalPrey == NULL)
            {
                optimalPrey = *iter1;
                optimalPosition = optimalPrey->getPosition();
                optimalWeight = optimalPrey->getWeight();
            }
            else
            {
                if (utils->distanceBetween(position, (*iter1)->getPosition()) < utils->distanceBetween(position, optimalPosition) &&
                        optimalWeight > (*iter1)->getWeight())
                {
                    optimalPrey = *iter1;
                    optimalPosition = optimalPrey->getPosition();
                    optimalWeight = optimalPrey->getWeight();
                }
            }
        }
    }

    if (optimalPrey != NULL && owner->getHungerFactor() > 0.5)
    {
        if (owner->getHungerFactor() < 1.0 && optimalPrey->getCurrentBehaviorState() == CAUTIOUS)
        {
            owner->setHeading(-utils->angleDegrees(utils->angleBetween(position, optimalPosition)));
            owner->setBehaviorState(FLEEING);

            owner->move(1.3);
        }
        else
        {
            owner->setHeading(utils->angleDegrees(utils->angleBetween(position, optimalPosition)));
            owner->setBehaviorState(PURSUING);

            double distance = utils->distanceBetween(position, optimalPosition);
            if (distance <= owner->getMaxAttackDistance())
            {
                if (utils->getRandomDouble(0.0, (0.5 + distance / owner->getMaxAttackDistance())) < .5)
                    owner->attack(optimalPrey);
            }

            owner->move(1.0 + owner->getHungerFactor() / 5);
        }
    }
    else
    {
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

        owner->move(0.8 + owner->getHungerFactor() / 5);
    }
}
