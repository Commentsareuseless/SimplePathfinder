#include "PathFinder.h"
#include "MainWindow.h"
#include <map>
#define MOVEMENT_COST 10

PathFinder::PathFinder(GridCoord* start, GridCoord* goal) : Start(start), Goal(goal)
{
    wayBack[Start] = nullptr;
    currentCost[Start] = 0;
    mToCheck.push_back(Start);
}

bool PathFinder::FindWay()
{
    if(Goal == nullptr || Start == nullptr)
    {
        std::cerr << "Start or Goal node doesn't exist\n";
        return false;
    }
    int wdth = MainWindow::GetNodeWidth();
    wxPoint dirs[] = {wxPoint(wdth,0), wxPoint(0,wdth), wxPoint(-wdth,0), wxPoint(0,-wdth)
                        /*,wxPoint(wdth, wdth), wxPoint(-wdth, wdth), wxPoint(wdth, -wdth), wxPoint(-wdth, -wdth)*/};

    GridCoord* current;    //Current position
        
    current = CheckCostInList(mToCheck, current);
    if(current == Goal) 
    {
        FindWayBack();
        return true;
    }
        current->SetType(GridCoord::SCANED);

        std::cout << "-------------------\n";
        std::cout << "Current: " << current->x << " " << current->y << std::endl;
        //Check neighbour nodes in all directions
        for (auto dir : dirs)
        {
            if((current->x + dir.x >= 0) && (current->y + dir.y >= 0))
            { 
                size_t xx = current->x + dir.x;
                size_t yy = current->y + dir.y;
                GridCoord* currNeighbour = MainWindow::GetNode(xx, yy);
                if(currNeighbour->GetType() == GridCoord::WALL) 
                    {continue;}

                int cost = currentCost.at(current) + MovementCost(dir);
                if((currentCost.find(currNeighbour) == currentCost.end())
                    || (cost < currentCost.at(currNeighbour)))
                {
                    currentCost[currNeighbour] = cost;
                    currNeighbour->SetPrio(cost + CalcCostToGoal(currNeighbour));
                    currNeighbour->SetType(GridCoord::SCANING);
                    mToCheck.push_back(currNeighbour);
                    wayBack[currNeighbour] = current;
                }

            }
        }
        // std::cout << "Lowest cost tile: " << lowest->x << " " << lowest->y;
        std::cout << "\n---------------------\n";
        
        return false;
}

GridCoord* PathFinder::CheckCostInList(std::vector<GridCoord*>& list, GridCoord* parent)
{
    GridCoord* result = list.back();
    size_t iter = 0;
    for(size_t i = 0; i < list.size() - 1; ++i) //-1 bcs we assigned last element to result
    {
        if (list[i]->GetPrio() <= result->GetPrio())
        {
            result = list[i];
            iter = i;
        }
        // else if(list[i]->GetSumCost() == result->GetSumCost())
        // {
        //     (list[i]->GetGoalCost() < result->GetGoalCost()) ? (result = list[i]) : (result);
        // }
    }

    list.erase(list.begin() + iter);
    return result;
}

void PathFinder::RemoveNode(GridCoord* node, std::vector<GridCoord*>& list)
{
    for(int i(0); i < list.size(); i++)
    {
        if(node == list[i])
        {
            list.erase(list.begin() + i);
            return;
        }
    }
}

bool PathFinder::ContainsNode(int x, int y, std::vector<GridCoord*>& list)
{
    for(auto coord : list)
    {
        if((x == coord->x) && (y == coord->y)) {return true;}
    }
    return false;
}

int PathFinder::CalcCostFromStart(GridCoord* curr)
{
    int dx = abs(curr->x - Start->x) / MainWindow::GetNodeWidth();
    int dy = abs(curr->y - Start->y) / MainWindow::GetNodeWidth();
    return (dx + dy) * MOVEMENT_COST;
}

int PathFinder::CalcCostToGoal(GridCoord* curr)
{
    int dx = abs(curr->x - Goal->x) / MainWindow::GetNodeWidth();
    int dy = abs(curr->y - Goal->y) / MainWindow::GetNodeWidth();
    return (dx + dy) * MOVEMENT_COST;
}

int PathFinder::MovementCost(const wxPoint& neigh)
{
    //Check for diagonal nodes
    return ((neigh.x == 0) || (neigh.y == 0)) ? (MOVEMENT_COST) : (MOVEMENT_COST * 1.4);
}

void PathFinder::FindWayBack()
{
    GridCoord* current = Goal;
    int i(0);
    while (current != Start)
    {
        if(current == nullptr)
        {
            std::cerr << "Error lul\n";
            return;
        }
        std::cout << "Finding way bac!\n" << i << "\n" << current->x << " " << current->y << "\n";
        current->SetType(GridCoord::PATH);
        current = wayBack.at(current);
        // current = current->GetParent();
        ++i;
    }
}


PathFinder::~PathFinder()
{
    // No need to free memmory since this class usess MainWindow::mCoordsTable pointers lul
    // for(auto item : mToCheck) {delete item;}
    // for(auto item : mChecked) {delete item;}
}
