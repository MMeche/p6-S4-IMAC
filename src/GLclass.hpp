#pragma once
#include "img/src/Image.h"
#include "p6/p6.h"
#include <imgui.h>

class VBO
{
    public:
    VBO()
    {
        glGenBuffers(1,&_id);
    }
    ~VBO()
    {
        glDeleteBuffers(1,&_id);
    }
    
    //interdit la copie !!
    VBO(const VBO& other) = delete;
    VBO& operator= (const VBO& other) = delete;
    
    VBO(VBO&& other) noexcept : _id{other._id} //move constructor.
    {
        other._id = 0; //Make sure 
    }
    VBO& operator=(VBO&& other) noexcept //move assignement.
    {
        if(this!= &other)
        {
            glDeleteBuffers(1,&_id);
            _id = other._id;
            other._id = 0;
        }
        return *this;
    }

    void bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }
    void unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    private : 
    GLuint _id{};
};



class VAO
{
    public:
    VAO()
    {
        glGenVertexArrays(1,&_id);
    }
    ~VAO()
    {
        glDeleteBuffers(1,&_id);
    }
    
    //interdit la copie !!
    VAO(const VBO& other) = delete;
    VAO& operator= (const VBO& other) = delete;
    
    VAO(VAO&& other) noexcept : _id{other._id} //move constructor.
    {
        other._id = 0; //Make sure 
    }
    VAO& operator=(VAO&& other) noexcept //move assignement.
    {
        if(this!= &other)
        {
            glDeleteBuffers(1,&_id);
            _id = other._id;
            other._id = 0;
        }
        return *this;
    }

    void bind() const
    {
        glBindVertexArray(_id);
    }
    void unbind() const
    {
        glBindVertexArray(0);
    }

    private : 
    GLuint _id{};
};

class TextureID
{
    public:
    TextureID()
    {
        glGenTextures(1,&_id);
    }
    ~TextureID()
    {
        glDeleteTextures(1,&_id);
    }
    
    //interdit la copie !!
    TextureID(const TextureID& other) = delete;
    TextureID& operator= (const TextureID& other) = delete;
    
    TextureID(TextureID&& other) noexcept : _id{other._id} //move constructor.
    {
        other._id = 0; //Make sure 
    }
    TextureID& operator=(TextureID&& other) noexcept //move assignement.
    {
        if(this!= &other)
        {
            glDeleteBuffers(1,&_id);
            _id = other._id;
            other._id = 0;
        }
        return *this;
    }

    void bind() const
    {
        glBindTexture(GL_TEXTURE_2D,_id);
    }
    void unbind() const
    {
        glBindTexture(GL_TEXTURE_2D,0);
    }

    private : 
    GLuint _id{};
};

struct Vertex3D {
    glm::vec3 position;
};


