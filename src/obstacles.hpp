#pragma once
#include <glm/glm.hpp>

class Wall{
    
    private:
    float _scaleX{1.};
    float _scaleY{1.};
    float _scaleZ{1.};
    glm::vec3 _center{};

    public:
    Wall(float x,float y, float z, float scaleX,float scaleY,float scaleZ) : _center{glm::vec3(x,y,z)},_scaleX{scaleX}, _scaleY{scaleY}, _scaleZ{scaleZ}{};
    Wall(glm::vec3 coords,float scaleX, float scaleY,float scaleZ)         : _center{coords},_scaleX{scaleX}, _scaleY{scaleY}, _scaleZ{scaleZ}{};
    
    inline glm::vec3 getCoords(){return _center;};


};