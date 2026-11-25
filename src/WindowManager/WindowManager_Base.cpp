#include "EarthAuth/WindowManager/WindowManager_Base.h"

namespace LabRat
{
    WindowManager_Base::WindowManager_Base() : m_MainWindowWidth(480), m_MainWindowHeight(480), m_MainWindowTitle("Window"), m_bShouldWindowUpdate(true)
    {


    }

    WindowManager_Base::WindowManager_Base(const unsigned int MainWindowWidth, const unsigned int MainWindowHeight, const char* MainWindowTitle)
    : m_MainWindowWidth(MainWindowWidth), m_MainWindowHeight(MainWindowHeight), m_MainWindowTitle(MainWindowTitle)
    { }

    WindowManager_Base::~WindowManager_Base()
    { }
}