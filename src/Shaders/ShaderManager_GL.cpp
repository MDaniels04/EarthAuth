#include "EarthAuth/Shaders/ShaderManager_GL.h"


namespace LabRat
{

    ShaderManager_GL::ShaderManager_GL()
    {
        m_ProgramNum = -1;
    }

    ShaderManager_GL::~ShaderManager_GL()
    {

    }

    auto ShaderManager_GL::InitShader(const char* ShaderFilepath, GLenum Type) -> bool
    {

        const unsigned int Shader = glCreateShader(Type);

        //Read the code from the given filepath
        const char* ShaderCode = ReadShaderFromFilepath(ShaderFilepath);

        if (ShaderCode == "NULL")
            return false;

        /*Compile our shader and add the num reference to our map of shader maps */
        m_ShaderNumMap[Type] = CompileShader(ShaderCode, Type);

        return true;
    }


    auto ShaderManager_GL::LinkShaderProgram() -> bool
    {
        m_ProgramNum = glCreateProgram();

        /*For our shaders, we want to attach them and get them up and running!*/
        for (const auto i : m_ShaderNumMap)
        {
            glAttachShader(m_ProgramNum, i.second);
        }

        glLinkProgram(m_ProgramNum);


        if (!PrintProgramCompileStatus())
            return false;
        //IF we get to here all must be well, so now its time to use the program created
        glUseProgram(m_ProgramNum);


        //We can now delete shader objects, as they are no longer needed once linked.
        for (const auto i : m_ShaderNumMap)
        {
            glDeleteShader(i.second);
            m_ShaderNumMap.erase(i.second); //Remove from map too as this number ref will no longer be vaild.
        }

        return true;
    }

    auto  ShaderManager_GL::ReadShaderFromFilepath(const char* ShaderFilepath) -> const char*
    {
        /*This code is as it was in Crumb - works well enough for the feasibility demo*/
        std::ifstream ShaderFile(ShaderFilepath);
        if (!ShaderFile.is_open())
        {
            std::cout << "ERROR SHADER FILE NOT FOUND: " << ShaderFilepath << "\n";
            return "NULL";
        }

        std::stringstream FileBuffer;
        FileBuffer << ShaderFile.rdbuf();
        return FileBuffer.str().c_str(); //TODO ew
    }

    auto ShaderManager_GL::CompileShader(const char* ShaderCode, GLenum Type) -> int
    {
        const int ShaderNum = glCreateShader(Type);
        glShaderSource(ShaderNum, 1, &ShaderCode, nullptr);

        glCompileShader(ShaderNum);

        PrintShaderCompileStatus(ShaderNum);

        return ShaderNum;
    }

    auto ShaderManager_GL::PrintProgramCompileStatus() -> int
    {
        int Out;
        char Log[512];

        glGetProgramiv(m_ProgramNum, GL_LINK_STATUS, &Out);

        if (Out)
            return Out;

        glGetProgramInfoLog(m_ProgramNum, 512, nullptr, Log);

        Utils::Debug::PrintDebugText(Log, Utils::EDMT_Error);

        return Out;
    }

    auto ShaderManager_GL::PrintShaderCompileStatus(int ShaderNum) -> int
    {
        /*As seen in prev engine work*/

        int Out;
        char Log[512];

        glGetShaderiv(ShaderNum, GL_COMPILE_STATUS, &Out);

        if (Out)
            return Out;

        glGetShaderInfoLog(ShaderNum, 512, nullptr, Log);

        Utils::Debug::PrintDebugText(Log, Utils::EDMT_Error);

        return Out;
    }
}