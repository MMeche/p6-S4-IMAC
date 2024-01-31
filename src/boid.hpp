#pragma once
#include <vector>
#include "math.hpp"


class Boid{
    private :
        Vec3 _coords;
        Vec3 _velocity;
        Vec3 _acceleration;
        
        float _separationRadius;
        float _alignementRadius;
        float _cohesionRadius;


    public :
    Boid(Vec3& posit,
         Vec3& speed,
         Vec3& accel,
         float r, float a, float c)
         : _coords{posit},_velocity{speed},_acceleration{accel},
           _separationRadius{r},_alignementRadius{a},_cohesionRadius{c}
         {
         };

    void SeparationForce(std::vector<Boid>& f);
    void AlignementForce(std::vector<Boid>& f);
    void CohesionForce  (std::vector<Boid>& f);


};

