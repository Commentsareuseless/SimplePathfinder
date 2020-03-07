#include "PathFinder.h"
#include "MainWindow.h"
//#include <math.h>

PathFinder::PathFinder(GridCoord* start, GridCoord* goal) : Start(start), Goal(goal)
{}

void PathFinder::FindWay()
{
    if(Goal == nullptr || Start == nullptr)
    {
        std::cerr << "Start or Goal node doesn't exist\n";
        return;
    }
    int offs = MainWindow::GetNodeOffset();
    int wdth = MainWindow::GetNodeWidth();
    int fact = offs + wdth;
    wxPoint dirs[] = {wxPoint(wdth,0), wxPoint(0,wdth), wxPoint(-wdth,0), wxPoint(0,-wdth),
                        wxPoint(wdth, wdth), wxPoint(-wdth, wdth), wxPoint(wdth, -wdth), wxPoint(-wdth, -wdth)};

    if(mChecked.empty())
    {
        mChecked.push_back(Start);
    }

    GridCoord* current = Start;    //Current position
    current->CalculateCost(*Start, *Goal);
    for(size_t i = 0; current != Goal; ++i)
    {
        if (i > 40000000)
        {
            std::cout << "Error!!!" << std::endl;   //Just in case xD
            throw "OVERFLOWWWWW";                   //It should be exception i guess, let os deal wit it heh
            break;
        }
        
        size_t n = 0;
        //Lowest cost node
        GridCoord *lowest = current;
        std::cout << "-------------------\n";
        std::cout << "Current: " << current->x << " " << current->y << std::endl;
        //Check nodes in all directions
        for (auto dir : dirs)
        {
            if((current->x + dir.x >= 0) && (current->y + dir.y >= 0))
            { 
                size_t xx = current->x + dir.x;
                size_t yy = current->y + dir.y;
                // if(MainWindow::GetNode(xx,yy)->GetType() == GridCoord::WALL)
                //     {continue;}
                std::cout << "xx= " << xx << "yy=" << yy << std::endl;
                if(!ContainsNode(xx, yy))
                {
                    //A little unsafe but saves lots of memory
                    mToCheck.push_back(MainWindow::GetNode(xx,yy));
                    mToCheck.back()->SetParent(current);
                    mToCheck.back()->CalculateCost(*Start, *Goal);
                    mToCheck.back()->SetType(GridCoord::SCANING);
                    std::cout << "Cost=" << current->GetSumCost() << "\n";
                    std::cout << "Goal=" << current->GetGoalCost() << "\n";
                    std::cout << "Start=" << current->GetStartCost() << "\n";

                    // Find the lowest cost coord
                    lowest = CheckCostInList(mToCheck, lowest);
                    lowest = CheckCostInList(mChecked, lowest);
                    std::cout << "Lowest cost tile: " << lowest->x << " " << lowest->y;
                    std::cout << "\n---------------------\n";
                }
            }
        }
        lowest->SetType(GridCoord::SCANED);
        mChecked.push_back(lowest);
        current = lowest;
        RemoveScanedNodes();
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
            (list[i]->GetGoalCost() < toCheck->GetGoalCost()) ? (result = list[i]) : (result = toCheck);
        }
    }
    return result;
}


bool PathFinder::ContainsNode(int x, int y)
{
    for(auto coord : mChecked)
    {
        if((x == coord->x) && (y == coord->y))
        {return true;}
    }
    return false;
}

void PathFinder::RemoveScanedNodes()
{
    for(size_t n = 0; n < mToCheck.size(); n++)
    {
        if(mToCheck[n]->GetType() == GridCoord::SCANED)
        {
            mToCheck.erase(mToCheck.begin() + n);
        }
    }
    mToCheck.shrink_to_fit();
}

PathFinder::~PathFinder()
{
    // No need to free memmory since this class usess MainWindow::mCoordsTable pointers lul
    // for(auto item : mToCheck) {delete item;}
    // for(auto item : mChecked) {delete item;}
}
