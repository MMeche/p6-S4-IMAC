#include <cstdlib>
#include <vector>
#include "FreeflyCamera.hpp"
#include "GLFW/glfw3.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "shape_vertices.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "walker.hpp"
#include "p6/p6.h"
#include "UI.hpp"
#include "flock.hpp"
#include <cstddef>
#include <memory>
#include "common.hpp"
#include "shape_vertices.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/matrix.hpp"
#include "img/src/Image.h"
#include "p6/p6.h"
#include"glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"
#include "GLclass.hpp"
#include "programs.hpp"

int main()
{
    auto ctx = p6::Context{{.title = "Old Boids"}};
    
    
    Flock boids = Flock(30);
    Wall aquarium = Wall(glm::vec3(0,0,0),2*Wall::UI_AQUARIUMSIZE);
    std::vector<Wall> obstacles;
    Walker catWalker;
    obstacles.push_back(aquarium);
    //obstacles.push_back(catWalker);
    
    img::Image cloud = p6::load_image_buffer("assets/clouds.jpg");

    img::Image souslocean1 = p6::load_image_buffer("assets/aquarium_1.png");
    img::Image souslocean2 = p6::load_image_buffer("assets/aquarium_2.png");

    
    
    

    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normal.fs.glsl"
    );
    AquariumProgram AquariumPrgm{};
    ctx.maximize_window();
    
    
    //Partie OpenGL
    

    // Création d'un Vertex Buffer Object et d'un Vertex Array Object
    VBO vboCones{};
    VAO vaoCones{};

    VBO vboAquarium{};
    VAO vaoAquarium{};
     //texture bindings
        TextureID oceanTex1{};
        TextureID oceanTex2{};
        // TextureID oceanTex3{};
        // TextureID cielTex{};

        oceanTex1.bind();
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,souslocean1.width(),souslocean1.height(), 0,GL_RGBA,GL_UNSIGNED_BYTE,souslocean1.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        oceanTex1.unbind();

        oceanTex2.bind();
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,souslocean2.width(),souslocean2.height(), 0,GL_RGBA,GL_UNSIGNED_BYTE,souslocean2.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        oceanTex2.unbind();
    

    vboCones.bind();
    // Tableau des attributs des sommets pour les cônes des boids.
    const std::vector<glimac::ShapeVertex> coneVertices = glimac::cone_vertices(1., 0.5, 32, 16);
    // Stockage des données du tableau vertices dans le vbo placé sur GL_ARRAY_BUFFER (c'est à dire "vboCônes" ici) :
    glBufferData(GL_ARRAY_BUFFER, coneVertices.size()*sizeof(glimac::ShapeVertex), coneVertices.data(), GL_STATIC_DRAW);
    vboCones.unbind();

    //On va faire la même chose pour les vertices de l'aquarium
    vboAquarium.bind();
    const std::vector<glimac::ShapeVertex> aquaVertices = glimac::cube_vertices(1.);
    glBufferData(GL_ARRAY_BUFFER,aquaVertices.size()*sizeof(glimac::ShapeVertex),aquaVertices.data(),GL_STATIC_DRAW);
    vboAquarium.unbind();
    
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

    //...Et on recommence avec le vao de l'Aquarium.
    vaoAquarium.bind();
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);

    vboAquarium.bind();
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

    vboAquarium.unbind();
    vaoAquarium.unbind();

    // vaoDirections.bind();
    // glEnableVertexAttribArray(vertex_attr_position);
    // vboDirections.bind();
    // glVertexAttribPointer(
    //     vertex_attr_position,
    //     3,
    //     GL_FLOAT,
    //     GL_FALSE,
    //     sizeof(Vertex3D),
    //     (const GLvoid*)offsetof(Vertex3D,position)
    // );
    // vboDirections.unbind();
    // vaoDirections.unbind();

    //Uniform Variables
    GLuint uMVPMatrix    = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uMVPMatrix"));
    GLuint uMVMatrix     = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uMVMatrix"));
    GLuint uNormalMatrix = glGetUniformLocation(shader.id(),static_cast<const GLchar*>("uNormalMatrix"));
    
    glEnable(GL_DEPTH_TEST);
    
    glm::vec3 cameraPos = {0.,0.,0.};


    // Declare your infinite update loop.
    ctx.update = [&]() {
        // User interface controler
        UI::startUI(boids,obstacles);
        boids.update(obstacles, ctx.delta_time());
        

        if(ctx.key_is_pressed(GLFW_KEY_W)){
            catWalker.moveForward();
        }
        if(ctx.key_is_pressed(GLFW_KEY_S)){
            catWalker.moveBackward();
        }
        if(ctx.key_is_pressed(GLFW_KEY_A)){
            catWalker.moveLeft();
        }
        if(ctx.key_is_pressed(GLFW_KEY_D)){
            catWalker.moveRight();
        }
        if(ctx.mouse_button_is_pressed(p6::Button{GLFW_MOUSE_BUTTON_LEFT}) && ctx.mouse_delta()!=glm::vec2{0.,0.}){
            catWalker.turn(ctx.mouse_delta(),ctx.delta_time());
        };
        catWalker.stayInBox(aquarium.getWidth(), aquarium.getHeigth(), aquarium.getDepth());
        FreeflyCamera camera = catWalker.getCamera();



        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // DESSIN DES BOIDS
        shader.use();
        

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(100.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix     = glm::translate(glm::mat4{1.f},-cameraPos);
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glm::mat4 MVPMatrix    = ProjMatrix * MVMatrix;
        
        
        for (Boid& b : boids.getFlock())
        {
            shader.use();
            vaoCones.bind();
            glm::vec3 direction = b.getSpeed();
            
            // MVMatrix     = glm::translate(glm::mat4{1.f},glm::vec3(0,0,-5.f));
            MVMatrix = glm::mat4{1.f};
            MVMatrix     = camera.getViewMatrix()*MVMatrix;
            MVMatrix     = glm::translate(MVMatrix, b.getCoords()); // Translation * Rotation * Translation
            MVMatrix     = glm::rotate(MVMatrix, glm::angle(glm::vec3{0.,1.,0.},glm::normalize(direction)),glm::normalize(glm::cross(glm::vec3{0.,1.,0.}, direction)));
            MVMatrix     = glm::scale(MVMatrix, glm::vec3{.2f*Boid::UI_meshRadius}); // Translation * Rotation * Translation * Scale
            
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVPMatrix = ProjMatrix * MVMatrix;
            
            glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
            glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
            
            glDrawArrays(GL_TRIANGLES, 0 /* Pas d'offset au début du VBO */, coneVertices.size());
            vaoCones.unbind(); 
        }
        
        AquariumPrgm.m_program.use();
        //DESSIN DE L'AQUARIUM
        vaoAquarium.bind();
        // MVMatrix = glm::translate(glm::mat4{1.f},glm::vec3(0,0,-5.f));
        MVMatrix = glm::mat4{1.f};
        MVMatrix     = camera.getViewMatrix()*MVMatrix;
        MVMatrix = glm::scale(MVMatrix, glm::vec3{Wall::UI_AQUARIUMSIZE});

        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVPMatrix = ProjMatrix * MVMatrix;

        glUniformMatrix4fv(AquariumPrgm.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(AquariumPrgm.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(AquariumPrgm.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        
        glActiveTexture(GL_TEXTURE0);
        oceanTex1.bind();
        glActiveTexture(GL_TEXTURE1);
        oceanTex2.bind();

        glUniform1i(AquariumPrgm.uTexture1,0);
        glUniform1i(AquariumPrgm.uTexture2,1);

        glDrawArrays(GL_TRIANGLES, 0 /* Pas d'offset au début du VBO */, aquaVertices.size());
        
        oceanTex2.unbind();
        glActiveTexture(GL_TEXTURE0);
        oceanTex1.unbind();


        shader.use();
        //DESSIN DE L'ARPENTEUR
        MVMatrix = glm::mat4{1.f};
        MVMatrix = camera.getViewMatrix()*MVMatrix;
        MVMatrix = glm::translate(MVMatrix,camera.getPos());
        MVMatrix = glm::rotate(MVMatrix,glm::angle(glm::normalize(catWalker.getForward()),glm::normalize(camera.getFront())),glm::normalize(glm::cross(catWalker.getForward(),camera.getFront())));
        MVMatrix = glm::translate(MVMatrix,catWalker.getCoords()-camera.getPos());
        MVMatrix = glm::scale(MVMatrix, glm::vec3{catWalker.getSize()});

        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVPMatrix = ProjMatrix * MVMatrix;

        glUniformMatrix4fv(uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));

        glDrawArrays(GL_TRIANGLES,0,aquaVertices.size());

        vaoAquarium.unbind();

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}