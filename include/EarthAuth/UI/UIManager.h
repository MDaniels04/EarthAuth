//
// Created by Morga on 26/11/2026.
//

#ifndef EARTHAUTH_UIMANAGER_H
#define EARTHAUTH_UIMANAGER_H

class GLFWwindow;

namespace LabRat {
    /*OUR UI Manager is essentially an interface with ImGUI, and handles the update, initialisation and reading of values from ImGUI
     * Eventually this should be ported into a base class to make it library agnostic, but we are up against the clock here and this will suffice for now
     */
    class UIManager
    {
    public:


        /*Default constructor*/
        UIManager();

        /*Default destructor*/
        ~UIManager();


        /*initialise our ImGUI library  - TEMP parameter of the windo wptr, will redo when I have time*/
        auto InitUI(GLFWwindow* GivenWindow) -> const bool;

        /*Update our IMGUI window*/
        auto UpdateUI() -> void;

        /*Get rid of our UI, do the necessary ImGUI end lifetime funcs*/
        auto ShutdownUI() -> void;

    };
}

#endif //EARTHAUTH_UIMANAGER_H
