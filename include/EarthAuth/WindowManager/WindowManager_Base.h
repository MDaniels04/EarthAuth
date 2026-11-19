#ifndef EARTHAUTH_WINDOWMANAGER_BASE_H
#define EARTHAUTH_WINDOWMANAGER_BASE_H

#include <pch.h>



namespace EarthAuth
{
    /*
     * Abstract class which specific library implementations will derrive from, allowing us to not be hard wired to one lib, and can make later implementations
     * down the line
     */
    class WindowManager_Base
    {
    public:

        /*Default constructor*/
        WindowManager_Base();

        /*Constructor*/
        WindowManager_Base(const unsigned int MainWindowWidth, const unsigned int MainWindowHeight, const char* MainWindowTitle);

        /*Default destructor*/
        ~WindowManager_Base();

        /*
         * //////////
         * FUNCTIONS
         * //////////
         */


        /*
         *Abstract declaration of the function that will set up and open the main window in lib specific implementations.
         *Returns TRUE / FALSE on success of window initialisation
         */
        virtual auto InitialiseMainWindow() -> const bool = 0;


        /*
         *Abstract declaration of the function that will handle each frame update of the main window in lib specific implementations
         *Returns an uint describing the success or errors that came up during the update
         *(i.e.: 0 -> updated, 1... -> update problem, number describing)
         */
        virtual auto UpdateMainWindow() -> const unsigned int = 0;

    protected:


        /*
         * //////////
         * VARIABLES
         * //////////
         */

        /*Window width and height variables*/
        unsigned int m_MainWindowWidth;
        unsigned int m_MainWindowHeight;

        /*Title of the window*/
        std::string m_MainWindowTitle;

    public:

        /*GETTERS AND SETTERS*/

        /*Window width*/
        inline auto GetWindowWidth() const -> unsigned int { return m_MainWindowWidth; }


        /*Window height*/
        inline auto GetWindowHeight() const -> unsigned int { return m_MainWindowHeight; }
    };
}
#endif //EARTHAUTH_WINDOWMANAGER_BASE_H
