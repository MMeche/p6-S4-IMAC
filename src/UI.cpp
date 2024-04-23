#include "UI.hpp"


void UI::startUI(Flock& boids, std::vector<Wall>& obstacles)
{
    ImGui::Begin("User Interface");
    ImGui::SliderFloat("Boids radius", &Boid::UI_meshRadius, 0.f, 6.f);
    ImGui::SliderFloat("Velocity", &Boid::UI_MAXSPEED, 0.f, 6.f);
    ImGui::SliderFloat("Cohesion intensity", &Boid::UI_FORCE_COHESION, 0.f, 6.f);
    ImGui::SliderFloat("Alignement intensity", &Boid::UI_FORCE_ALIGNEMENT, 0.f, 6.f);
    ImGui::SliderFloat("Separation intensity", &Boid::UI_FORCE_SEPARATION, 0.f, 6.f);
    ImGui::SliderInt("Number of Boids",&Flock::UI_NumberBoid,0,100);
    ImGui::SliderFloat("Size of the Aquarium, dang!",&Wall::UI_AQUARIUMSIZE,1.,10);
    ImGui::End();

    //Pour que le nombre de boids corresponde toujours avec l'affichage de l'UI
    if(Flock::UI_NumberBoid > boids.getFlock().size())
    {
        boids.instantiateNewBoid(Flock::UI_NumberBoid - boids.getFlock().size());
    }
    if(Flock::UI_NumberBoid < boids.getFlock().size())
    {
        boids.deleteBoid(boids.getFlock().size() - Flock::UI_NumberBoid);
    }
    
    //Pour que la taille de l'aquarium corresponde toujours avec l'affichage de l'UI
    if(Wall::UI_AQUARIUMSIZE != obstacles[0].getWidth())
    {
        obstacles[0].setSize(Wall::UI_AQUARIUMSIZE);
    }
}