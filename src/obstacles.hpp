#pragma once
#include <glm/glm.hpp>

class Wall{
    
    private:
    float _width{1.};
    float _heigth{1.};
    float _scaleZ{1.};
    glm::vec3 _center{};

    public:
    Wall(float x,float y, float z, float width,float heigth,float depth) : _center{glm::vec3(x,y,z)},_width{width}, _heigth{heigth}, _scaleZ{depth}{};
    Wall(glm::vec3 coords,float width, float heigth,float depth)         : _center{coords},_width{width}, _heigth{heigth}, _scaleZ{depth}{};
    inline glm::vec3 getCoords(){return _center;};
    inline float     getScaleX(){return _width;};
    inline float     getScaleY(){return _heigth;};
    inline float     getScaleZ(){return _scaleZ;};


};