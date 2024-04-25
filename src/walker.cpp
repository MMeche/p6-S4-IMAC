#include "walker.hpp"
#include "FreeflyCamera.hpp"
#include "random.hpp"

void Walker::setCoords(glm::vec3 newCoords){
    _coords = newCoords;
};
void Walker::setVelocity(float newVelocity){
    _velocity = newVelocity;
}
glm::vec3 Walker::getCoords(){
    return _coords;
};
float Walker::getVelocity(){
    return _velocity;
};
FreeflyCamera Walker::getCamera(){
    return _camera;
}
glm::vec3 Walker::getForward(){
    return _forward;
}

Walker::Walker() : /*Wall(_coords,Wall::UI_AQUARIUMSIZE*0.1f),*/_coords{}, _velocity{0.01f}, _camera{FreeflyCamera()}, _forward{glm::vec3{0.,0.,-1.}}
{
    
    _camera.setPos(_coords+glm::vec3{0.,0.3,0.3});
};


void Walker::stayInBox(float width,float height,float depth){
    width *= Wall::UI_AQUARIUMSIZE;
    height *= Wall::UI_AQUARIUMSIZE;
    depth *= Wall::UI_AQUARIUMSIZE;
    if(_coords.x+_size >= width/2){
        _coords.x = width/2-_size;
    };
    if(_coords.x-_size <= -width/2){
        _coords.x = -width/2+_size;
    };

    if(_coords.y+_size >= height/2){
       _coords.y = height/2-_size;
    };
    if(_coords.y-_size <= -height/2){
       _coords.y = -height/2+_size;
    };
    
    if(_coords.z+_size >= depth/2){
         _coords.z = depth/2-_size;
    };
    if(_coords.z-_size <= -depth/2){
        _coords.z = -depth/2+_size;
    };
    _camera.setPos(_coords+glm::vec3{0.,0.3,0.3});
}
 void Walker::update(float size){
    stayInBox(size, size, size);
    nextKittyMarkov(_state);
    if(_state){
        _velocity = 0.02f;
    }else{
        _velocity = 0.01f;
    }
 }

void Walker::moveForward(){
    _coords += _velocity*_camera.getFront();
    _camera.moveFront(_velocity);
};

void Walker::moveBackward(){
    _coords -= _velocity*_camera.getFront();
    _camera.moveFront(-_velocity);
};

void Walker::turn(glm::vec2 mouseD,float t){
    _camera.rotateLeft(mouseD.x*t*3000);
    _camera.rotateUp(mouseD.y*t*3000);
};

void Walker::moveRight(){
    _coords -= _velocity*_camera.getLeft();
    _camera.moveLeft(-_velocity);
};

void Walker::moveLeft(){
    _coords += _velocity*_camera.getLeft();
    _camera.moveLeft(_velocity);
};