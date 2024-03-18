#include <cstdlib>
#include <vector>
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"
#include "UI.hpp"
#include "flock.hpp"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Old Boids"}};
    ctx.maximize_window();

    Flock boids = Flock(30);

    Wall aquarium = Wall(glm::vec3(0,0,0),1.,1.,1.);
    std::vector<Wall> obstacles;
    obstacles.push_back(aquarium);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // User interface controler
        UI::startUI();
        if(Flock::UI_NumberBoid > boids.getFlock().size())
        {
            boids.instantiateNewBoid(Flock::UI_NumberBoid - boids.getFlock().size());
        }
        if(Flock::UI_NumberBoid < boids.getFlock().size())
        {
            boids.deleteBoid(boids.getFlock().size() - Flock::UI_NumberBoid);
        }
        ctx.background(p6::NamedColor::BlueGray);
        boids.update(obstacles, ctx.delta_time());
        for (Boid& b : boids.getFlock())
        {
            ctx.triangle(glm::vec2(2 * b.meshRadius*Boid::UI_meshRadius, 0), glm::vec2(0, b.meshRadius*Boid::UI_meshRadius / 2), glm::vec2(0, -b.meshRadius*Boid::UI_meshRadius / 2), p6::Center(b.getCoords()), p6::Angle(b.getSpeed()));
        }
        ctx.square(p6::Center(aquarium.getCoords()));

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}