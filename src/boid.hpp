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

        float _obstacleRadius   = 0.2;

        int _type = 0 ; //0 for fish 1 for star;
        glm::vec4 _color;

        
    public:
        static constexpr float MAXSPEED = 0.5;
        static constexpr float MAXFORCE = 0.3;

        static float UI_MAXSPEED ;
        static float UI_FORCE_COHESION;
        static float UI_FORCE_ALIGNEMENT;
        static float UI_FORCE_SEPARATION;
        static float UI_meshRadius;
    
        const float meshRadius = 0.05;

    Boid()= default;
    Boid(glm::vec3& posit,glm::vec3& speed, int& type, glm::vec4& color)
         : _coords{posit},_velocity{speed}, _type{type}, _color{color}
         {};

    void SeparationForce(std::vector<Boid>& f,std::vector<Wall>& o);
    void AlignementForce(std::vector<Boid>& f);
    void CohesionForce  (std::vector<Boid>& f);
    void wrapAround(); 
    void update(std::vector<Boid> & f, std::vector<Wall> & o, float deltaTime);

    inline glm::vec3 getCoords(){return _coords;};
    inline glm::vec3 getSpeed(){return _velocity;};
    inline int getType(){return _type;};
    inline glm::vec4 getColor(){return _color;};


    inline void setCoords(glm::vec3 pos){_coords = pos;};

};

