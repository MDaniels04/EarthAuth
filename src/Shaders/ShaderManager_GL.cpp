#include "EarthAuth/Shaders/ShaderManager_GL.h"


namespace LabRat
{

    ShaderManager_GL::ShaderManager_GL() :  m_ProgramNum(-1), m_ShaderNumMap({})
    {

    }

    ShaderManager_GL::~ShaderManager_GL()
    {

    }

    auto ShaderManager_GL::InitShader(const char* ShaderFilepath, GLenum Type) -> bool
    {
        //return true;
        const unsigned int Shader = glCreateShader(Type);

        //Read the code from the given filepath
        const std::string ShaderCode = ReadShaderFromFilepath(ShaderFilepath);

        //If shadercode doesnt overwrite its default, or is empty, this is an easy catch to return false on
        if (ShaderCode == "NULL" || ShaderCode == "")
            return false;

        m_ShaderNumMap.insert({Type, CompileShader(ShaderCode.c_str(), Type)});

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

    auto  ShaderManager_GL::ReadShaderFromFilepath(const char* ShaderFilepath) -> std::string
    {
        /*This code is as it was in Crumb - works well enough for the feasibility demo*/
        std::ifstream ShaderFile(ShaderFilepath);
        if (!ShaderFile.is_open())
        {
            Utils::Debug::PrintDebugText("Shader file not found", Utils::EDMT_Error);
            return "NULL";
        }

        std::stringstream FileBuffer;
        FileBuffer << ShaderFile.rdbuf();
        return FileBuffer.str(); //TODO ew
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



        return Out;
    }

    auto ShaderManager_GL::PrintShaderCompileStatus(int ShaderNum) -> int
    {
        /*As seen in prev engine work*/

        int Out;
        char Log[512];

        glGetShaderiv(ShaderNum, GL_COMPILE_STATUS, &Out);

        glGetShaderInfoLog(ShaderNum, 512, nullptr, Log);

        //Utils::Debug::PrintDebugText(Log, Utils::EDMT_Error);

        return Out;
    }

    auto ShaderManager_GL::SetShaderParams(glm::mat4 MatWorld, glm::mat4 MatView, glm::mat4 MatProj) -> void
    {
        //TODO can we assume these won't move and we can just do the getting locations once?
        //As mentioned, this is based off Crumb untill we atleast get off of the ground, so we will just follow it to a probably
        //unoptimised T untill we have a point to build off of and a way to actually debug the graphics
        GLint MatWorldLoc = glGetUniformLocation(m_ProgramNum, "MatWorld");
        GLint MatViewLoc = glGetUniformLocation(m_ProgramNum, "MatView");
        GLint MatProjLoc = glGetUniformLocation(m_ProgramNum, "MatProj");

        glUniformMatrix4fv(MatWorldLoc, 1, GL_FALSE, &MatWorld[0][0]);
        glUniformMatrix4fv(MatViewLoc, 1, GL_FALSE, &MatView[0][0]);
        glUniformMatrix4fv(MatProjLoc, 1, GL_FALSE, &MatProj[0][0]);
    }

}