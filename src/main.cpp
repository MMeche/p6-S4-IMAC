#include <cstdlib>
#include <vector>
#include "FreeflyCamera.hpp"
#include "GLFW/glfw3.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "shape_vertices.hpp"
#include "loader.hpp"
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
#include "clouds.hpp"
#include "programs.hpp"

int main()
{
    auto ctx = p6::Context{{.title = "Old Boids"}};
    
    
    Flock boids = Flock(30);
    Wall aquarium = Wall(glm::vec3(0,0,0),2*Wall::UI_AQUARIUMSIZE);
    std::vector<Wall> obstacles;
    Walker catWalker;
    Clouds clouds;
    obstacles.push_back(aquarium);
    //obstacles.push_back(catWalker);
    
    
    img::Image souslocean1 = p6::load_image_buffer("assets/textures/aquarium_1.png");
    img::Image souslocean2 = p6::load_image_buffer("assets/textures/aquarium_2.png");

    const std::vector<glimac::ShapeVertex> fishVerticesBQ = loadOBJ("assets/obj/poisson_bq.obj");
    const std::vector<glimac::ShapeVertex> fishVerticesHQ = loadOBJ("assets/obj/poisson_hq.obj");
    
    const std::vector<glimac::ShapeVertex> starVerticesBQ = minimalLoadOBJ("assets/obj/star_bq.obj");
    const std::vector<glimac::ShapeVertex> starVerticesHQ = minimalLoadOBJ("assets/obj/star_hq.obj");

    const std::vector<glimac::ShapeVertex> cloudVerticesHQ = minimalLoadOBJ("assets/obj/cloud1.obj");
    
    
    

    const p6::Shader shader = p6::load_shader(
        "shaders/3D.vs.glsl",
        "shaders/normal.fs.glsl"
    );
    AquariumProgram AquariumPrgm{};
    FishProgram FishPrgm{};
    StarProgram StarPrgm{};
    CloudProgram CloudPrgm{};

    ctx.maximize_window();
    
    // Création d'un Vertex Buffer Object et d'un Vertex Array Object
    VBO vboFishBQ{};
    VAO vaoFishBQ{};

    VBO vboFishHQ{};
    VAO vaoFishHQ{};

    VBO vboStarBQ{};
    VAO vaoStarBQ{};

    VBO vboStarHQ{};
    VAO vaoStarHQ{};

    VBO vboAquarium{};
    VAO vaoAquarium{};


    VBO vboCloud{};
    VAO vaoCloud{};
     //texture bindings
        TextureID oceanTex1{};
        TextureID oceanTex2{};

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
    

    vboFishBQ.bind();
    glBufferData(GL_ARRAY_BUFFER, fishVerticesBQ.size()*sizeof(glimac::ShapeVertex), fishVerticesBQ.data(), GL_STATIC_DRAW);
    vboFishBQ.unbind();

    vboFishHQ.bind();
    glBufferData(GL_ARRAY_BUFFER, fishVerticesHQ.size()*sizeof(glimac::ShapeVertex), fishVerticesHQ.data(), GL_STATIC_DRAW);
    vboFishHQ.unbind();

    vboStarBQ.bind();

    glBufferData(GL_ARRAY_BUFFER, starVerticesBQ.size()*sizeof(glimac::ShapeVertex), starVerticesBQ.data(), GL_STATIC_DRAW);
    vboStarBQ.unbind();

    vboStarHQ.bind();
    glBufferData(GL_ARRAY_BUFFER, starVerticesHQ.size()*sizeof(glimac::ShapeVertex), starVerticesHQ.data(), GL_STATIC_DRAW);
    vboStarHQ.unbind();

    vboAquarium.bind();
    const std::vector<glimac::ShapeVertex> aquaVertices = glimac::cube_vertices(1.);
    glBufferData(GL_ARRAY_BUFFER,aquaVertices.size()*sizeof(glimac::ShapeVertex),aquaVertices.data(),GL_STATIC_DRAW);
    vboAquarium.unbind();

    vboCloud.bind();
    glBufferData(GL_ARRAY_BUFFER,cloudVerticesHQ.size()*sizeof(glimac::ShapeVertex),cloudVerticesHQ.data(),GL_STATIC_DRAW);
    vboCloud.unbind();
    
    vaoFishBQ.bind();
    static constexpr GLuint vertex_attr_position = 0;
    static constexpr GLuint vertex_attr_normal   = 1;
    static constexpr GLuint vertex_attr_tex      = 2;
    
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    
    
    vboFishBQ.bind();   
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
    vboFishBQ.unbind();
    vaoFishBQ.unbind();

    vaoFishHQ.bind();

    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    
    
    vboFishHQ.bind();   
    
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
    vboFishHQ.unbind();
    vaoFishHQ.unbind();

    vaoStarBQ.bind();
    
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    
    
    vboStarBQ.bind();   
    
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
    vboStarBQ.unbind();
    vaoStarBQ.unbind();

    vaoStarHQ.bind();
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    vboStarHQ.bind();   
    
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
    vboStarHQ.unbind();
    vaoStarHQ.unbind();

    vaoAquarium.bind();
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);

    vboAquarium.bind();
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
    
    vaoCloud.bind();
    glEnableVertexAttribArray(vertex_attr_position);
    glEnableVertexAttribArray(vertex_attr_normal);
    glEnableVertexAttribArray(vertex_attr_tex);
    vboCloud.bind();   
    
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
    vboCloud.unbind();
    vaoCloud.unbind();
    
    glEnable(GL_DEPTH_TEST);
    
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
        catWalker.update(aquarium.getWidth());
        FreeflyCamera camera = catWalker.getCamera();
        clouds.updateCloud();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        glm::mat4 ProjMatrix   = glm::perspective(glm::radians(100.f), ctx.aspect_ratio(), 0.1f, 100.f);
        glm::mat4 MVMatrix;
        glm::mat4 NormalMatrix;
        glm::mat4 MVPMatrix;
        glm::vec4 color;
        
        // DESSIN DES BOIDS
        for (Boid& b : boids.getFlock())
        {
            color = b.getColor();
            glm::vec3 direction = -b.getSpeed();
            MVMatrix = glm::mat4{1.f};
            MVMatrix     = camera.getViewMatrix()*MVMatrix;
            MVMatrix     = glm::translate(MVMatrix, b.getCoords());
            MVMatrix     = glm::rotate(MVMatrix, glm::angle(glm::normalize(glm::vec3{0.,0.,1.}),glm::normalize(direction)),glm::normalize(glm::cross(glm::vec3{0.,0.,1.}, direction)));
            MVMatrix     = glm::scale(MVMatrix, glm::vec3{.02f*Boid::UI_meshRadius});
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVPMatrix = ProjMatrix * MVMatrix;
            if(b.getType()==0){
                FishPrgm.m_program.use();    
                glUniformMatrix4fv(FishPrgm.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
                glUniformMatrix4fv(FishPrgm.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(FishPrgm.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
                glUniform4f(FishPrgm.uColor,color.x,color.y,color.z,color.w);
                
                float distance = glm::distance(b.getCoords(), camera.getPos());
                if(distance<0.5){
                    vaoFishHQ.bind();
                    glDrawArrays(GL_TRIANGLES, 0, fishVerticesBQ.size());
                    vaoFishHQ.unbind();
                }
                else{
                    vaoFishBQ.bind();
                    glDrawArrays(GL_TRIANGLES, 0, fishVerticesHQ.size());
                    vaoFishBQ.unbind();
                }
            }
            else{
                StarPrgm.m_program.use();
                glUniformMatrix4fv(StarPrgm.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
                glUniformMatrix4fv(StarPrgm.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(StarPrgm.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
                glUniform4f(StarPrgm.uColor,color.x,color.y,color.z,color.w);
                
                vaoStarBQ.bind();
                glDrawArrays(GL_TRIANGLES, 0, starVerticesBQ.size());
                vaoStarBQ.unbind();
            }
        }
        
        
        //DESSIN DE L'AQUARIUM
        AquariumPrgm.m_program.use();
        vaoAquarium.bind();
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
        vaoAquarium.unbind();


        
        //DESSIN DE L'ARPENTEUR
        StarPrgm.m_program.use();
        vaoStarBQ.bind();
        
        MVMatrix = glm::mat4{1.f};
        

        MVMatrix = glm::translate(MVMatrix,camera.getPos());
        MVMatrix = glm::rotate(MVMatrix,glm::angle(glm::normalize(catWalker.getForward()),glm::normalize(camera.getFront())),glm::normalize(glm::cross(catWalker.getForward(),camera.getFront())));
        MVMatrix = glm::translate(MVMatrix,catWalker.getCoords()-camera.getPos());
        MVMatrix = camera.getViewMatrix()*MVMatrix;
        

        MVMatrix = glm::scale(MVMatrix, glm::vec3{catWalker.getSize()});
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        MVPMatrix = ProjMatrix * MVMatrix;

        if(catWalker.getState()){
            color = glm::vec4{1.0,0.1,0.1,1.};

        }else{
            color = glm::vec4{0.9,0.2,0.4,1.};
        }
        glUniformMatrix4fv(StarPrgm.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(StarPrgm.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(StarPrgm.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        glUniform4f(StarPrgm.uColor,color.x,color.y,color.z,color.w);

        glDrawArrays(GL_TRIANGLES,0,starVerticesBQ.size());

        vaoStarBQ.unbind();

        //DESSIN DES NUAGES Didn't make it in time
        // CloudPrgm.m_program.use();
        
        // MVMatrix = glm::mat4{1.f};
        // MVMatrix     = camera.getViewMatrix()*MVMatrix;
        // MVMatrix = glm::scale(MVMatrix, glm::vec3{0.1f*Wall::UI_AQUARIUMSIZE});

        // NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        // MVPMatrix = ProjMatrix * MVMatrix;
        // color = glm::vec4(1.,1.,1.,1.);

        // glUniformMatrix4fv(CloudPrgm.uNormalMatrix,1,GL_FALSE,glm::value_ptr(NormalMatrix));
        // glUniformMatrix4fv(CloudPrgm.uMVMatrix,1,GL_FALSE,glm::value_ptr(MVMatrix));
        // glUniformMatrix4fv(CloudPrgm.uMVPMatrix,1,GL_FALSE,glm::value_ptr(MVPMatrix));
        // glUniform4f(CloudPrgm.uColor,color.x,color.y,color.z,color.w);

        // vaoCloud.bind();
        // glDrawArrays(GL_TRIANGLES,0,cloudVerticesHQ.size());
        // vaoCloud.unbind();

    };
    ctx.start();
}