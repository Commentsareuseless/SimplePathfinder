#include "PathFinder.h"
#include "MainWindow.h"
#include <math.h>

PathFinder::PathFinder(const GridCoord& start, const GridCoord& goal) : Start(start), Goal(goal)
{}

//Let it return GridCoord obj with set costs
void PathFinder::CalculateCost(const GridCoord& position)
{
    int toStartCost;
    int toGoalCost;
    int sumCost;

    toStartCost = abs(Start.x - position.x) + abs(Start.y - position.y);
    toGoalCost = abs(Goal.x - position.x) + abs(Goal.y - position.y); 
    sumCost = toStartCost + toGoalCost;
    
    MainWindow::GetTile(position).SetCost(sumCost, toStartCost, toGoalCost);   
}

void PathFinder::CalculateCost(int x, int y)
{
    CalculateCost(GridCoord(x, y));
}

void PathFinder::FindWay()
{
    wxPoint dirs[4] = {wxPoint(1,0), wxPoint(0,1), wxPoint(-1,0), wxPoint(0,-1)};

    if(mToCheck.empty())
    {
        mToCheck.push(Start);
    }

    GridCoord current;    //Current position
    for(size_t i = 0; current == Goal; ++i)
    {
        if (i > 40000000)
        {
            std::cout << "Error!!!" << std::endl;   //Just in case xD
            throw "OVERFLOWWWWW";                   //It should be exception i guess, let os deal wit it heh
            break;
        }
        
        current = mToCheck.front();
        GridCoord next;
        //Check tiles in all directions
        for (auto dir : dirs)
        {
            if(current.x + dir.x >= 0 && current.y + dir.y >= 0)
            {
                //Change this func
                CalculateCost(current.x + dir.x, current.y + current.y);
                if (MainWindow::GetTile(current.x + dir.x, current.y + current.y).GetSumCost() > current.GetSumCost())
                {
                    current.SetCost()
                    next = current;
                }
                
                mChecked.push_back(wxPoint(current.x + dir.x, current.y + current.y));
            }
        }
        


    }
}