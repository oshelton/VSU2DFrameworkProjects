/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#include <iostream>
#include <windows.h>
#include <math.h>
#include <Utils.h>
#include "TriangleShape.h"
#include "PointShape.h"
#include "AlgorithmRunner.h"

using namespace std;

AlgorithmRunner::AlgorithmRunner()
{
    ofstream report;
    report.open("../report.txt", ios::trunc);
    report << "Polygon triangulation report.  This file is reset whenver the application is restarted.\n";
    report.close();
}

void AlgorithmRunner::calculateMaxMin(const hgeVector& p1, const hgeVector& p2, const hgeVector& p3, hgeVector& minOut, hgeVector& maxOut)
{
    minOut.x = p1.x;
    minOut.y = p1.y;
    maxOut.x = p1.x;
    maxOut.y = p1.y;

    if (p2.x < minOut.x)
        minOut.x = p2.x;
    else if (p2.x > maxOut.x)
        maxOut.x = p2.x;

    if (p3.x < minOut.x)
        minOut.x = p3.x;
    else if (p3.x > maxOut.x)
        maxOut.x = p3.x;

    if (p2.y < minOut.y)
        minOut.y = p2.y;
    else if (p2.y > maxOut.y)
        maxOut.y = p2.y;

    if (p3.y < minOut.y)
        minOut.y = p3.y;
    else if (p3.y > maxOut.y)
        maxOut.y = p3.y;
}

const bool AlgorithmRunner::pointsClockwise(CyclicVector<hgeVector> points)
{
    double sum = 0;

    for (int i = 0; i < points.size() - 1; ++i)
        sum += (points[i].x * points[i + 1].y - points[i + 1].x * points[i].y);

    if (sum < 0)
        return true;
    else
        return false;
}

bool AlgorithmRunner::vertexConvex(const hgeVector& v1, const hgeVector& v2, const hgeVector& v3)
{
    double sum = 0;

    sum += v1.x * (v3.y - v2.y);
    sum += v2.x * (v1.y - v3.y);
    sum += v3.x * (v2.y - v1.y);

    if (sum < 0)
        return false;
    else
        return true;
}

bool AlgorithmRunner::pointInsideStandard(const hgeVector& A, const hgeVector& B, const hgeVector& C, const hgeVector& P)
{
    hgeVector v0 = C - A;
    hgeVector v1 = B - A;
    hgeVector v2 = P - A;

    double dot00 = v0.Dot(&v0);
    double dot01 = v0.Dot(&v1);
    double dot02 = v0.Dot(&v2);
    double dot11 = v1.Dot(&v1);
    double dot12 = v1.Dot(&v2);

    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u > 0) && (v > 0) && (u + v < 1);
}

bool AlgorithmRunner::pointInsideOptomized(const hgeVector& minCoords, const hgeVector& maxCoords, const hgeVector& A, const hgeVector& B, const hgeVector& C, const hgeVector& P)
{
    if (P.x <= minCoords.x || P.x >= maxCoords.x || P.y <= minCoords.y || P.y >= maxCoords.y)
        return false;
    else
    {
        return pointInsideStandard(A, B, C, P);
    }
}

void AlgorithmRunner::processShapeStandard(vector<hgeVector>* points, TriangleShape* output)
{
    if (points->size() == 3)
        output->addTriangle(points->at(0), points->at(1), points->at(2));
    else if (points->size() > 3)
    {
        for (int i = 0; i < points->size() - 2; ++i)
        {
            if (!vertexConvex(points->at(i), points->at(i + 1), points->at(i + 2)))
                continue;

            if (i > 0)
            {
                for (int j = 0; j < i; ++j)
                {
                    if (pointInsideStandard(points->at(i), points->at(i + 1), points->at(i + 2), points->at(j)))
                        continue;
                }
            }

            if (i < points->size() - 3)
            {
                for (int j = i + 3; j < points->size(); ++j)
                {
                    if (pointInsideStandard(points->at(i), points->at(i + 1), points->at(i + 2), points->at(j)))
                        continue;
                }
            }

            output->addTriangle(points->at(i), points->at(i + 1), points->at(i + 2));
            points->erase(points->begin() + i + 1);
        }

        bool validEar = true;

        if (vertexConvex(points->at(points->size() - 2), points->at(points->size() - 1), points->at(0)))
        {
            for (int i = 1; i < points->size() - 1; ++ i)
            {
                if (pointInsideStandard(points->at(points->size() - 2), points->at(points->size() - 1), points->at(0), points->at(i)))
                {
                    validEar = false;
                    break;
                }
            }

            if (validEar)
            {
                validEar = true;
                output->addTriangle(points->at(points->size() - 2), points->at(points->size() - 1), points->at(0));
                points->erase(points->end());
            }
        }

        validEar = true;

        if (vertexConvex(points->at(points->size() - 1), points->at(0), points->at(1)))
        {
            for (int i = 2; i < points->size() - 1; ++ i)
            {
                if (pointInsideStandard(points->at(points->size() - 1), points->at(0), points->at(1), points->at(i)))
                {
                    validEar = false;
                    break;
                }
            }

            if (validEar)
            {
                output->addTriangle(points->at(points->size() - 1), points->at(0), points->at(1));
                points->erase(points->begin());
            }
        }

        processShapeStandard(points, output);
    }
    else if (points->size() < 3)
        Utils::get()->writeToLog("Error converting polygon!");
}

void AlgorithmRunner::processShapeOptomized(CyclicVector<hgeVector> points, TriangleShape* output)
{
    if (!pointsClockwise(points))
    {
        for (int i = 0; i < points.size() / 2; ++i)
        {
            hgeVector tmp = points[i];
            points[i] = points[points.size() - 1 - i];
            points[points.size() - 1 - i] = tmp;
        }
    }

    CyclicVector<hgeVector>::iterator iter1 = points.begin();
    while (points.size() > 3)
    {
        hgeVector point1 = *iter1;
        hgeVector point2 = points[iter1.getIndex() + 1];
        hgeVector point3 = points[iter1.getIndex() + 2];

        if (vertexConvex(point1, point2, point3))
        {
            hgeVector minRect(0, 0);
            hgeVector maxRect(0, 0);
            calculateMaxMin(point1, point2, point3, minRect, maxRect);

            CyclicVector<hgeVector>::iterator iter2 = iter1 + 3;
            bool validEar = true;
            while (iter2 != iter1)
            {
                if (pointInsideOptomized(minRect, maxRect, point1, point2, point3, *iter2))
                {
                    validEar = false;
                    break;
                }
                else
                    ++iter2;
            }

            if (validEar)
            {
                output->addTriangle(point1, point2, point3);
                points.erase(iter1 + 1);
            }
        }
        ++iter1;
    }
    output->addTriangle(points[0], points[1], points[2]);
}

void AlgorithmRunner::convertShape(PointShape* shape, TriangleShape* output1, TriangleShape* output2)
{
    const bool clockwise = pointsClockwise(shape->getPoints());

    LARGE_INTEGER start;
    LARGE_INTEGER end;
    LARGE_INTEGER elapsed1;

    if (clockwise)
    {
        QueryPerformanceCounter(&start);

        vector<hgeVector> points1 = shape->getPoints().getSource();
        processShapeStandard(&points1, output1);

        QueryPerformanceCounter(&end);

        elapsed1.QuadPart = end.QuadPart - start.QuadPart;
    }

    QueryPerformanceCounter(&start);

    processShapeOptomized(shape->getPoints(), output2);

    QueryPerformanceCounter(&end);

    LARGE_INTEGER elapsed2;
    elapsed2.QuadPart = end.QuadPart - start.QuadPart;

    ofstream report;
    report.open("../report.txt", ios::app);

    if (clockwise)
        report << "\nClock Cycles Taken for Unoptomized Algorithm: " << elapsed1.QuadPart;
    else
        report << "\nClock Cycles Taken for Unoptomized Algorithm: " << "N/A";
    report << "\nClock Cycles Taken for Optomized Algorithm: " << elapsed2.QuadPart;
    if (clockwise)
    {
        report << "\nTime differencial, positive value means optomized version was faster: " << elapsed1.QuadPart - elapsed2.QuadPart;
        report << "\nDecrease %: " << (100 - (double)elapsed2.QuadPart / (double)elapsed1.QuadPart * 100);
    }
    else
    {
        report << "\nTime differencial, positive value means optomized version was faster: " << "N/A";
        report << "\nDecrease %: " << "N/A";
    }
    report << "\n Shape Points: " << shape->getSummary();
    if (clockwise)
        report << "\n Unoptomized Output: " << output1->getSummary();
    else
        report << "\n Unoptomized Output: " << "N/A";
    report << "\n Optomized Output: " << output2->getSummary() << "\n";

    report.close();
}
