//
// Created by Morga on 24/11/2026.
//

#include "EarthAuth.h"


using namespace LabRat;

EarthAuth::EarthAuth(ERenderingLibrary GivenLib) : Application::Application(GivenLib)
{
    m_TerrainManager = std::make_unique<TerrainManager>();

    Utils::Debug::PrintDebugText("Our app being built correctly", Utils::EDebugMessageType::EDMT_Info);
}