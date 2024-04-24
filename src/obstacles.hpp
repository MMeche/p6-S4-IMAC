#pragma once
#include <glm/glm.hpp>

class Wall{
    
    private:
    float _width{1.};
    float _heigth{1.};
    float _depth{1.};
    glm::vec3 _center{};

    public:
    static float UI_AQUARIUMSIZE;
    Wall();
    Wall(float x,float y, float z, float width,float heigth,float depth) : _center{glm::vec3(x,y,z)},_width{width}, _heigth{heigth}, _depth{depth}{};
    Wall(glm::vec3 coords,float width, float heigth,float depth)         : _center{coords},_width{width}, _heigth{heigth}, _depth{depth}{};
    Wall(glm::vec3 coords, float size)                                   : _center{coords},_width{size}, _heigth{size}, _depth{size}{};
    
    
    inline glm::vec3 getCoords(){return _center;};
    inline float     getWidth(){return _width;};
    inline float     getHeigth(){return _heigth;};
    inline float     getDepth(){return _depth;};

    void      setSize(float size);


};