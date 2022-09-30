/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <assert.h>
#include <angelscript.h>
#include <math.h>
#include <hge.h>
#include <hgerect.h>
#include <hgevector.h>
#include <hgecolor.h>
#include <stddef.h>
#include "Utils.h"
#include "UtilBinder.h"

using namespace std;

int BLEND_COLOR_ADD;
int BLEND_COLOR_MUL;
int BLEND_ALPHA_ADD;
int BLEND_ALPHA_BLEND;
int BLEND_NOZ_WRITE;
int BLEND_Z_WRITE;
int BLEND_DEFAULTZ;

void constructHgeRect(hgeRect* rect)
{
    new (rect) hgeRect();
}

void constructHgeRect(hgeRect* rect, double x1, double y1, double x2, double y2)
{
    new (rect) hgeRect(x1, -y1, x2, -y2);
}

double rectX1(hgeRect* rect)
{
    return rect->x1;
}

double setX1(hgeRect* rect, double newX1)
{
    rect->x1 = newX1;
    return rect->x1;
}

double rectX2(hgeRect* rect)
{
    return rect->x2;
}

double setX2(hgeRect* rect, double newX2)
{
    rect->x2 = newX2;
    return rect->x2;
}

double rectY1(hgeRect* rect)
{
    return rect->y1;
}

double setY1(hgeRect* rect, double newY1)
{
    rect->y1 = newY1;
    return rect->y1;
}

double rectY2(hgeRect* rect)
{
    return rect->y2;
}

double setY2(hgeRect* rect, double newY2)
{
    rect->y2 = newY2;
    return rect->y2;
}

bool pointInside(hgeRect* rect, double x, double y)
{
    return rect->TestPoint(x, -y);
}

bool intersects(hgeRect* rect1, hgeRect* rect2)
{
    return rect1->Intersect(rect2);
}

void emptyConstructVec(hgeVector* vec)
{
    new (vec) hgeVector();
}

void constructVec(hgeVector* vec, float x, float y)
{
    new (vec) hgeVector(x, y);
}

hgeVector addVec(const hgeVector &vec, const hgeVector &vec2)
{
    return vec + vec2;
}

hgeVector subVec(const hgeVector &vec, const hgeVector &vec2)
{
    return vec - vec2;
}

hgeVector divVec(const hgeVector &vec, float val)
{
    return vec / val;
}

hgeVector multVec(const hgeVector &vec, float val)
{
    return vec * val;
}

double dotVec(const hgeVector &vec1, const hgeVector &vec2)
{
    return vec1.Dot(&vec2);
}

void constructEmptyColor(hgeColor* color)
{
    new (color) hgeColor();
}

void constructColor(hgeColor* color, double r, double g, double b, double a)
{
    new (color) hgeColor(r, g, b, a);
}

void constructColorDefAlpha(hgeColor* color, double r, double g, double b)
{
    new (color) hgeColor(r, g, b, 1.0);
}

hgeColor subColor(const hgeColor &c1, const hgeColor &c2)
{
    return c1 - c2;
}

hgeColor addColor(const hgeColor &c1, const hgeColor &c2)
{
    return c1 + c2;
}

hgeColor multColor(const hgeColor &c1, const hgeColor &c2)
{
    return c1 * c2;
}

hgeColor divideScalarColor(const hgeColor &c1, double val)
{
    return c1 / val;
}

hgeColor multScalarColor(const hgeColor &c1, double val)
{
    return c1 * val;
}

void UtilBinder::bind(asIScriptEngine* engine)
{
    BLEND_ALPHA_ADD = BLEND_ALPHAADD;
    BLEND_ALPHA_BLEND = BLEND_ALPHABLEND;
    BLEND_COLOR_ADD = BLEND_COLORADD;
    BLEND_COLOR_MUL = BLEND_COLORMUL;
    BLEND_NOZ_WRITE = BLEND_NOZWRITE;
    BLEND_Z_WRITE = BLEND_ZWRITE;
    BLEND_DEFAULTZ = BLEND_DEFAULT_Z;

    int r = 0;
    r = engine->RegisterGlobalProperty("const int BLEND_ALPHA_ADD", &BLEND_ALPHA_ADD); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_ALPHA_BLEND", &BLEND_ALPHA_BLEND); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_COLOR_ADD", &BLEND_COLOR_ADD); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_COLOR_MUL", &BLEND_COLOR_MUL); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_NOZ_WRITE", &BLEND_NOZ_WRITE); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_Z_WRITE", &BLEND_Z_WRITE); assert (r >= 0);
    r = engine->RegisterGlobalProperty("const int BLEND_DEFAULT", &BLEND_DEFAULTZ); assert (r >= 0);

    r = engine->RegisterObjectType("Rect", sizeof(hgeRect), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); //assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double left()", asFUNCTION(rectX1), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double left(double)", asFUNCTION(setX1), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double right()", asFUNCTION(rectX2), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double right(double)", asFUNCTION(setX2), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double top()", asFUNCTION(rectY1), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double top(double)", asFUNCTION(setY1), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double bottom()", asFUNCTION(rectY2), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "double bottom(double)", asFUNCTION(setY2), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "bool pointInside(double, double)", asFUNCTION(pointInside), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectMethod("Rect", "bool intersects(const Rect &in)", asFUNCTION(intersects), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void construct()", asFUNCTIONPR(constructHgeRect, (hgeRect*), void), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Rect", asBEHAVE_CONSTRUCT, "void construct(double, double, double, double)", asFUNCTIONPR(constructHgeRect, (hgeRect*, double, double, double, double), void), asCALL_CDECL_OBJFIRST); assert (r >= 0);

    r = engine->RegisterObjectType("Vector2", sizeof(hgeVector), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert (r >= 0);
    r = engine->RegisterObjectMethod("Vector2", "double length()", asMETHOD(hgeVector, Length), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Vector2", "double angleBetween(Vector2)", asMETHOD(hgeVector, Angle), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Vector2", "void clamp(const float)", asMETHOD(hgeVector, Clamp), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Vector2", "void normalize()", asMETHOD(hgeVector, Normalize), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Vector2", "void rotate(float)", asMETHOD(hgeVector, Rotate), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectProperty("Vector2", "float x", offsetof(hgeVector, x)); assert (r >= 0);
    r = engine->RegisterObjectProperty("Vector2", "float y", offsetof(hgeVector, y)); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(emptyConstructVec), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(constructVec), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD, "Vector2 f(const Vector2 &in, const Vector2 &in)", asFUNCTION(addVec), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_SUBTRACT, "Vector2 f(const Vector2 &in, const Vector2 &in)", asFUNCTION(subVec), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_DIVIDE, "Vector2 f(const Vector2 &in, float)", asFUNCTION(divVec), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_MULTIPLY, "Vector2 f(const Vector2 &in, float)", asFUNCTION(multVec), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_MULTIPLY, "double f(const Vector2 &in, const Vector2 &in)", asFUNCTION(dotVec), asCALL_CDECL); assert (r >= 0);

    r = engine->RegisterObjectType("Color", sizeof(hgeColor), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_CA); assert (r >= 0);
    r = engine->RegisterObjectMethod("Color", "void clamp()", asMETHOD(hgeColor, Clamp), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectProperty("Color", "double r", offsetof(hgeColor, r)); assert (r >= 0);
    r = engine->RegisterObjectProperty("Color", "double g", offsetof(hgeColor, g)); assert (r >= 0);
    r = engine->RegisterObjectProperty("Color", "double b", offsetof(hgeColor, b)); assert (r >= 0);
    r = engine->RegisterObjectProperty("Color", "double a", offsetof(hgeColor, a)); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(constructEmptyColor), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(double, double, double)", asFUNCTION(constructColorDefAlpha), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(double, double, double, double)", asFUNCTION(constructColor), asCALL_CDECL_OBJFIRST); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_ADD, "Color f(const Color &in, const Color &in)", asFUNCTION(addColor), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_SUBTRACT, "Color f(const Color &in, const Color &in)", asFUNCTION(subColor), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_DIVIDE, "Color f(const Color &in, double)", asFUNCTION(divideScalarColor), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_MULTIPLY, "Color f(const Color &in, double)", asFUNCTION(multScalarColor), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalBehaviour(asBEHAVE_MULTIPLY, "double f(const Color &in, const Color &in)", asFUNCTION(multColor), asCALL_CDECL); assert (r >= 0);

    r = engine->RegisterObjectType("Utils", 0, asOBJ_REF | asOBJ_NOHANDLE); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const int getRandomInt(const int& in, const int& in)", asMETHOD(Utils, getRandomInt), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const double getRandomDouble(const double& in, const double& in)", asMETHOD(Utils, getRandomDouble), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const double getFPS()", asMETHOD(Utils, getFPS), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const double getDTime()", asMETHOD(Utils, getDTime), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const double distanceBetween(Vector2, Vector2)", asMETHOD(Utils, distanceBetween), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const string& toString(int)", asMETHOD(Utils, intToString), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const string& toString(double)", asMETHOD(Utils, doubleToString), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const int toInt(const string& in)", asMETHOD(Utils, stringToInt), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "const double toDouble(const string& in)", asMETHOD(Utils, stringToDouble), asCALL_THISCALL); assert (r >= 0);
    r = engine->RegisterObjectMethod("Utils", "void writeToLog(const string &in, bool)", asMETHODPR(Utils, writeToLog, (const std::string&, bool), void), asCALL_THISCALL); assert (r >= 0);

    Utils* utils = Utils::get();
    engine->RegisterGlobalProperty("Utils utils", utils);
}
