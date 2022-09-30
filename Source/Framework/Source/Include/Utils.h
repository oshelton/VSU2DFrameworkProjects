/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <map>
#include <string>
#include <fstream>
#include <hgevector.h>
#include "dll.h"

class HGE;
class Camera;
class asIScriptEngine;
class Timer;
class RenderTexture;

///Utility class that provides many commonly used methods and manages some utility classes.
class EXPORT_FRAME Utils
{
private:
    ///The output stream used as the log.
    std::ofstream log;

    ///Singleton access pointer, returns a pointer to the Utils object.
    static Utils* utils;

    ///Constructor.
    Utils();

public:
    ///Deconstructor.
    ~Utils();

    /** Get a random, bound, integer.
    * \param min The minimum value of the random number.
    * \param max The maximum value of the random number.
    */
    const int getRandomInt(const int& min, const int& max);
    /** Get a random, bound, double.
    * \param min The minimum value of the random number.
    * \param max The maximum value of the random number.
    */
    const double getRandomDouble(const double& min, const double& max);

    /**Get the average number of frames render per second.
    * \remark 60 is the optimal number, but anything above 25 is acceptable.
    */
    const double getFPS();
    /** Get the time since the last frame was rendered.
    * \remark This is a special number that is used to scale object movement so that all translations and rotations occur at the same rate no matter the FPS.
    */
    const double getDTime();

    /** Get whether or not the circle with origin at center and radius radius is going to be rendered to tex.
    * \param tex The RenderTexture being rendered.
    * \param center The center of the circle to check.
    * \param radius The radius of the circle to check.
    */
    const bool onScreen(RenderTexture* const tex, const hgeVector& center, const double& radius);
    /** Get whether or not the circle with origin at center and radius radius is going to be rendered to the main window.
    * \param center The center of the circle to check.
    * \param radius The radius of the circle to check.
    */
    const bool onScreen(const hgeVector& center, const double& radius);

    /** Simple method for getting the distance between two points.
    * \param p1 The first point.
    * \param p2 The second point.
    */
    const double distanceBetween(const hgeVector& p1, const hgeVector& p2);
    /** Simple method for getting the angle between two points, returns radians.
    * \param p1 The first point.
    * \param p2 The second point.
    */
    const double angleBetween(const hgeVector& p1, const hgeVector& p2);

    /** Write a message to the log file.
    * \param text The message to write to the log.
    * \param writeToConsole Whether or not text should bewritten to the GUI console as well
    */
    void writeToLog(const std::string& text, const bool& writeToConsole = true);

    /** Write a message to the log file.
    * \param text The message to write to the log.
    * \param writeToConsole Whether or not text should bewritten to the GUI console as well
    * \param ... arbitrary parameters to be formatted.
    */
    void writeFormattedToLog(const std::string& format, const bool& writeToConsole, ...);

    /** Format the passed string, essentially wraps sprintf.
    * \param format The formating string to use.
    * \param ... arbitrary parameters to be formatted.
    */
    const std::string formatString(const std::string& format, ...);

    ///Convert an int to a string.
    const std::string intToString(const int& val);
    ///Convert a double to a string.
    const std::string doubleToString(const double& val);

    /** Convert a string to an int.
    * \param str The string to parse.
    * \return 0 if conversion fails.
    */
    const int stringToInt(const std::string& str);
    /** Convert a string to a double.
    * \param str The string to parse.
    * \return 0 if conversion fails.
    */
    const double stringToDouble(const std::string& str);

    ///Convert a radians angle to degrees.
    const double angleDegrees(const double& radians);
    ///Convert a degrees angle to radians.
    const double angleRadians(const double& degrees);

    ///Singleton access method, returns a pointer to the Utils instance.
    static Utils* get();
};

#endif // UTILS_H_INCLUDED
