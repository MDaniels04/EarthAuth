#include "EarthAuth/WindowManager/WindowManager_Base.h"

namespace EarthAuth
{
    WindowManager_Base::WindowManager_Base() : m_MainWindowWidth(0), m_MainWindowHeight(0), m_MainWindowTitle("Window")
    {


    }

    WindowManager_Base::WindowManager_Base(const unsigned int MainWindowWidth, const unsigned int MainWindowHeight, const char* MainWindowTitle)
    : m_MainWindowWidth(MainWindowWidth), m_MainWindowHeight(MainWindowHeight), m_MainWindowTitle(MainWindowTitle)
    { }

    WindowManager_Base::~WindowManager_Base()
    { }
}