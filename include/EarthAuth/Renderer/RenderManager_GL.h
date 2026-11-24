//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_RENDERMANAGER_GL_H
#define BSDCOUNTER_TXT_RENDERMANAGER_GL_H


#include "EarthAuth/Renderer/RenderManager_Base.h"

namespace EarthAuth {

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

        /*Initialise GL specific renderer functionality*/
        virtual auto InitialiseRenderer() -> bool override;

        /*GL Specific Override of renderer update*/
        virtual auto UpdateRenderer() -> bool override;

    private:

        /*Shader Storage Buffer Object*/
        unsigned int m_SSBO;
        //TODO Further research itno SSBOs
        /*Vertex Attribute Object*/
        unsigned int m_VAO;

        /*Shader manager for our renderer. Handles initialisation, compilation and other shader related gubbins*/
        std::unique_ptr<ShaderManager_GL> m_ShaderManager;

    };
}
#endif //BSDCOUNTER_TXT_RENDERMANAGER_GL_H
