#pragma once
#include "boid.hpp"
#include <vector>
#include <random>

class Flock{
    private :
        std::vector<Boid> _boids;

    public :
        explicit Flock(int n = 30);

        void update();

        inline std::vector<Boid> getFlock(){return _boids;}
};