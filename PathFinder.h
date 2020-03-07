#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include <wx/wx.h>
#include <vector>
#include "GridCoord.h"

class PathFinder
{
    //Checked nodes
    std::vector<GridCoord*> mChecked;
    //Visually the outline of searched area
    std::vector<GridCoord*> mToCheck;

    GridCoord *neighbours[4];
    GridCoord *Start = nullptr;
    GridCoord *Goal = nullptr;

    bool ContainsNode(int x, int y);
    //returns input arg if lower cost doesn't exist 
    GridCoord* CheckCostInList(std::vector<GridCoord*>& list, GridCoord* toCheck);
    void FindWayBack();
    void RemoveScanedNodes();
public:
    PathFinder(GridCoord* start, GridCoord* goal);
    //Initialize pathfinding
    void FindWay();
    virtual ~PathFinder();
};
#endif
