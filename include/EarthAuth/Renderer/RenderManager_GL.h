//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_RENDERMANAGER_GL_H
#define BSDCOUNTER_TXT_RENDERMANAGER_GL_H


#include "EarthAuth/Renderer/RenderManager_Base.h"

#include <glm/glm.hpp>

namespace LabRat {

    /*Forward decl of shader manager class*/
    class ShaderManager_GL;

    /*
     * OpenGL implementation of our render manager. In this current implementation, is quite barebones (i.e.: just draws some voxels).
     * Iterations later can be made to optimise for our SVO / DAG (Im not typing the full acronym for the transform aware layout)
     *
     * The renderer and shader manager in current states are extensions of the game engine work I did previously, TODO make better...
     */
    class RenderManager_GL : public RenderManager_Base
    {

    public:

        RenderManager_GL();

        ~RenderManager_GL();

        /*Initialise GL specific renderer functionality*/
        virtual auto InitialiseRenderer() -> bool override;

        /*GL Specific Override of renderer update*/
        virtual auto UpdateRenderer(const float DeltaTime) -> bool override;

    private:

        /*Shader Storage Buffer Object*/
        // unsigned int m_SSBO;
        // //TODO Further research itno SSBOs
        // /*Vertex Attribute Object*/
        // unsigned int m_VAO;

        /*Shader manager for our renderer. Handles initialisation, compilation and other shader related gubbins*/
        std::unique_ptr<ShaderManager_GL> m_ShaderManager;

        /*VERTEX BUFFER OBJECT - TEMP TEMP TEMP - WE JUST WANT A CUBE MAN*/
        unsigned int m_VBO;

        /*VERTEX ATTRIBUTE OBJECT*/
        unsigned int m_VAO;


        /*Calcualte our matricies that are passed into the shaders...*/
        void CalculateRenderMatricies();


        glm::mat4 m_MatWorld;
        glm::mat4 m_MatView;
        glm::mat4 m_MatProjection;


        /*Everything we render will be cubes - so we can just define the verticies here and reuse!*/

        const float CubeVertData[108] = {
            -1.0f,-1.0f,-1.0f, // tri 1 begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,  // tri 1 end
            1.0f, 1.0f,-1.0f,   // tri 2 begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,  // tri 2 end
            1.0f,-1.0f, 1.0f,   //tri 3 begin
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,   //tri 3 end
            1.0f, 1.0f,-1.0f,   //tri4 begin
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,  //tri 4 end
            -1.0f,-1.0f,-1.0f,  //tri 5 begin
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,  //tri 5 end
            1.0f,-1.0f, 1.0f,   //tri 6 begin
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,  //tri 6 end
            -1.0f, 1.0f, 1.0f,  //tri 7 begin
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,   //tri 7 end
            1.0f, 1.0f, 1.0f,   //tri 8 begin
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,   //tri 8 end
            1.0f,-1.0f,-1.0f,   //tri 9 begin
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,   //tri 9 end
            1.0f, 1.0f, 1.0f,   //tri 10 begin
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,  //tri 10 end
            1.0f, 1.0f, 1.0f,   //tri 11 begin
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,  //tri 11 end
            1.0f, 1.0f, 1.0f,   //tri 12 begin
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f    //tri 12 end
        };
    };
}
#endif //BSDCOUNTER_TXT_RENDERMANAGER_GL_H
