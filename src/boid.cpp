#include "boid.hpp"
#include <vector>

void Boid::SeparationForce(std::vector<Boid>& f){
    Vec3 totalForce;
    for(Boid &b : f)
    {
        float distance = _coords.length(b._coords);
        if(distance<=_separationRadius)
        {
            totalForce = totalForce + (_coords-b._coords)/distance;
        }
    }
}

void Boid::AlignementForce(std::vector<Boid>& f){

}

void Boid::CohesionForce(std::vector<Boid>& f){

}