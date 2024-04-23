#include "obstacles.hpp"
#include <iostream>

float Wall::UI_AQUARIUMSIZE = 1.;

void Wall::setSize(float size){
    _width  = size;
    _heigth = size;
    _depth  = size;
}