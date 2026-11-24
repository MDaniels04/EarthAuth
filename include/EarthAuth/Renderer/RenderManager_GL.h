//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_RENDERMANAGER_GL_H
#define BSDCOUNTER_TXT_RENDERMANAGER_GL_H


#include "EarthAuth/Renderer/RenderManager_Base.h"

/*
 * OpenGL implementation of our render manager. In this current implementation, is quite barebones (i.e.: just draws some voxels).
 * Iterations later can be made to optimise for our SVO / DAG (Im not typing the full acronym for the transform aware layout)
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
    unsigned int SSBO;

    /*Vetex Attribute Object*/
    unsigned int VAO;

};

#endif //BSDCOUNTER_TXT_RENDERMANAGER_GL_H
