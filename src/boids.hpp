#pragma once
#include <iostream>
#include <vector>
class boid {
private:
    float x{};
    float y{};
    float z{};

public:
    // float seperation;
    // float alignment;
    // float cohesion;
};

class appearance : public boid {
protected:
    // unsigned int color; // Donnée accessible, aux classes filles. fichier boids.h
    float            my_diametre;
    std::vector<int> m_color;

public:
    appearance() = default;
    void appearance::SetColor(unsigned int);
    // void appearance::appearance() const;
    //  void appearance::SetColor() const;
    appearance& operator=(std::vector<int> m_color);
    // appearance& operator=(const appearance&);
    ~appearance() = default;
};

class flock {
};