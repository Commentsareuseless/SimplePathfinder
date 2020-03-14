#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include <wx/wx.h>
#include <vector>
#include <unordered_map>
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

    std::unordered_map<GridCoord*, GridCoord*> wayBack;
    std::unordered_map<GridCoord*, int> currentCost;

    bool ContainsNode(int x, int y, std::vector<GridCoord*>& list);
    int CalcCostFromStart(GridCoord* curr);
    int CalcCostToGoal(GridCoord* curr);
    // neigh must be relative to curr (Can't have absolute x and y)
    int MovementCost(const wxPoint& neigh);
    GridCoord* CheckCostInList(std::vector<GridCoord*>& list, GridCoord* parent);
    void RemoveNode(GridCoord* node, std::vector<GridCoord*>& list);
    void FindWayBack();
public:
    PathFinder(GridCoord* start, GridCoord* goal);
    //Initialize pathfinding
    bool FindWay();
    virtual ~PathFinder();
};
#endif
