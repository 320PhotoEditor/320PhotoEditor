#include "MosaicTool.h"
#include "../GUI/GUIElement.h"
#include <tchar.h>
#include <atlstr.h>
#include <windows.h>

MosaicTool::MosaicTool(sf::Texture* up, sf::Texture* down, sf::Texture* over) : Tool(up, down, over)
{
}

void MosaicTool::init()
{
}

void MosaicTool::start(Layer* layer)
{
    this->layer = layer;
}

// Not supported for Apple products yet
std::string MosaicTool::openFileDialog(sf::RenderWindow* parentWindow)
{
//#include <tchar.h>
//#include <atlstr.h>
//#include <windows.h>

    //char filename[MAX_PATH];

    OPENFILENAME ofn;
    TCHAR szFile[260] = { 0 };
    //ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = (HWND)parentWindow->getSystemHandle();  // If you have a window to center over, put its HANDLE here
    //ofn.lpstrFilter = "\0*.jpeg\0*.png\0*.jpg\0";
    ofn.lpstrFilter = _T("\0*.jpeg\0*.png\0*.jpg\0");
    //ofn.lpstrFile = ofn;
    ofn.lpstrFile = szFile;
    //ofn.nMaxFile = MAX_PATH;
    ofn.nMaxFile = sizeof(szFile);
    //ofn.lpstrTitle = "Select a File, yo!";
    ofn.lpstrTitle = NULL;
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)==TRUE)
    {
        std::cout << "You chose the file \"" << GetOpenFileName(&ofn) << "\"\n";
        return std::string(CW2A(ofn.lpstrFile));
    }
    else
    {
        // All this stuff below is to tell you exactly how you messed up above. 
        // Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
        switch (CommDlgExtendedError())
        {
        case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
        case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
        case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
        case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
        case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
        case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
        case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
        case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
        case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
        case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
        case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
        case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
        case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
        case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
        case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
        default: std::cout << "You cancelled.\n";
        }
    }
}

void MosaicTool::buttonPressed(GUIElement* button, int status)
{
    //std::cout << button << "\n";
    //std::cout << selectButton << "\n";

    if (status != ButtonElement::ButtonState::DOWN)
    {
        return;
    }

    if (button == selectButton) 
    {
        //openFileDialog(;
    }
}
