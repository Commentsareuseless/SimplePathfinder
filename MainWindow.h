#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wx/wx.h"
#include "GridCoord.h"
#include "PathFinder.h"

class MainWindow : public wxFrame
{
private:
    static GridCoord *mCoordsTable;
    GridCoord* mStart = nullptr;    //Quick ref to start and goal node not to iterate over
    GridCoord* mGoal = nullptr;     //whole mCoordsTable

    wxToolBar *mNodeBar = nullptr;
    wxButton *mStartNode = nullptr;
    wxButton *mEndNode = nullptr;
    wxButton *mWallNode = nullptr;
    //TODO: 
    wxButton *mFindPath = nullptr;
    wxButton *mRestartMap = nullptr;

    unsigned long Colors[3];
    GridCoord::FieldType mSelectedNode;
    static int mSquaresNum;
    static int mGridOffset;
    static int mSqrWidth;
    static wxSize sqrSize;

    wxTimer* mTimer = nullptr;
    bool isTimerOn = false;
    PathFinder* pathFinder = nullptr;

public:
    MainWindow(const wxString& name);
    //Get reference to apropriate tile form mCoordTable
    static GridCoord* GetNode(int x, int y);
    static GridCoord* GetNode(const wxPoint& position); 
    static int GetNodeWidth();
    static int GetNodeOffset();
    //Set every tile to default colour
    void RefreshCoordsTable();
    void OnPaint(wxPaintEvent& evt);
    void OnDraw(wxDC& dc); 
    //Handle click on squares
    void OnLMBClick(wxMouseEvent& evt);
    //Get pressed button id and figure out what node was selected
    void OnNodeSelected(wxCommandEvent& evt);
    void OnStartPathfinding(wxCommandEvent& evt);
    void OnRestart(wxCommandEvent& evt);
    void OnTimer(wxTimerEvent& evt);

    //Maybe todo but not very important
    static bool ContainsNodeOfType(GridCoord::FieldType type);
    static void ClearNodesOfType(GridCoord::FieldType type); //For clearing start and end nodes so there is only 1 on grid
    
    enum IDs{
        // *_B == wxButton 
        unused = 10000,
        START_NODE_B,
        END_NODE_B,
        WALL_NODE_B,
        FIND_PATH_B,
        RESTART_B,
        TIMER_T
    };

    wxDECLARE_EVENT_TABLE();
};
#endif
