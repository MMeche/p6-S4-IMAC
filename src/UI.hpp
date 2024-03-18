#pragma once
#include <imgui.h>
#include "boid.hpp"
#include "flock.hpp"

class UI
{
    UI(){};
    public:
    static void startUI(Flock boids);
};