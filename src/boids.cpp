#include "../src/boids.hpp"

void appearance::SetColor(unsigned int NewColor)
{
    // m_color = NewColor; // Définit la couleur.
    m_color   = std::vector<int>(3);
    int red   = NewColor / 255.0f;
    int green = NewColor / 255.0f;
    int blue  = NewColor / 255.0f;
    m_color   = {red, green, blue};
}

appearance& appearance::operator=(const std::vector<int>& color)
{
    m_color = color;
    return *this;
}

// appearance& operator=(std::vector<int> m_color)
// {
//     appearance m_color = red.m_color;
//     appearance m_color = green.m_color;
//     appearance m_color = blue.m_color;
//     return m_color;
// };

// void appearance::appearance() const
// {
//     m_color              = std::vector<int>(3);
//     const int m_color[0] = red;
//     const int m_color[1] = green;
//     const int m_color[2] = blue;
// };