#pragma once
#include "p6/p6.h"

struct AquariumProgram{
    p6::Shader m_program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture1;
    GLint uTexture2;
    // GLint uTexture3;
    // GLint uTexture4;

    AquariumProgram()
        :m_program{p6::load_shader("shaders/aquarium.vs.glsl","shaders/multitex3D.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_program.id(),"uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_program.id(),"uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_program.id(),"uNormalMatrix");
        uTexture1      = glGetUniformLocation(m_program.id(),"uTexture1");
        uTexture2      = glGetUniformLocation(m_program.id(),"uTexture2");
        // uTexture3      = glGetUniformLocation(m_program.id(),"uTexture3");
        // uTexture4      = glGetUniformLocation(m_program.id(),"uTexture4");

    }
};

//Other structs of programs to be added (the fishes? / platforms.)