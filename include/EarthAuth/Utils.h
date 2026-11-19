//
// Created by Morga on 18/11/2026.
//

#ifndef EARTHAUTH_UTILS_H
#define EARTHAUTH_UTILS_H

#pragma once

#include <string>
#include <cstdio>

namespace EarthAuth
{

    /*Utils namespace including a number of helper functions and classes, including our own little debug library*/
    namespace Utils
    {
        /*Enum representing colours to the application*/
        enum EColour : unsigned char
        {
            EC_Red = 1,
            EC_Green = 2,
            EC_Yellow = 3,
            EC_Blue = 4,
            EC_Magenta = 5,
            EC_Cyan = 6,
            EC_White = 0
        };

        /*Enum representing the verbosity of a debug console message*/
        enum EDebugMessageType : unsigned char
        {
            EDMT_Normal = 0,
            EDMT_Warning = 1,
            EDMT_Error = 2,
            EDMT_Info = 3
        };
        /*^^^ Custom functionality may later extend to do something specific with each of these verbosities*/

        /*Class of static functions for debugging purposes*/
        class Debug
        {
            /*
             *IMPORTANT NOTE - IF UR IDE CONSOLE DOESN'T SUPPOURT ANSI COLOUR  CODES THIS WILL JUST HAVE ANSI CODES AT THE FRONT
             *TODO a way to tell if we are using a console / can suppourt ANSI output?
             */

        public:

            /*Print a coloured message to the terminal - if no colour is specified, we will go with the colour syonymous with that verbosity, as follows:
             * -> Normal - white
             * -> Warning - yellow
             * -> Error - red
             * -> Info - Magenta
             */
            static void PrintDebugText(const std::string& OutText, const EDebugMessageType OutVerbosity = EDebugMessageType::EDMT_Normal)
            {
                std::string VStr = "";

                switch (OutVerbosity)
                {
                    case EDebugMessageType::EDMT_Error:
                        VStr = "ERROR: ";
                        break;
                    case EDebugMessageType::EDMT_Warning:
                        VStr = "WARNING: ";
                        break;
                    case EDebugMessageType::EDMT_Info:
                        VStr = "INFO: ";
                        break;
                }

                //TODO ANSI COLOUR CODE IMPLS - FOR NOW THIS IS A SOLOUTION THAT SOLELY SUPPOURTS COLORED OUTPUT IN THE GREP CONSOLE
                const std::string Appended = VStr + OutText + "\n";
                printf(Appended.c_str());
            }


        };
    }

}




#endif //EARTHAUTH_UTILS_H
