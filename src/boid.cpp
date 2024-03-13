#include "boid.hpp"
#include <algorithm>

#include "glm/common.hpp"
#include "p6/p6.h"
#include "glm/geometric.hpp"


void Boid::SeparationForce(std::vector<Boid>& f,std::vector<Wall>& o){
    glm::vec3 totalForce{};
    for(Boid &b : f)
    {
        float distance = glm::distance(_coords,b._coords);
        if((distance > 0 ) && distance<=_separationRadius)
        {
            totalForce += (_coords-b._coords)/distance;
        }
    }
    for(Wall &w : o)
    {
        float distanceX = _coords.x - w.getCoords().x;
        float distanceY = _coords.y - w.getCoords().y;
        if(distanceX <= _separationRadius){}
    }
    _acceleration += totalForce;
}

void Boid::AlignementForce(std::vector<Boid>& f){
    glm::vec3 direction{};
    int cmp{};
    for(Boid &b : f)
    {
        float distance = glm::distance(_coords,b._coords);
        
        if((distance > 0)&& distance <= _alignementRadius)
        {
            direction += b._velocity;
            cmp++;
        }
    }
    if(cmp>0)
    {
        direction /= cmp;

        _acceleration += direction;
    }
}

void Boid::CohesionForce(std::vector<Boid>& f)
{
    glm::vec3 target{};
    int          cmp{};
    for (Boid& b : f)
    {
        float distance = glm::distance(_coords, b._coords);
        if ((distance > 0) && (distance <= _cohesionRadius))
        {
            cmp++;
            target += b._coords;
        }
    }
    if (cmp > 0)
    {
        target /= cmp;
        glm::vec3 cohesionDirection = target - _coords;

        // Ajouter cette direction à l'accélération du boid
        _acceleration += cohesionDirection;
    }
}

void Boid::wrapAround()
{
    if(_coords.x + meshRadius > 1.)  {_coords.x = -1.+meshRadius;}
    if(_coords.y + meshRadius > 1.)  {_coords.y = -1.+meshRadius;}
    if(_coords.x - meshRadius < -1.) {_coords.x =  1.-meshRadius;}
    if(_coords.y - meshRadius < -1.) {_coords.y =  1.-meshRadius;}
}

void Boid::update(std::vector<Boid>& f, std::vector<Wall>& o, float deltaTime){
    SeparationForce(f,o);
    AlignementForce(f);
    CohesionForce  (f);

    _velocity += _acceleration * deltaTime;
    _velocity  = glm::normalize(_velocity)*MAXSPEED;
    _coords   += _velocity  * deltaTime;
    wrapAround();
    _acceleration = glm::vec3(0,0,0);
}
