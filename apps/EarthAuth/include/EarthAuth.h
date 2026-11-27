//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_EARTHAUTH_H
#define BSDCOUNTER_TXT_EARTHAUTH_H

#include "EarthAuth/Application/Application.h"

#include "EarthAuth/Terrain/TerrainManager.h"

#pragma once

using namespace LabRat;



/*Our extenstion of application for the tool - define the states we want to go between, and the actual functionality of each*/
class EarthAuth : public Application
{
public:

    /*Default constructor*/
    EarthAuth();


    EarthAuth(ERenderingLibrary GivenLib = ERenderingLibrary::ERL_OpenGL);


    std::unique_ptr<TerrainManager> m_TerrainManager;
};



#endif //BSDCOUNTER_TXT_EARTHAUTH_H
