#pragma once
#include "boid.hpp"
#include <vector>
#include "p6/p6.h"
#include <random>

class Flock{
    private :
        std::vector<Boid> _boids;

    public :
        static int UI_NumberBoid;
        explicit Flock(int n = 30);

        void update(std::vector<Wall> & o, float deltaTime);
        void instantiateNewBoid(int n);
        void deleteBoid(int n);

        inline std::vector<Boid> getFlock(){return _boids;}
};