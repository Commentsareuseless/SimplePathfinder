#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "wx/wx.h"
#include "GridCoord.h"

class MainWindow : public wxFrame
{
private:
    static GridCoord *mCoordsTable;

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
    int mGridOffset;
    int mSqrWidth;
    wxSize sqrSize;

public:
    MainWindow(const wxString& name);
    //Get reference to apropriate tile form mCoordTable
    static GridCoord& GetTile(int x, int y);
    static GridCoord& GetTile(const wxPoint& position); 
    //Set every tile to default colour
    void RefreshCoordsTable();
    void OnPaint(wxPaintEvent& evt);
    void OnDraw(wxDC& dc); 
    //Handle click on squares
    void OnLMBClick(wxMouseEvent& evt);
    //Get pressed button id and figure out what node was selected
    void OnNodeSelected(wxCommandEvent& evt);



    enum IDs{
        // *_B == wxButton 
        unused = 10000,
        START_NODE_B,
        END_NODE_B,
        WALL_NODE_B,
        FIND_PATH_B,
        RESTART_B
    };

    wxDECLARE_EVENT_TABLE();
};
#endif
