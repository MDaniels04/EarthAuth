#include "EarthAuth/Renderer/RenderManager_GL.h"

///Includes for GL specific functionality
#include "glad/gl.h"
#include "EarthAuth/Shaders/ShaderManager_GL.h"

namespace LabRat
{

    RenderManager_GL::RenderManager_GL() : m_ShaderManager(nullptr)
    {
    }



    auto RenderManager_GL::InitialiseRenderer() -> bool
    {
        /*Create our buffers*/
        glCreateBuffers(1, &m_SSBO);
        glCreateBuffers(1, &m_VAO);

        //Create our shader manager - it will be of type shader manager gl.
        m_ShaderManager = std::unique_ptr<ShaderManager_GL>();

        m_ShaderManager->InitShader("GLSL/BlockVSH.vert", GL_VERTEX_SHADER);
        m_ShaderManager->InitShader("GLSL/BlockFSH.frag", GL_FRAGMENT_SHADER);


        m_ShaderManager->LinkShaderProgram();
        //glUseProgram(ShaderProgram);

    }

    auto RenderManager_GL::UpdateRenderer() -> bool
    {

    }
}