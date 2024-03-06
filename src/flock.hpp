#pragma once
#include "boid.hpp"
#include <vector>
#include "p6/p6.h"
#include <random>

class Flock{
    private :
        std::vector<Boid> _boids;

    public :
        explicit Flock(int n = 30);

        void update(float deltaTime);

        inline std::vector<Boid> getFlock(){return _boids;}
};