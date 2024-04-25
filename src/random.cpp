#include "random.hpp"
#include <cmath>

// the brick de base
double rand01() {
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto distrib = std::uniform_real_distribution<double>{0.0, 1.0};

    return distrib(gen);
}

// Even dice
int diceEven() {
    return 1+floor(6*rand01());
}

// 1 for pile or 0 for face
int pileFace(double p){
    if(p>1){
        return -1;
    }
    double pf = rand01();
    return pf<p ? 1 : 0;
}


//Exponential
float exponentielle(float lambda){
    return -std::log(rand01())/lambda;
}

//Poiscaille
int poiscaille(float lambda){
    int N{};
    float Tn{exponentielle(lambda)};
    while(Tn<=1)
    {
        N++;
        Tn += exponentielle(lambda);
    }
    return N;
}

float normale(float mu, float sigma){
    double u1 = rand01();
    double u2 = rand01();
    double z1 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mu + z1 * sigma;
};

// Kitty Markov
// There is two state of the cat : 
// false he is pretty normal you know vibing and all ... 
// true he is abnormally excited as if he consummed cocaine straight in his nose.
void nextKittyMarkov(bool& state){
    float U = rand01();
    if(state && U>0.9){
        state = false;
    }
    if(!state && U>0.99)
    {
        state = true;
    }
};

