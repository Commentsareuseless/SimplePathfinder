#include "MainWindow.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

#include <iostream>

GridCoord* MainWindow::mCoordsTable = nullptr;
int MainWindow::mSquaresNum = 40;
int MainWindow::mGridOffset = 0;
int MainWindow::mSqrWidth = 0;
wxSize MainWindow::sqrSize = wxSize();


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_PAINT(MainWindow::OnPaint)
EVT_BUTTON(MainWindow::START_NODE_B, MainWindow::OnNodeSelected)
EVT_BUTTON(MainWindow::END_NODE_B, MainWindow::OnNodeSelected)
EVT_BUTTON(MainWindow::WALL_NODE_B, MainWindow::OnNodeSelected)
EVT_BUTTON(MainWindow::FIND_PATH_B, MainWindow::OnStartPathfinding)
EVT_BUTTON(MainWindow::RESTART_B, MainWindow::OnRestart)
EVT_LEFT_DOWN(MainWindow::OnLMBClick)
EVT_TIMER(MainWindow::TIMER_T, MainWindow::OnTimer)
wxEND_EVENT_TABLE()


MainWindow::MainWindow(const wxString& name) : wxFrame(nullptr, wxID_ANY, name, wxDefaultPosition, wxSize(1024, 860))
{
    Colors[0] = 0xc948cd;
    Colors[1] = 0xff8f00;
    Colors[2] = 0x35464d;
    mGridOffset = 10;

    wxColour bgColour(0xafafaf);
    wxColour panColour(0xffff00);
    this->SetBackgroundColour(bgColour);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mNodeBar = this->CreateToolBar(wxTB_RIGHT);
    mStartNode = new wxButton(mNodeBar, START_NODE_B, wxT("Start"));
    mStartNode->SetBackgroundColour(Colors[0]);
    mEndNode = new wxButton(mNodeBar, END_NODE_B, wxT("End"));
    mEndNode->SetBackgroundColour(Colors[1]);
    mWallNode = new wxButton(mNodeBar, WALL_NODE_B, wxT("Wall"));

    mRestartMap = new wxButton(mNodeBar, RESTART_B, wxT("Restart"));
    mFindPath = new wxButton(mNodeBar, FIND_PATH_B, wxT("Find path"));
    
    mNodeBar->AddControl(mStartNode, wxT("Start node"));
    mNodeBar->AddControl(mEndNode, wxT("End node"));
    mNodeBar->AddControl(mWallNode, wxT("Wall node"));
    mNodeBar->AddSeparator();
    mNodeBar->AddControl(mFindPath, wxT("Find path"));
    mNodeBar->AddControl(mRestartMap, wxT("Restart"));
    //Initialize table (Refresh but whatever)
    RefreshCoordsTable();
}

void MainWindow::RefreshCoordsTable()
{
    //Delete prev table
    delete [] mCoordsTable;

    wxSize screenSize = this->GetScreenRect().GetSize() - wxSize(100,50);
    mSqrWidth = wxMin<int>(screenSize.GetWidth() / mSquaresNum, screenSize.GetHeight()/mSquaresNum);
    sqrSize = wxSize(mSqrWidth, mSqrWidth);

    mCoordsTable = new GridCoord [mSquaresNum*mSquaresNum];
    for (size_t y = 0; y < mSquaresNum; ++y)
    {
        for(size_t x = 0; x < mSquaresNum; ++x)
        {
            int n = y*mSquaresNum + x;
            mCoordsTable[n] = GridCoord(x * mSqrWidth + mGridOffset, y * mSqrWidth + mGridOffset);
        }
    }
    std::cout << "Restarted" << std::endl;
}

GridCoord* MainWindow::GetNode(int x, int y)
{
    size_t n = ((y -  mGridOffset) / mSqrWidth) * mSquaresNum + (x - mGridOffset)/mSqrWidth;
    std::cout << "Returned n= " << n << std::endl;
    return &mCoordsTable[n];
}

GridCoord* MainWindow::GetNode(const wxPoint& position)
{
    return GetNode(position.x, position.y);
}

int MainWindow::GetNodeWidth()
{
    return mSqrWidth;
}

int MainWindow::GetNodeOffset() 
{
    return mGridOffset;
}

void MainWindow::OnPaint(wxPaintEvent& evt)
{    
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}

void MainWindow::OnDraw(wxDC& dc)
{
    dc.Clear();

    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();
    dc.SetPen(pen);

    for (size_t y = 0; y < mSquaresNum; ++y)
    {
        for(size_t x = 0; x < mSquaresNum; ++x)
        {
            int n = y*mSquaresNum + x;
            brush.SetColour(mCoordsTable[n].GetTypeColor());
            dc.SetBrush(brush);
            dc.DrawRectangle(mCoordsTable[n], sqrSize);
        }
    }
}

void MainWindow::OnNodeSelected(wxCommandEvent& evt)
{
    int id = evt.GetId();

    switch (id)
    {
    case START_NODE_B:                      //TODO: check for existing start and end nodes and 
        mSelectedNode = GridCoord::START;   //don't let 2 of any of them exist simultaniusly
        break;
    
    case END_NODE_B:
        mSelectedNode = GridCoord::END;
        break;

    case WALL_NODE_B:
        mSelectedNode = GridCoord::WALL;
        break;

    default:
        mSelectedNode = GridCoord::ERROR;
        break;
    }
    // std::cout << "Selected: " << mSelectedNode << std::endl;
}

void MainWindow::OnLMBClick(wxMouseEvent& evt)
{
    wxPoint position = evt.GetPosition();
    if(position.x < mSquaresNum*sqrSize.GetX() && position.y < mSquaresNum*sqrSize.GetY())
    {    
        int n = ((position.y - mGridOffset)/mSqrWidth) * mSquaresNum + (position.x - mGridOffset)/mSqrWidth;
        if(mSelectedNode == GridCoord::START)
        {
            if (mStart != nullptr) mStart->ResetToDfault();
            mStart = &mCoordsTable[n];
            mStart->SetType(mSelectedNode);  
        }
        if(mSelectedNode == GridCoord::END)
        {
            if(mGoal != nullptr) mGoal->ResetToDfault();
            mGoal = &mCoordsTable[n];
            mGoal->SetType(mSelectedNode);  
        }
        mCoordsTable[n].SetType(mSelectedNode);
        this->Refresh(false);
        std::cout << "Click! on: " << n << " " << mCoordsTable[n].x << " " << mCoordsTable[n].y << std::endl;
    }
    evt.Skip();
}

void MainWindow::OnStartPathfinding(wxCommandEvent& evt)
{
    // RefreshCoordsTable();
    if(isTimerOn)
    {
        mTimer->Stop();
        delete pathFinder;
        delete mTimer;
        isTimerOn = false;
    }
    else
    {
        mTimer = new wxTimer(this, TIMER_T);
        pathFinder = new PathFinder(mStart, mGoal);
        mTimer->Start(10);
        isTimerOn = true;
    }
    evt.Skip();
}

void MainWindow::OnRestart(wxCommandEvent& evt)
{
    // Just launch Refresh
    RefreshCoordsTable();
    mTimer->Stop();
    delete pathFinder;
    delete mTimer;
    isTimerOn = false;
    this->Refresh(false);
    evt.Skip();
}

void MainWindow::OnTimer(wxTimerEvent& evt)
{
    if(pathFinder->FindWay())
    {
        std::cout << "Finished!" << std::endl;
        isTimerOn = false;
        mTimer->Stop();
        this->Refresh(false);
    }
    this->Refresh();
    evt.Skip();
}

