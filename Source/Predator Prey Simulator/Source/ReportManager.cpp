/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <direct.h>
#include <Utils.h>
#include "ReportSection.h"
#include "ReportManager.h"

using namespace std;

ReportManager* ReportManager::manager(NULL);

ReportManager::ReportManager() : reportCount(0)
{
    mkdir("../Reports");
}

ReportManager::~ReportManager()
{
    clearReportSections();
}

ReportSection* ReportManager::createReportSection(const string& name)
{
    if (sections.find(name) == sections.end())
        sections[name] = new ReportSection();
    else
        Utils::get()->writeToLog("ReportSection with name [" + name + "] already exists, returning previously existing ReportSection.");
    return sections[name];
}

ReportSection* ReportManager::getReportSection(const string& name)
{
    if (sections.find(name) == sections.end())
    {
        Utils::get()->writeToLog("ReportSection with name [" + name + "] does not exist, returning NULL.");
        return NULL;
    }
    else
        return sections[name];
}

void ReportManager::clearReportSections()
{
    map<string, ReportSection*>::const_iterator iter;
    for (iter = sections.begin(); iter != sections.end(); ++iter)
        delete iter->second;

    sections.clear();
}

void ReportManager::writeReport(const bool& autoPurge)
{
    ofstream report;
    string fileName = Utils::get()->formatString("../Reports/report %i.txt", reportCount++);
    report.open(fileName.c_str(), ios::trunc);
    report << "Predator Prey Simulator Report." << endl;
    report.close();

    report.open(fileName.c_str(), ios::app);

    map<string, ReportSection*>::reverse_iterator iter;
    for (iter = sections.rbegin(); iter != sections.rend(); ++iter)
    {
        const vector<string> messages = iter->second->getMessages();

        for (unsigned int i = 0; i < messages.size(); ++i)
            report << messages[i];

        report << endl;
    }

    report.close();

    if (autoPurge)
        clearReportSections();
}

ReportManager* ReportManager::get()
{
    if (manager == NULL)
        manager = new ReportManager();

    return manager;
}
