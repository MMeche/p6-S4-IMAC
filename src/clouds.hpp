#pragma once
#include <vector>
#include "p6/p6.h"
#include "random.hpp"

#include <vector>
class Clouds{
    private :
    std::vector<glm::vec3> _clouds{};
    glm::vec3 _wind{0.1,0.,0.}; //its the speed vector;

    public :
    Clouds();
    void addCloud();
    void deleteCloud(int index);
    void updateCloud();
};