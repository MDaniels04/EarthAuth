#include "EarthAuth/Renderer/RendererManager_GL.h"


auto RenderManager_GL::InitialiseRenderer() -> bool
{
    glCreateBuffers(1, &SSBO);
    glCreateBuffers(1, &VAO)

}

auto RenderManager_GL::UpdateRenderer() -> bool
{

}
