#include "boid.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "glm/common.hpp"
#include "p6/p6.h"
#include "glm/geometric.hpp"

float Boid::UI_FORCE_COHESION = 1.;
float Boid::UI_FORCE_ALIGNEMENT = 1.;
float Boid::UI_FORCE_SEPARATION = 1.;
float Boid::UI_MAXSPEED = 1.;
float Boid::UI_meshRadius = 1.;

void Boid::SeparationForce(std::vector<Boid>& f,std::vector<Wall>& o){
    glm::vec3 totalForce{};
    for(Boid &b : f)
    {
        float distance = glm::distance(_coords,b._coords);
        if((distance > 0 ) && distance<=_separationRadius+UI_meshRadius*meshRadius)
        {
            totalForce += UI_FORCE_SEPARATION*(_coords-b._coords)/distance;
        }
    }
    for(Wall &w : o)
    {
        
        float distanceX = std::abs(_coords.x - w.getCoords().x);
        float distanceY = std::abs(_coords.y - w.getCoords().y);
        float distanceZ = std::abs(_coords.z - w.getCoords().z);
        if(distanceX >= w.getWidth()-_obstacleRadius)
        {
            totalForce += (_coords - glm::vec3(1*glm::sign(_coords.x),_coords.y,_coords.z))/(0.25f*(1-distanceX));
        }
        if(distanceY >= w.getHeigth()-_obstacleRadius)
        {
            totalForce += (_coords - glm::vec3(_coords.x,1*glm::sign(_coords.y),_coords.z))/(0.25f*(1-distanceY));
        }
        if(distanceZ >= w.getDepth()-_obstacleRadius)
        {
            totalForce += (_coords - glm::vec3(_coords.x,_coords.y,1*glm::sign(_coords.z)))/(0.25f*(1-distanceZ));
        }
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

        _acceleration += UI_FORCE_ALIGNEMENT*direction;
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
        _acceleration += UI_FORCE_COHESION*cohesionDirection;
    }
}

void Boid::wrapAround()
{
    if(_coords.x + meshRadius*UI_meshRadius > Wall::UI_AQUARIUMSIZE)  {_coords.x = -Wall::UI_AQUARIUMSIZE+meshRadius*UI_meshRadius;}
    if(_coords.y + meshRadius*UI_meshRadius > Wall::UI_AQUARIUMSIZE)  {_coords.y = -Wall::UI_AQUARIUMSIZE+meshRadius*UI_meshRadius;}
    if(_coords.z + meshRadius*UI_meshRadius > Wall::UI_AQUARIUMSIZE)  {_coords.z = -Wall::UI_AQUARIUMSIZE+meshRadius*UI_meshRadius;}

    if(_coords.x - meshRadius*UI_meshRadius < -Wall::UI_AQUARIUMSIZE) {_coords.x =  Wall::UI_AQUARIUMSIZE-meshRadius*UI_meshRadius;}
    if(_coords.y - meshRadius*UI_meshRadius < -Wall::UI_AQUARIUMSIZE) {_coords.y =  Wall::UI_AQUARIUMSIZE-meshRadius*UI_meshRadius;}
    if(_coords.z - meshRadius*UI_meshRadius < -Wall::UI_AQUARIUMSIZE) {_coords.z =  Wall::UI_AQUARIUMSIZE-meshRadius*UI_meshRadius;}
}

void Boid::update(std::vector<Boid>& f, std::vector<Wall>& o, float deltaTime){
    SeparationForce(f,o);
    AlignementForce(f);
    CohesionForce  (f);

    _velocity += _acceleration * deltaTime;
    _velocity  = glm::normalize(_velocity)*MAXSPEED*UI_MAXSPEED;
    _coords   += _velocity  * deltaTime;
    wrapAround();
    _acceleration = glm::vec3(0,0,0);
}
