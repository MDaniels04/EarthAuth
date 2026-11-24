#ifndef EARTHAUTH_SHADERMANGER_BASE_H
#define EARTHAUTH_SHADERMANGER_BASE_H

#pragma once

namespace LabRat {
    /*Shader Managers are our classes responsible for loading and communicating with shaders*/
    class ShaderManager_Base
    {
    public:

        /*Default const and destr*/
        ShaderManager_Base();
        ~ShaderManager_Base();

    protected:

        /*Class specific management of compiling our shaders*/
        virtual auto CompileShader() -> int = 0;
    };
}
#endif
