/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <Utils.h>
#include <angelscript.h>
#include <ScriptManager.h>
#include <SceneManager.h>
#include <SimpleRenderable.h>
#include <dirent.h>
#include "PreyManager.h"
#include "PredatorManager.h"
#include "ReportManager.h"
#include "ReportSection.h"
#include "SimulationManager.h"
#include "Prey.h"
#include "Predator.h"
#include "Environment.h"

using namespace std;

void Environment::init()
{
    predatorCounter = 0;
    preyCounter = 0;
}

const list<string> Environment::getFileNames()
{
    list<string> fileNames;

    DIR* directory = opendir(getScriptDirectory().c_str());
    if (directory == NULL)
        Utils::get()->writeFormattedToLog("Error opening the [%s] Environment's script directory [%s], ignoring.", true, getType().c_str(), getScriptDirectory().c_str());
    else
    {
        dirent* file;
        while ((file = readdir(directory)) != NULL)
        {
            if (file->d_name[0] != '.')
                fileNames.push_back(file->d_name);
        }
    }

    return fileNames;
}

void Environment::loadSimulation(const string& file)
{
    ReportManager* report = ReportManager::get();

    clearEnvironment();
    report->clearReportSections();

    report->createReportSection("environment");
    report->getReportSection("environment")->addMessage("Environment created from file: " + getScriptDirectory() + "/" + file);

    ScriptManager::get()->getScriptEngine()->DiscardModule((getScriptDirectory() + file).c_str());
    ScriptManager::get()->executeScript((getScriptDirectory() + "/" + file).c_str());

    if (predators.size() > 0)
    {
        report->getReportSection("environment")->addMessage("Number of Predators: " + Utils::get()->intToString(predators.size()));
        report->getReportSection("environment")->addMessage("Number of Prey: " + Utils::get()->intToString(prey.size()));

        SimpleRenderable* background = static_cast<SimpleRenderable*>(SceneManager::get()->getComponent("background"));
        background->setSprite(getBackgroundSpriteName());

        SimulationManager::get()->activate();
    }
    else
    {
        Utils::get()->writeToLog("Invalid environment.  At least one Predator must exist in a simulation otherwise it could run forever.");
        ReportManager::get()->clearReportSections();
    }
}

Predator* Environment::createPredator(const string& type, const hgeVector& pos)
{
    return createPredator(type, type + Utils::get()->intToString(predatorCounter++), pos);
}

void Environment::killPredator(const string& name)
{
    if (predators.find(name) != predators.end())
    {
        SimulationManager::get()->getPredatorManager()->predatorStarved(predators.begin()->second);
        killPredator(predators[name]);
    }
    else
        Utils::get()->writeToLog("Predator with name [" + name + "] does not exists, ignoring.");
}

void Environment::killPredator(Predator* animal)
{
    predators.erase(animal->getName());
    delete animal;
}

Prey* Environment::createPrey(const string& type, const hgeVector& pos)
{
    return createPrey(type, type + Utils::get()->intToString(preyCounter++), pos);
}

void Environment::killPrey(const string& name)
{
    if (prey.find(name) != prey.end())
    {
        SimulationManager::get()->getPredatorManager()->removePrey(prey.begin()->second);
        killPrey(prey[name]);
    }
    else
        Utils::get()->writeToLog("Prey with name [" + name + "] does not exists, ignoring.");
}

void Environment::killPrey(Prey* animal)
{
    prey.erase(animal->getName());
    delete animal;
}

void Environment::clearEnvironment()
{
    while (predators.size() > 0)
    {
        killPredator(predators.begin()->second);
        SimulationManager::get()->getPredatorManager()->flushPredators();
    }

    while (prey.size() > 0)
    {
        SimulationManager::get()->getPredatorManager()->removePrey(prey.begin()->second);
        killPrey(prey.begin()->second);
    }
}

void Environment::update()
{
    if (predators.size() == 0 && SimulationManager::get()->isActive())
    {
        ReportManager::get()->getReportSection("environment")->addMessage("Simulation terminated at: " + SimulationManager::get()->getSimulationTime());
        ReportManager::get()->writeReport();
        SimulationManager::get()->deactivate();
    }
}
