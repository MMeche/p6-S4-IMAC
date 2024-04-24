#pragma once
#include "p6/p6.h"

class FreeflyCamera {
    private :
    glm::vec3 _position;
    float _Phi;
    float _Theta;
    glm::vec3 _FrontVector;
    glm::vec3 _LeftVector;
    glm::vec3 _UpVector;
    
    void computeDirectionVectors();
    
    public:
    
    FreeflyCamera();
    inline void moveLeft(float t){_position += t*_LeftVector;};
    inline void moveFront(float t){_position += t*_FrontVector;};
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    
    void setPos(glm::vec3 newPos);
    inline glm::vec3 getPos(){return _position;};
    inline glm::vec3 getFront(){return _FrontVector;};
    inline glm::vec3 getLeft(){return _LeftVector;};
    inline glm::vec3 getUp(){return _UpVector;};
    glm::mat4 getViewMatrix() const;
};