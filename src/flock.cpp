#include "flock.hpp"
#include "glm/common.hpp"
#include "glm/ext/quaternion_geometric.hpp"


thread_local std::default_random_engine gen{std::random_device{}()};
thread_local auto distrib = std::uniform_real_distribution<double>{-1.0, 1.0};
int Flock::UI_NumberBoid = 0;

Flock::Flock(int n)
{
    Flock::UI_NumberBoid = n;
    for(int i = 0 ; i < n ; i++)
    {
        glm::vec3 r_pos   = glm::vec3(distrib(gen),distrib(gen),0);
        glm::vec3 r_speed = glm::vec3(distrib(gen),distrib(gen),0);
        r_speed = glm::normalize(r_speed);
        r_speed = glm::min(r_speed,r_speed*Boid::MAXSPEED);
        
        Boid boid = Boid(r_pos,r_speed);
        _boids.push_back(boid);
    }
}

void Flock::instantiateNewBoid(int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        glm::vec3 r_pos   = glm::vec3(distrib(gen),distrib(gen),0);
        glm::vec3 r_speed = glm::vec3(distrib(gen),distrib(gen),0);
        r_speed = glm::normalize(r_speed);
        r_speed = glm::min(r_speed,r_speed*Boid::MAXSPEED);
        
        Boid boid = Boid(r_pos,r_speed);
        _boids.push_back(boid);
    }
}

void Flock::deleteBoid(int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        _boids.pop_back();
    }
}

void Flock::update(std::vector<Wall> & o,float deltaTime)
{
    for(Boid &b : _boids)
    {
        b.update(_boids,o,deltaTime);
    }
}
