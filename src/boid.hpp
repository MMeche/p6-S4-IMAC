#pragma once
#include <vector>
#include<iostream>
#include "obstacles.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "p6/p6.h"
#include <glm/glm.hpp>


class Boid{
    private :
        glm::vec3 _coords{};
        glm::vec3 _velocity{};
        glm::vec3 _acceleration{};
        
        float _separationRadius = 0.1;
        float _alignementRadius = 0.4;
        float _cohesionRadius   = 0.4;
    public:
        static constexpr float MAXSPEED = 0.7;
        static constexpr float MAXFORCE = 0.4;
    
        const float meshRadius = 0.05;

    Boid()= default;
    Boid(glm::vec3& posit,glm::vec3& speed)
         : _coords{posit},_velocity{speed}
         {};

    void SeparationForce(std::vector<Boid>& f,std::vector<Wall>& o);
    void AlignementForce(std::vector<Boid>& f);
    void CohesionForce  (std::vector<Boid>& f);
    void wrapAround(); 
    void update(std::vector<Boid> & f, std::vector<Wall> & o, float deltaTime);

    inline glm::vec3 getCoords(){return _coords;};
    inline glm::vec3 getSpeed(){return _velocity;};


    inline void setCoords(glm::vec3 pos){_coords = pos;};

};

