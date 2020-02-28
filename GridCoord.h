#ifndef GRID_COORD_H
#define GRID_COORD_H
#include <wx/wx.h>

// Simple class to represent squares on main window 
class GridCoord : public wxPoint
{
public:
    enum FieldType
    {
        NORMAL, //default type
        START,  //Start node
        END,    //End node
        WALL,   //Wall node
        PATH,   //Final path
        SCANED, //Checked field which doesn't belong to shortest path
        SCANING, //Type of head of scaning wave xD
        ERROR
    };
private:
    FieldType _type;
    wxPoint parent; //for finding way backwards after reaching goal
    int sumCost = 0;
    int toStartCost;
    int toGoalCost;
    static unsigned int Colors[7];
public:
    GridCoord();
    GridCoord(int x, int y);
    void SetType(FieldType type);
    void SetCost(int sum, int toStart = 0, int toGoal = 0);
    FieldType GetType() const {return _type;}
    int GetSumCost() const {return sumCost;}
    int GetStartCost() const {return toStartCost;}
    int GetGoalCost() const {return toGoalCost;}
    unsigned int GetTypeColor() const;
};
#endif
