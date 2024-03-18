#include "UI.hpp"


void UI::startUI(Flock boids)
{
    ImGui::Begin("User Interface");
    ImGui::SliderFloat("Boids radius", &Boid::UI_meshRadius, 0.f, 6.f);
    ImGui::SliderFloat("Velocity", &Boid::UI_MAXSPEED, 0.f, 6.f);
    ImGui::SliderFloat("Cohesion intensity", &Boid::UI_FORCE_COHESION, 0.f, 6.f);
    ImGui::SliderFloat("Alignement intensity", &Boid::UI_FORCE_ALIGNEMENT, 0.f, 6.f);
    ImGui::SliderFloat("Separation intensity", &Boid::UI_FORCE_SEPARATION, 0.f, 6.f);
    ImGui::SliderInt("Number of Boids",&Flock::UI_NumberBoid,0,100);
    ImGui::End();

    if(Flock::UI_NumberBoid > boids.getFlock().size())
        {
            boids.instantiateNewBoid(Flock::UI_NumberBoid - boids.getFlock().size());
        }
        if(Flock::UI_NumberBoid < boids.getFlock().size())
        {
            boids.deleteBoid(boids.getFlock().size() - Flock::UI_NumberBoid);
        }
}