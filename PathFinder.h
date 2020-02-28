#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include <wx/wx.h>
#include <vector>
#include <queue>
#include "GridCoord.h"

class PathFinder
{
    std::vector<wxPoint> mChecked;
    std::queue<GridCoord> mToCheck;
    GridCoord Start;
    GridCoord Goal;

public:
    PathFinder(const GridCoord& start, const GridCoord& goal);
    void CalculateCost(const GridCoord& position);
    void CalculateCost(int x, int y);
    void FindWay();
};
#endif
