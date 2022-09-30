/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <math.h>
#include <Camera.h>
#include <CompoundRenderable.h>
#include <SimpleRenderable.h>
#include <LineRenderable.h>
#include <Utils.h>
#include <SceneManager.h>
#include <SceneNode.h>
#include <Camera.h>
#include "Animal.h"

using namespace std;

void Animal::setupNodeHeirarchy()
{
    mainNode = SceneManager::get()->getRootSceneNode()->createChildSceneNode(name + " " + species);
    mainNode->setZ(0.5);

    pointerNode = SceneManager::get()->getCamera()->getParent()->createChildSceneNode(name + " " + species + " pointer");

    SceneNode* tmp = pointerNode->createChildSceneNode(name + " " + species + " pointer point");
    tmp->setZ(0.01);
    tmp->setPosition(hgeVector(260, 0));
    tmp->setVisible(false);
    tmp->setInheritScale(false);
}

void Animal::destroyNodeHeirarchy()
{
    mainNode->destroy();
    pointerNode->destroy();
}

void Animal::setPosition(const hgeVector position)
{
    mainNode->setPosition(position);
}

hgeVector Animal::getPosition()
{
    return mainNode->getPosition();
}

void Animal::setHeading(const double& angle)
{
    mainNode->setRotation(angle);
}

const double Animal::getHeading()
{
    return mainNode->getWorldRotation();
}

void Animal::constructRenderables(const string& spriteName, const string& pointerSpriteName, const hgeColor& hearingColor, const hgeColor& sightColor)
{
    SceneManager* scene = SceneManager::get();

    if (scene->componentExists(pointerSpriteName))
        scene->getSceneNode(name + " " + species + " pointer point")->attachComponent(scene->getComponent(pointerSpriteName));
    else
    {
        SimpleRenderable* renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", pointerSpriteName));
        renderable->setSprite(pointerSpriteName);
        scene->getSceneNode(name + " " + species + " pointer point")->attachComponent(renderable);
    }

    CompoundRenderable* compound = NULL;

    if (scene->componentExists(species))
    {
        compound = static_cast<CompoundRenderable*>(scene->getComponent(species));
        mainNode->attachComponent(compound);
    }
    else
    {
        compound = static_cast<CompoundRenderable*>(scene->createComponent("CompoundRenderable", species));
        mainNode->attachComponent(compound);

        if (scene->componentExists(spriteName))
            compound->addRenderable(static_cast<Renderable*>(scene->getComponent(spriteName)));
        else
        {
            SimpleRenderable* renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", spriteName));
            renderable->setSprite(spriteName);
            compound->addRenderable(renderable);
        }

        LineRenderable* hearingCircle = NULL;

        if (scene->componentExists(species + "_hearing"))
            hearingCircle = static_cast<LineRenderable*>(scene->getComponent(species + "_hearing"));
        else
        {
            hearingCircle = static_cast<LineRenderable*>(scene->createComponent("LineRenderable", species + "_hearing"));

            for (int i = 0; i <= 360; i += 45)
            {
                hearingCircle->addLine(hgeVector(cos(Utils::get()->angleRadians(i)) * hearingDistance, sin(Utils::get()->angleRadians(i)) * hearingDistance),
                                       hgeVector(cos(Utils::get()->angleRadians(i + 45)) * hearingDistance, sin(Utils::get()->angleRadians(i + 45)) * hearingDistance),
                                       hearingColor);

            }
        }
        compound->addRenderable(hearingCircle);

        LineRenderable* sightCone = NULL;

        if (scene->componentExists(species + "_sight"))
            sightCone = static_cast<LineRenderable*>(scene->getComponent(species + "_sight"));
        else
        {
            sightCone = static_cast<LineRenderable*>(scene->createComponent("LineRenderable", species + "_sight"));

            double radianAngle = Utils::get()->angleRadians(sightAngle);

            sightCone->addLine(hgeVector(0, 0),
                               hgeVector(cos(radianAngle / 2) * sightDistance, sin(radianAngle / 2) * sightDistance),
                               sightColor);

            sightCone->addLine(hgeVector(0, 0),
                               hgeVector(cos(-radianAngle / 2) * sightDistance, sin(-radianAngle / 2) * sightDistance),
                               sightColor);

            sightCone->addLine(hgeVector(cos(radianAngle / 2) * sightDistance, sin(radianAngle / 2) * sightDistance),
                               hgeVector(sightDistance, 0),
                               sightColor);

            sightCone->addLine(hgeVector(sightDistance, 0),
                               hgeVector(cos(-radianAngle / 2) * sightDistance, sin(-radianAngle / 2) * sightDistance),
                               sightColor);
        }
        compound->addRenderable(sightCone);
    }
}

void Animal::updatePointer()
{
    hgeVector animalPos = mainNode->getWorldPosition();
    hgeVector camPosition = SceneManager::get()->getCamera()->getCenter();

    double angle = atan2(animalPos.y - camPosition.y, animalPos.x - camPosition.x);

    pointerNode->setRotation(Utils::get()->angleDegrees(angle));
    pointerNode->setScale(1.0 + fabs(cos(angle)) / 2.2);

    SceneNode* pointer = SceneManager::get()->getSceneNode(name + " " + species + " pointer point");

    SimpleRenderable* renderable = static_cast<SimpleRenderable*>(mainNode->getComponent());
    double radius = sqrt((renderable->getWidth() * renderable->getWidth()) + (renderable->getHeight() * renderable->getHeight()));
    if (Utils::get()->onScreen(animalPos, mainNode->getWorldScale() * radius))
        pointer->setVisible(false);
    else
        pointer->setVisible(true);
}
