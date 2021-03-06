#include "GridCoord.h"

unsigned int GridCoord::Colors[] = {0x8f8f8fU, 0xc948cd, 0xc948cd, 0x1, 0x000fff, 0x20e11d, 0xff0f00};

GridCoord::GridCoord() : wxPoint(), _type(NORMAL) {}
GridCoord::GridCoord(int x, int y) : wxPoint(x ,y) ,_type(NORMAL) {}
GridCoord::GridCoord(const GridCoord& pos) : wxPoint(pos), _type(NORMAL) {}

void GridCoord::CalculateCost(const wxPoint& start, const wxPoint& goal)
{
    int toStartCost = abs(start.x - this->x) + abs(start.y - this->y);
    int toGoalCost = abs(goal.x - this->x) + abs(goal.y - this->y); 
    sumCost = toStartCost + toGoalCost;
}

void GridCoord::ResetToDfault()
{
    // SetParent(nullptr);
    SetPrio(0);
    SetCost(0);
    SetType(NORMAL);
}

unsigned int GridCoord::GetTypeColor() const
{
    switch (_type)
    {
    case NORMAL:
        return Colors[0];
        break;

    case START:
        return Colors[1];
    break;

    case END:
        return Colors[2];
        break;

    case WALL:
        return Colors[3];
        break;

    case PATH:
        return Colors[4];
        break;
    
    case SCANED:
        return Colors[5];
        break;

    case SCANING:
        return Colors[6];
        break;
    default:
        return ERROR;
        break;
    }
}

void GridCoord::SetCost(int sum)
{
    sumCost = sum;
//     toStartCost = toStart;
//     toGoalCost = toGoal;
}
