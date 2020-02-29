#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include <wx/wx.h>
#include <vector>
#include <queue>
#include "GridCoord.h"

class PathFinder
{
    std::vector<GridCoord*> mChecked;
    std::queue<GridCoord*> mToCheck;

    GridCoord *neighbours[4];
    GridCoord *Start = nullptr;
    GridCoord *Goal = nullptr;

public:
    PathFinder(GridCoord* start, GridCoord* goal);
    void FindWay();
};
#endif
