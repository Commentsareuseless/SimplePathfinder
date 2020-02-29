#include "MainWindow.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

#include <iostream>

GridCoord* MainWindow::mCoordsTable = nullptr;
int MainWindow::mSquaresNum = 40;

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_PAINT(MainWindow::OnPaint)
EVT_BUTTON(MainWindow::START_NODE_B, MainWindow::OnNodeSelected)
EVT_BUTTON(MainWindow::END_NODE_B, MainWindow::OnNodeSelected)
EVT_BUTTON(MainWindow::WALL_NODE_B, MainWindow::OnNodeSelected)
EVT_LEFT_DOWN(MainWindow::OnLMBClick)
EVT_BUTTON(MainWindow::FIND_PATH_B, MainWindow::OnStartPathfinding)
EVT_BUTTON(MainWindow::RESTART_B, MainWindow::OnRestart)
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
    
    mNodeBar->AddControl(mStartNode, wxT("Start node"));
    mNodeBar->AddControl(mEndNode, wxT("End node"));
    mNodeBar->AddControl(mWallNode, wxT("Wall node"));
    mNodeBar->AddSeparator();
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
}

GridCoord& MainWindow::GetNode(int x, int y)
{
    if (mCoordsTable != nullptr)
    {
        return mCoordsTable[y * mSquaresNum + x];
    }//TODO: implement some exceptions in case table doesnt exist
     //Kinda unlikely xD
}

GridCoord& MainWindow::GetNode(const wxPoint& position)
{
    return GetNode(position.x, position.y);
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
    std::cout << "Selected: " << mSelectedNode << std::endl;
}

void MainWindow::OnLMBClick(wxMouseEvent& evt)
{
    wxPoint position = evt.GetPosition();
    if(position.x < mSquaresNum*sqrSize.GetX() && position.y < mSquaresNum*sqrSize.GetY())
    {    
        int n = ((position.y - mGridOffset)/mSqrWidth) * mSquaresNum + (position.x - mGridOffset)/mSqrWidth;
        mCoordsTable[n].SetType(mSelectedNode);
        this->Refresh(false);
        std::cout << "Click! on: " << n << std::endl;
    }
    evt.Skip();
}

void MainWindow::OnStartPathfinding(wxCommandEvent& evt)
{
    //TODO
    evt.Skip();
}

void MainWindow::OnRestart(wxCommandEvent& evt)
{
    // Just launch Refresh
    RefreshCoordsTable();
    evt.Skip();
}
