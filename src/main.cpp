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

    Flock boids = Flock(10);

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::White);
        boids.update();
        for(Boid &b : boids.getFlock())
        {
            if(b.getCoords().x < -b.meshRadius) {b.setCoords(glm::vec3(1+b.meshRadius,b.getCoords().y,b.getCoords().z));}
            if(b.getCoords().y < -b.meshRadius) {b.setCoords(glm::vec3(b.getCoords().x,1+b.meshRadius,b.getCoords().z));}

            
            ctx.circle(glm::vec2(b.getCoords()),b.meshRadius);
        }

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}