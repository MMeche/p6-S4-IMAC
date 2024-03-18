#include "UI.hpp"


void UI::startUI()
{
    ImGui::Begin("User Interface");
    ImGui::SliderFloat("Boids radius", &Boid::UI_meshRadius, 0.f, 6.f);
    ImGui::SliderFloat("Velocity", &Boid::UI_MAXSPEED, 0.f, 6.f);
    ImGui::SliderFloat("Force intensity", &Boid::UI_MAXFORCE, 0.f, 6.f);
    ImGui::End();
}