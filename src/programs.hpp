#pragma once
#include "p6/p6.h"

struct AquariumProgram{
    p6::Shader m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    AquariumProgram()
        :m_program{p6::load_shader("3D.vs.glsl","shaders/normal.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_program.id(),"uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_program.id(),"uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.id(),"uNormalMatrix");
    }
};

//Other structs of programs to be added (the fishes? / platforms.)