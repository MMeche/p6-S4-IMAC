#include <cstdlib>
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
        boids.update();
        for(Boid &b : boids.getFlock())
        {
            ctx.circle(glm::vec2(b.getCoords().x,b.getCoords().y),b.meshRadius);
        }

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}