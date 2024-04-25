#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "common.hpp"

std::vector<glimac::ShapeVertex> loadOBJ(const std::string& filePath);
void processFaceVertex(const std::string& vertexStr, std::vector<glimac::ShapeVertex>& vertices);

std::vector<glimac::ShapeVertex> minimalLoadOBJ(const std::string& filePath);
void minimalProcessFaceVertex(const std::string& vertexStr, std::vector<glimac::ShapeVertex>& vertices);


