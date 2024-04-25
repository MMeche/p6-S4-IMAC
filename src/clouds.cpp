#include "clouds.hpp"
#include "random.hpp"

//Didn't make it in time
void Clouds::addCloud(){
    glm::vec3 newPos{-1.,0.5+0.5*rand01(),rand_11()};
    _clouds.push_back(newPos);

};
void Clouds::deleteCloud(int index){
    _clouds[index] = _clouds.back();
    _clouds.pop_back();
};
void Clouds::updateCloud(){
    for(size_t i = 0 ; i < _clouds.size() ; i++){
        _clouds[i] += _wind;
        if(_clouds[i].length()>4){
            deleteCloud(i);
        }
    }
}
Clouds::Clouds(){
    addCloud();
    
};