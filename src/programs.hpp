#pragma once
#include "p6/p6.h"

struct AquariumProgram{
    p6::Shader m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture1;
    GLint uTexture2;
    

    AquariumProgram()
        :m_program{p6::load_shader("shaders/aquarium.vs.glsl","shaders/multitex3D.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_program.id(),"uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_program.id(),"uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.id(),"uNormalMatrix");
        uTexture1      = glGetUniformLocation(m_program.id(),"uTexture1");
        uTexture2      = glGetUniformLocation(m_program.id(),"uTexture2");


    }
};

struct FishProgram{
    p6::Shader m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uColor;

    FishProgram()
        :m_program{p6::load_shader("shaders/3D.vs.glsl","shaders/normal.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_program.id(),"uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_program.id(),"uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.id(),"uNormalMatrix");
        uColor        = glGetUniformLocation(m_program.id(),"uColor");

    }
};

struct StarProgram{
    p6::Shader m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uColor;

    StarProgram()
        :m_program{p6::load_shader("shaders/3D.vs.glsl","shaders/normal.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_program.id(),"uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_program.id(),"uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.id(),"uNormalMatrix");
        uColor        = glGetUniformLocation(m_program.id(),"uColor");

    }
};