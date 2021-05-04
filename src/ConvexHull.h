#pragma once

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <fstream>

struct Point
{
    double x;
    double y;
    int index;
};

class Plain
{
public:
    std::vector<Point> points;

    Point p0;

    Point secondTop(std::stack<Point>& stack)
    {
        Point tempPoint = stack.top();
        stack.pop();
        Point res = stack.top();
        stack.push(tempPoint);
        return res;
    }

    double squaredDist(Point p1, Point p2)
    {
        return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    int findMinIndex()
    {
        double minY = points[0].y;
        int min = 0;
        for(int i = 1; i < points.size(); i++)
        {
            double y = points[i].y;

            if((y < minY) || (minY == y) && points[i].x < points[min].x)
            {
                minY = points[i].y;
                min = i;
            }
        }

        return min;
    }

    int direction(Point a, Point b, Point c)
    {
        double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

        if(val == 0)
        {
            return 0;
        }
        else if(val < 0)
        {
            return 2;
        }

        return 1;
    }

    std::vector<Point> findConvexHull()
    {
        std::vector<Point> res;
        std::stack<Point> stack;

        int min = findMinIndex();

        std::swap(points[0], points[min]);

        p0 = points[0];

        std::sort(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2) -> bool
        {
            int dir = direction(p0, p1, p2);

            switch(dir)
            {
                case 0:
                    return squaredDist(p0, p2) >= squaredDist(p0, p1);
                case 1:
                    return false;
                case 2:
                    return true;
            }
        });

        int arrSize = 1;
        for(int i = 1; i < points.size(); i++)
        {
            while(i < points.size() - 1 && direction(p0, points[i], points[i + 1]) == 0)
            {
                i++;
            }
            points[arrSize] = points[i];
            arrSize++;
        }

        stack.push(points[0]);
        stack.push(points[1]);
        stack.push(points[2]);

        for(int i = 3; i < arrSize; i++)
        {
            while(direction(secondTop(stack), stack.top(), points[i]) != 2)
            {
                stack.pop();
            }
            stack.push(points[i]);
        }

        for(int i = stack.size(); i > 0; i--)
        {
            res.push_back(stack.top());
            stack.pop();
        }

        return res;
    }
};
