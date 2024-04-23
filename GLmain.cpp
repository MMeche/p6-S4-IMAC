#include <cstddef>
#include <memory>
#include "glimac/common.hpp"
#include "glimac/cone_vertices.hpp"
#include "glimac/sphere_vertices.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/matrix.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"
#include"glm/gtc/type_ptr.hpp"

#include "glm/gtc/random.hpp"
#include "GLclass.hpp"

int main()
{
    auto ctx = p6::Context{{1280, 720, "TP6"}};
    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normal.fs.glsl"
    );

    //ctx.maximize_window();
    shader.use();

    // Création d'un Vertex Buffer Object et d'un Vertex Array Object
    VBO vboCones{};
    VAO vaoCones{};

    VBO vboAquarium{};
    VAO vaoAquarium{};
    

    // "vbo" devient le VBO courant sur la cible GL_ARRAY_BUFFER:
    vboCones.bind();

    // Tableau des attributs des sommets
    const std::vector<glimac::ShapeVertex> vertices = glimac::cone_vertices(1., 0.5, 32, 16);
    
    // Stockage des données du tableau vertices dans le vbo placé sur GL_ARRAY_BUFFER (c'est à dire "vbo" ici) :
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    // Plus de VBO sur la cible GL_ARRAY_BUFFER:
    vboCones.unbind();
    // "vao" devient le VAO courant:
    vaoCones.bind();


    static constexpr GLuint vertex_attr_position = 0;
    static constexpr GLuint vertex_attr_normal   = 1;
    static constexpr GLuint vertex_attr_tex      = 2;
    
    // Activation de l'attribut de vertex 0; nous l'interpretons comme la position
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    
    vboCones.bind();   
    
    // On spécifie le type de donnée de l'attribut position ainsi que la manière dont il est stocké dans le VBO
    glVertexAttribPointer(
        vertex_attr_position /* Indice attribut */,
        3 /* Nombre de composantes */,
        GL_FLOAT /* Type d'une composante */,
        GL_FALSE /* Pas de normalisation */,
        sizeof(glimac::ShapeVertex) /* Taille en octet d'un vertex complet entre chaque attribut position */,
        (const GLvoid*)offsetof(glimac::ShapeVertex, position)/* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
    );
    
    glVertexAttribPointer(
        vertex_attr_normal /* Indice attribut */,
        3 /* Nombre de composantes */,
        GL_FLOAT /* Type d'une composante */,
        GL_FALSE /* Pas de normalisation */,
        sizeof(glimac::ShapeVertex) /* Taille en octet d'un vertex complet entre chaque attribut position */,
        (const GLvoid*)offsetof(glimac::ShapeVertex, normal) /* OpenGL doit utiliser le VBO attaché à GL_ARRAY_BUFFER et commencer à l'offset 0 */
    );    
    glVertexAttribPointer(
        vertex_attr_tex,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glimac::ShapeVertex),
        (const GLvoid*)offsetof(glimac::ShapeVertex, texCoords)
    );
    
    vboCones.unbind();
    vaoCones.unbind();

    //Uniform Variables
    GLuint uMVPMatrix    = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uMVPMatrix"));
    GLuint uMVMatrix     = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uMVMatrix"));
    GLuint uNormalMatrix = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uNormalMatrix"));
    GLuint uTexture      = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uTexture"));
    
    glEnable(GL_DEPTH_TEST);

    std::vector<glm::vec3> moonTransforms;
    for(int i = 0 ; i<32 ; i++)
    {
        moonTransforms.push_back(glm::sphericalRand(3.f));
    }    
        

    // Declare your infinite update loop.
    ctx.update = [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // "vao" devient le VAO courant, OpenGL l'utilisera lors du dessin pour avoir des informations sur les sommets
        vaoCones.bind();

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f},glm::vec3(0,0,-5.f));
        MVMatrix = glm::rotate(MVMatrix,-2*ctx.time(),{0.f,1.f,0.f});
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glm::mat4 MVPMatrix    = ProjMatrix * MVMatrix;
        
        glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        
        glDrawArrays(GL_TRIANGLES, 0 /* Pas d'offset au début du VBO */, vertices.size());
        
        
        MVMatrix = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -5.f}); // Translation
        MVMatrix = glm::rotate(MVMatrix, ctx.time(), {0.f, 1.f, 0.f}); // Translation * Rotation
        
        for(glm::vec3 &moon : moonTransforms)
        {
            MVMatrix = glm::translate(MVMatrix, moon); // Translation * Rotation * Translation
            MVMatrix = glm::scale(MVMatrix, glm::vec3{.2f}); // Translation * Rotation * Translation * Scale
            
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVPMatrix = ProjMatrix * MVMatrix;
            
            glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
            glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
            
            glDrawArrays(GL_TRIANGLES, 0 /* Pas d'offset au début du VBO */, vertices.size());

            MVMatrix = glm::scale(MVMatrix,glm::vec3{5.f});
            MVMatrix = glm::translate(MVMatrix,-moon);
        }
        // Plus de VAO courant:
        vaoCones.unbind();
        glBindTexture(GL_TEXTURE_2D,0);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}