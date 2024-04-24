#include "FreeflyCamera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"

void FreeflyCamera::computeDirectionVectors(){
    _FrontVector = glm::vec3{
        glm::cos(_Theta)*glm::sin(_Phi),
        glm::sin(_Theta),
        glm::cos(_Theta)*glm::cos(_Phi)};
    
    _LeftVector = glm::vec3{
        glm::sin(_Phi+glm::pi<float>()/2),
        0,
        glm::cos(_Phi+glm::pi<float>()/2)};

    _UpVector = glm::cross(_FrontVector,_LeftVector);
};

FreeflyCamera::FreeflyCamera() : _position{glm::vec3{0}}, _Phi{glm::pi<float>()}, _Theta(0)
{
    computeDirectionVectors();
};

glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(_position, _position+_FrontVector, _UpVector);
};

void FreeflyCamera::setPos(glm::vec3 newPos){
    _position = newPos;
};

void FreeflyCamera::rotateLeft(float degrees){
    _Phi += glm::radians(degrees);
    computeDirectionVectors();
};
void FreeflyCamera::rotateUp(float degrees){
    _Theta += glm::radians(degrees);
    computeDirectionVectors();
};
