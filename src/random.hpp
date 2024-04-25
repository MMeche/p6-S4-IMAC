#pragma once
#include <cstdlib>
#include <ctime>
#include <random>

double rand01();

int pileFace(double p);

int diceEven();

float exponentielle(float lambda);

int poiscaille(float lambda);

float normale(float mu, float sigma);

void nextKittyMarkov(bool& state);