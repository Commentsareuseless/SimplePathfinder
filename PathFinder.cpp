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
        GridCoord *next = nullptr;
        //Check nodes in all directions
        for (auto dir : dirs)
        {
            if(current.x + dir.x >= 0 && current.y + dir.y >= 0)
            {
                size_t xx = current.x + dir.x;
                size_t yy = current.y + dir.y;
                // Later change mToCheck queue to local var if it wouldnt be necessary
                mToCheck.push(new GridCoord(xx,yy));
                mToCheck.front()->SetParent(current);
                mToCheck.front()->CalculateCost(*Start, *Goal);

                if(current.GetSumCost() > mToCheck.front()->GetSumCost())
                {
                    next = mToCheck.front();
                }
                else if(current.GetSumCost() == mToCheck.front()->GetSumCost())
                {
                    if(current.GetGoalCost() > mToCheck.front()->GetGoalCost())
                    {
                        next = mToCheck.front();
                    }
                }
                mChecked.push_back(mToCheck.front());
                delete mToCheck.front();
                mToCheck.pop();
            }
        }
        current = *next;
    }
}