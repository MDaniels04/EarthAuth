//
// Created by Morga on 24/11/2026.
//

#ifndef BSDCOUNTER_TXT_SHADERMANAGER_GL_H
#define BSDCOUNTER_TXT_SHADERMANAGER_GL_H

#pragma once

#include <pch.h>
#include "ShaderManager_Base.h"

#include <glad/gl.h> //We cannot forward reference enum types, so this has been included here...

namespace EarthAuth {

    /*GLSL specific implementation of our shader manager*/
    class ShaderManager_GL : public ShaderManager_Base
    {
    public:

        /*Default Constructor*/
        ShaderManager_GL();

        /*Default Destructor*/
        ~ShaderManager_GL();


        /*
         *Initialise a shader, attach it to gl then detach once its been compiled.
         *Extension of Crumb work as it can now be used for more than just Vert and Frag shaders
         *
         */
        auto InitShader(const char* ShaderFile, GLenum ShaderType) -> bool;

        /*Link shaders we have initialised to the program and set it running...*/
        auto LinkShaderProgram() -> bool;

    private:

        /*Overload of compile shader for GL specific code*/
        auto CompileShader(const char* ShaderFilepath, GLenum Type) -> int;

        /*Debug function for outputting the compile status of shaders to the console*/
        auto PrintShaderCompileStatus(int ShaderNum) -> int;

        /*Debug function for outputting the compile status of the whole shader program*/
        auto PrintProgramCompileStatus() -> int;


        /*Read the contents of a shader from an input file path*/
        auto  ReadShaderFromFilepath(const char* ShaderFilepath) -> const char*;


        /**
         * VARIABLES
         */


        /*Map pairing the shader number with the type of shader (e.g.: GL_VERTEX_SHADER - 1) - for ref use
         * First - GLenum - the type of shader this is
         * Second - int - number ref of this shader for OpenGL
         */
        std::unordered_map<GLenum, int> m_ShaderNumMap;

        /*Integer storing the number referencing the shader program*/
        int m_ProgramNum;

    };
}

#endif
