/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef REPORTMANAGER_H_INCLUDED
#define REPORTMANAGER_H_INCLUDED

#include <string>
#include <map>

class ReportSection;

///Class for writing reports to a file.
class ReportManager
{
private:
    ///Map of all sections in the report, allows for ordering and grouping of messages.
    std::map<std::string, ReportSection*> sections;

    ///Counter added to the filename of reports toallow multiple reports to be created in one execution of the program.
    unsigned int reportCount;

    ///Singleton instance of the ReportManager.
    static ReportManager* manager;

public:
    ReportManager();
    ///Deconstructor, destroys any remaining ReportSections.
    ~ReportManager();

    /** Create and return a new ReportSection.
    * \param name The name of the ReportSection to create.
    * \remark If name is already in use the previously existing ReportSection will be returned.
    */
    ReportSection* createReportSection(const std::string& name);
    /** Get a ReportSection.
    * \param name The name of the ReportSection to retrieve.
    * \remark If name is not in use NULL will be returned.
    */
    ReportSection* getReportSection(const std::string& name);
    ///Destroy all ReportSections.
    void clearReportSections();

    /** Write all ReportSections to file.
    * \param fileName The file name to write the report to, any existing file will be overwritten.
    * \param autoPurge If true all ReportSections will be destroyed after the writing process is finished.
    * \remark The report will be written to "exe directory"\Reports\report + counter
    */
    void writeReport(const bool& autoPurge = true);

    ///Singleton access method.
    static ReportManager* get();
};

#endif // REPORTMANAGER_H_INCLUDED
