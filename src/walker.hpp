#pragma once
#include "FreeflyCamera.hpp"
#include "obstacles.hpp"
#include "p6/p6.h"

class Walker //: public  Wall to enable the boids avoiding the walker
{ 
    private :
        glm::vec3 _coords{};
        glm::vec3 _forward{};
        float _size{Wall::UI_AQUARIUMSIZE*0.1f};
        float _velocity{};
        FreeflyCamera _camera;
        //glm::vec3 _acceleration{}; to implement gravity later

    public :
    Walker();

    // Moving/Turning
    void moveForward();
    void moveBackward();
    void moveRight();
    void moveLeft();
    void stayInBox(float width,float height,float depth);
    void turn(glm::vec2 mouseD,float t);
    

    // Getter Setter
    void setCoords(glm::vec3 newCoords);
    void setVelocity(float newVelocity);
    glm::vec3 getCoords();
    inline float getSize(){return _size;};
    float getVelocity();
    glm::vec3 getForward();
    FreeflyCamera getCamera();
};