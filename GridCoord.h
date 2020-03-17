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
    //for finding way backwards after reaching goal
    // GridCoord* mParent = nullptr;
    int sumCost = 0;
    int priority = 0;
    // int toStartCost = 0;
    // int toGoalCost = 0;
    static unsigned int Colors[7];
public:
    GridCoord();
    GridCoord(const GridCoord& pos);
    GridCoord(int x, int y);

    void CalculateCost(const wxPoint& start, const wxPoint& goal);
    void ResetToDfault();

    void SetType(FieldType type) {_type = type;}
    void SetCost(int sum/*, int toStart = 0, int toGoal = 0*/);
    // void SetParent(GridCoord* parent) {mParent = parent;}
    void SetPrio(int p) {priority = p;}

    int GetSumCost() const {return sumCost;}
    int GetPrio() const {return priority;}
    // int GetStartCost() const {return toStartCost;}
    // int GetGoalCost() const {return toGoalCost;}
    // GridCoord* GetParent() const {return mParent;}
    FieldType GetType() const {return _type;}
    unsigned int GetTypeColor() const;
};
#endif
