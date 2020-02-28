#include "Launcher.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(Launcher);

bool Launcher::OnInit(){
    MainWindow *NewWindow = new MainWindow("Beniz");
    NewWindow->Show(true);

    return true; 
}