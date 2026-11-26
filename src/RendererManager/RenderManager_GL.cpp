#include "EarthAuth/Renderer/RenderManager_GL.h"

///Includes for GL specific functionality
#include "glad/gl.h"
#include <glfw/glfw3.h>
#include "EarthAuth/Shaders/ShaderManager_GL.h"

#include "EarthAuth/WindowManager/WindowManager_GLFW.h"

#include "EarthAuth/Voxel/Voxel.h"

namespace LabRat
{

    RenderManager_GL::RenderManager_GL() : RenderManager_Base::RenderManager_Base(), m_ShaderManager(nullptr)
    {

    }


    RenderManager_GL::~RenderManager_GL()
    {

    }

    auto RenderManager_GL::InitialiseRenderer() -> bool
    {


        const int GladVersion = gladLoadGL(glfwGetProcAddress);
        if (GladVersion == 0)
        {
            Utils::Debug::PrintDebugText("Error: GLAD initialised incorrectly", Utils::EDMT_Error);
            return false;
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        //Create and bind our Vertex Attribute Object
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        //Enable our VAO
        glEnableVertexAttribArray(m_VAO);


        //Create our shader manager - it will be of type shader manager gl.

        m_ShaderManager = std::unique_ptr<ShaderManager_GL>(new ShaderManager_GL());

        if (!m_ShaderManager)
        {
            Utils::Debug::PrintDebugText("Shader manager not created", Utils::EDebugMessageType::EDMT_Error);
            return false;
        }

        //Initialise the shaders
        m_ShaderManager->InitShader("resources/shaders/GLSL/BlockVSH.vert", GL_VERTEX_SHADER);
        m_ShaderManager->InitShader("resources/shaders/GLSL/BlockFSH.frag", GL_FRAGMENT_SHADER);

        m_ShaderManager->LinkShaderProgram();

        //TEMP HERE
        constexpr static GLfloat Tri[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
         };

        //Generate our vbo and bind to it
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        //We will only be generating cubes, so the buffer data is always gonna be this (FOR NOW ATLEAST)
        glBufferData(GL_ARRAY_BUFFER, sizeof(Tri), Tri, GL_STATIC_DRAW);

        //Fill the VBO buffer data here with the HelloTriangle - TODO Later we want to have this be managed by some kind of voxel tracker....

        return true;
    }

    auto RenderManager_GL::UpdateRenderer(const float DeltaTime) -> bool
    {
        //Clear the old window stuff...
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Use our shader programs - for the now, that is just gonna be this program
        glUseProgram(m_ShaderManager->GetProgramNum());


        //FOR ALL OUR CUBES WE NEED TO RENDER:
        //SET THESE SHADER PARAMS


        //Pass our shaders their info

        /*ALL OF THE MESHES WE NEED TO RENDER WILL GO IN HERE, BUT FOR NOW JUST A CUBE*/
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        CalculateRenderMatricies();
        m_ShaderManager->SetShaderParams(m_MatWorld, m_MatView, m_MatProjection);;

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        // Draw the

        // glBindVertexArray(m_VAO);
        // glDrawElements(GL_TRIANGLES,
        //                 6,
        //                 );
        //
        // //Cannot remember what this does, but was used in Crumb
        // glBindVertexArray(0);
        //glVertexAttribPointer(m_VAO, );

        return true;
    }

    void RenderManager_GL::CalculateRenderMatricies()
    {

        //TEMP IDENTITY MATRIX FOR WORLD
        m_MatWorld = glm::mat4(1.0);

        m_MatView = glm::lookAt(
                    WindowManager_GLFW::GetViewPosition(),
                    WindowManager_GLFW::GetViewDirection() + WindowManager_GLFW::GetViewPosition(),
                    WindowManager_GLFW::GetViewUp()
            );

                            //TEMPORARILY hard coded projection matrix
        m_MatProjection = glm::perspective(glm::radians(45.f), 4.f/3.f, 0.1f, 100.f);
    }
}