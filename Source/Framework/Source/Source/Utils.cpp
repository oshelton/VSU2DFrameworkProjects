/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <angelscript.h>
#include <sstream>
#include <CEGUI.h>
#include <stdarg.h>
#include "Utils.h"
#include "Camera.h"
#include "ScriptManager.h"
#include "Timer.h"
#include "RenderTexture.h"
#include "SceneManager.h"
#include "SystemManager.h"
#include "GuiManager.h"

using namespace std;

Utils* Utils::utils(NULL);

Utils::Utils()
{
    log.open("log.txt", ios::trunc);
    log.close();
}

Utils::~Utils()
{
    utils = NULL;
}

const int Utils::getRandomInt(const int& min, const int& max)
{
    return SystemManager::get()->getHGEManager()->Random_Int(min, max);
}

const double Utils::getRandomDouble(const double& min, const double& max)
{
    return SystemManager::get()->getHGEManager()->Random_Float(min, max);
}

const double Utils::getFPS()
{
    return SystemManager::get()->getHGEManager()->Timer_GetFPS();
}

const double Utils::getDTime()
{
    return SystemManager::get()->getHGEManager()->Timer_GetDelta();
}

const bool Utils::onScreen(RenderTexture* const tex, const hgeVector& center, const double& radius)
{
    if (tex->getCamera() != NULL)
    {
        Camera* cam = tex->getCamera();
        if (cam->getLeft(tex) > (center.x + radius) || cam->getRight(tex) < (center.x - radius) ||
            cam->getTop(tex) < (center.y - radius) || cam->getBottom(tex) > (center.y + radius))
            return false;
        else
            return true;
    }
    return false;
}

const bool Utils::onScreen(const hgeVector& center, const double& radius)
{
    Camera* cam = SceneManager::get()->getCamera();
    if (cam->getLeft() > (center.x + radius) || cam->getRight() < (center.x - radius) ||
        cam->getTop() < (center.y - radius) || cam->getBottom() > (center.y + radius))
        return false;
    else
        return true;
}

const double Utils::distanceBetween(const hgeVector& p1, const hgeVector& p2)
{
    return (p1 - p2).Length();
}

const double Utils::angleBetween(const hgeVector& p1, const hgeVector& p2)
{
    double ret = atan2(p2.y - p1.y, p2.x - p1.x);
    if (ret + 2 * M_PI > 2 * M_PI)
        return ret;
    else
        return ret + 2 * M_PI;
}

void Utils::writeToLog(const string& text, const bool& writeToConsole)
{
    log.open("log.txt", ios::app);
    log << text << "\n";
    log.close();

    if (writeToConsole)
        GuiManager::get()->writeToConsole(text);
}

void Utils::writeFormattedToLog(const string& format, const bool& writeToConsole, ...)
{
    char buffer[2048];

    va_list args;
    va_start (args, writeToConsole);

    vsprintf(buffer, format.c_str(), args);

    va_end(args);

    const string tmp = buffer;
    writeToLog(tmp, writeToConsole);
}

const string Utils::formatString(const string& format, ...)
{
    char buffer[2048];

    va_list args;
    va_start (args, format);

    vsprintf(buffer, format.c_str(), args);

    va_end(args);

    return string(buffer);
}

const string Utils::intToString(const int& val)
{
    stringstream ss;
    string returnString;

    ss << val;
    ss >> returnString;

    return returnString;
}

const string Utils::doubleToString(const double& val)
{
    stringstream ss;
    string returnString;

    ss << val;
    ss >> returnString;

    return returnString;
}

const int Utils::stringToInt(const string& str)
{
    return atoi(str.c_str());
}

const double Utils::stringToDouble(const string& str)
{
    return atof(str.c_str());
}

const double Utils::angleDegrees(const double& radians)
{
    return radians * 57.2957795;
}

const double Utils::angleRadians(const double& degrees)
{
    return degrees / 57.2957795;
}

Utils* Utils::get()
{
    if (utils == NULL)
        utils = new Utils();

    return utils;
}
