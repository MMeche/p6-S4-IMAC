#include "boid.hpp"
#include <algorithm>
#include <vector>
#include "glm/common.hpp"
#include "glm/geometric.hpp"


void Boid::SeparationForce(std::vector<Boid>& f){
    glm::vec3 totalForce;
    int cmp{};
    for(Boid &b : f)
    {
        float distance = glm::distance(_coords,b._coords);
        if((distance > 0 ) && distance<=_separationRadius)
        {
            totalForce += glm::normalize(_coords-b._coords)/distance;
            cmp++;
        }
    }
    if(cmp>0)
    {
        totalForce/=cmp;
    }
    totalForce = glm::normalize(totalForce);
    totalForce *= MAXSPEED;
    totalForce -= _velocity;

    _acceleration += 5.f*glm::normalize(totalForce)*MAXFORCE;
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
        direction = glm::normalize(direction);
        direction *= MAXSPEED;
        
        glm::vec3 steer = direction - _velocity;

        _acceleration += 0.5f*glm::normalize(steer)*MAXFORCE;
    }
}

void Boid::CohesionForce(std::vector<Boid>& f){
    glm::vec3 target;
    int cmp{};
    for(Boid &b : f)
    {
        float distance = glm::distance(_coords,b._coords);
        if((distance >0) && (distance <= _cohesionRadius))
        {
            cmp++;
            target += b._coords;
        }
    }
    if(cmp>0)
    {
        target /= cmp;
        glm::vec3 desired = (target - _coords);
        desired = glm::normalize(desired)*MAXSPEED;

        glm::vec3 steer = desired - _velocity;
        _acceleration += 0.05f*glm::normalize(steer)*MAXFORCE;
    }
}

void Boid::wrapAround()
{
    if(_coords.x > 1.)  {_coords.x = -1.+meshRadius;}
    if(_coords.y > 1.)  {_coords.y = -1.+meshRadius;}
    if(_coords.x < -1.) {_coords.x =  1.-meshRadius;}
    if(_coords.y < -1.) {_coords.y =  1.-meshRadius;}
}

void Boid::update(std::vector<Boid>& f){
    SeparationForce(f);
    AlignementForce(f);
    CohesionForce(f);

    _velocity += _acceleration;
    _velocity  = glm::normalize(_velocity)*MAXSPEED;
    std::cout<<_velocity.x<<", "<<_velocity.y<<"\n";
    _coords   += _velocity;
    wrapAround();
    _acceleration = glm::vec3(0,0,0);
}
