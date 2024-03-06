#include <cstdlib>
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "p6/p6.h"
#include "flock.hpp"

int main()
{
    // Run the tests
    if (doctest::Context{}.run() != 0)
        return EXIT_FAILURE;

    // Actual application code
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    Flock boids = Flock(30);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::BlueGray);
        boids.update(ctx.delta_time());
        for(Boid &b : boids.getFlock())
        {
            ctx.triangle( glm::vec2(b.meshRadius/2,0),glm::vec2(0,2*b.meshRadius), glm::vec2(-b.meshRadius/2,0), p6::Center(b.getCoords()));
        }
        ctx.square(p6::Center(0,0),p6::Radius(1),p6::Angle(glm::vec2(0,0)));

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}