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
        //virtual auto CompileShader() -> int = 0;
        //TODO child variations will all require diff parameters, this does not have an implementation in its base for...

    };
}
#endif
