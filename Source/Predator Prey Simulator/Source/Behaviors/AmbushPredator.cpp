/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <hgevector.h>
#include <Utils.h>
#include "Predator.h"
#include "Prey.h"
#include "Behaviors/AmbushPredator.h"

using namespace std;

void AmbushPredator::update(Predator* owner, const list<Prey*>& movedPrey, const list<Prey*>& stateChangedPrey)
{
    Utils* utils = Utils::get();

    Prey* optimalPrey = NULL;
    hgeVector optimalPosition(0, 0);
    hgeVector position = owner->getPosition();

    list<Prey*>::const_iterator iter1;

    for (iter1 = movedPrey.begin(); iter1 != movedPrey.end(); ++iter1)
    {
        if (owner->canSee(*iter1) || owner->canHear(*iter1))
        {
            if (optimalPrey == NULL)
            {
                optimalPrey = *iter1;
                optimalPosition = optimalPrey->getPosition();
            }
            else
            {
                if (utils->distanceBetween(position, (*iter1)->getPosition()) < utils->distanceBetween(position, optimalPosition))
                {
                    optimalPrey = *iter1;
                    optimalPosition = optimalPrey->getPosition();
                }
            }
        }
    }

    if (optimalPrey != NULL)
    {
        owner->setHeading(utils->angleDegrees(utils->angleBetween(position, optimalPosition)));
        owner->setBehaviorState(PURSUING);

        double distance = utils->distanceBetween(position, optimalPosition);
        if (distance <= owner->getMaxAttackDistance())
        {
            if (utils->getRandomDouble(0.0, (0.5 + distance / owner->getMaxAttackDistance())) < .6)
                owner->attack(optimalPrey);
        }

        owner->move(1.1 + owner->getHungerFactor() / 5);
    }
    else
    {
        owner->setBehaviorState(PASSIVE);
        int rand = utils->getRandomInt(0, 3000);

        if (rand < 100)
            owner->setHeading(utils->getRandomInt(0, 359));

        if (owner->getHungerFactor() >= 0.8)
        {
            rand = utils->getRandomInt(0, 2000 - (owner->getHungerFactor() * 1500));
            if (rand <= 10)
                owner->move(0.5 + owner->getHungerFactor() / 3.5);
        }
    }
}
