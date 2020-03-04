#include "PathFinder.h"
#include "MainWindow.h"
#include <math.h>

PathFinder::PathFinder(GridCoord* start, GridCoord* goal) : Start(start), Goal(goal)
{}


void PathFinder::FindWay()
{
    wxPoint dirs[4] = {wxPoint(1,0), wxPoint(0,1), wxPoint(-1,0), wxPoint(0,-1)};

    if(mChecked.empty())
    {
        mChecked.push_back(Start);
    }

    GridCoord current = *Start;    //Current position
    current.CalculateCost(*Start, *Goal);
    for(size_t i = 0; current == *Goal; ++i)
    {
        if (i > 40000000)
        {
            std::cout << "Error!!!" << std::endl;   //Just in case xD
            throw "OVERFLOWWWWW";                   //It should be exception i guess, let os deal wit it heh
            break;
        }
        
        size_t n = 0;
        GridCoord *lowest = &current;
        //Check nodes in all directions
        for (auto dir : dirs)
        {
            if(current.x + dir.x >= 0 && current.y + dir.y >= 0)
            {
                size_t xx = current.x + dir.x;
                size_t yy = current.y + dir.y;
                if(!ContainsNode(xx, yy))
                {
                    mToCheck.push_back(new GridCoord(xx,yy));
                    mToCheck.back()->SetParent(current);
                    mToCheck.back()->CalculateCost(*Start, *Goal);
                    
                    // Find the lowest cost coord
                    lowest = CheckCostInList(mToCheck, lowest);
                    lowest = CheckCostInList(mChecked, lowest);
                }
            }
        }
        mChecked.push_back(lowest);
        current = *lowest;
    }
}

GridCoord* PathFinder::CheckCostInList(std::vector<GridCoord*>& list, GridCoord* toCheck)
{
    GridCoord* result = toCheck;
    size_t iter = 0;
    for(size_t i = 0; i < list.size(); ++i)
    {
        if (list[i]->GetSumCost() < toCheck->GetSumCost())
        {
            result = list[i];
            iter = i;
        }
        else if(list[i]->GetSumCost() == toCheck->GetSumCost())
        {
            (list[i]->GetGoalCost() < toCheck->GetGoalCost()) ? result = list[i] : result = toCheck;
        }
    }
        delete list[iter];
        list.erase(list.begin() + iter);
        list.shrink_to_fit();
        return result;
}


bool PathFinder::ContainsNode(int x, int y)
{
    for(auto coord : mChecked)
    {
        if(x == coord->x && y == coord->y)
        {return true;}
    }
    return false;
}

PathFinder::~PathFinder()
{
    for(auto item : mToCheck) {delete item;}
    for(auto item : mChecked) {delete item;}
}
