/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef REPORTSECTION_H_INCLUDED
#define REPORTSECTION_H_INCLUDED

#include <string>
#include <vector>

///Class representing a set of messages to be written in a report.
class ReportSection
{
private:
    ///Vector of strings that are to be written in thereport.
    std::vector<std::string> messages;

public:
    /** Add a message to the ReportSection.
    * \param message The message to be written to the report.
    */
    inline void addMessage(const std::string& message){ messages.push_back(message + "\n"); }
    ///Get all the messages in the ReportSection.
    inline const std::vector<std::string>& getMessages(){ return messages; }
};

#endif // REPORTSECTION_H_INCLUDED
