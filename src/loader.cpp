#include "loader.hpp"


void processFaceVertex(const std::string& vertexStr, std::vector<glimac::ShapeVertex>& vertices) {
    std::istringstream vStream(vertexStr);
    unsigned int vertexIndex, texCoordIndex, normalIndex;
    char slash;
    vStream >> vertexIndex >> slash >> texCoordIndex >> slash >> normalIndex;
    
    // Adjust indices to 0-based
    vertexIndex--;
    texCoordIndex--;
    normalIndex--;

    // Create ShapeVertex and add to vertices vector
    glimac::ShapeVertex ShapeVertex;
    ShapeVertex.position = vertices[vertexIndex].position;
    ShapeVertex.normal = vertices[normalIndex].normal;
    ShapeVertex.texCoords = vertices[texCoordIndex].texCoords;
    vertices.push_back(ShapeVertex);
}

std::vector<glimac::ShapeVertex> loadOBJ(const std::string& filePath) {
    std::vector<glimac::ShapeVertex> vertices;
    
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier OBJ : " << filePath << std::endl;
        return vertices;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            glimac::ShapeVertex ShapeVertex;
            ShapeVertex.position = vertex;
            vertices.push_back(ShapeVertex);
        } else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            vertices.back().normal = normal;
        } else if (type == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            vertices.back().texCoords = texCoord;
        } else if (type == "f") {
            
            std::string vertex1, vertex2, vertex3, vertex4;
            iss >> vertex1 >> vertex2 >> vertex3 >> vertex4;
            
            // First triangle
            processFaceVertex(vertex1, vertices);
            processFaceVertex(vertex2, vertices);
            processFaceVertex(vertex3, vertices);

            // Second triangle
            processFaceVertex(vertex1, vertices);
            processFaceVertex(vertex3, vertices);
            processFaceVertex(vertex4, vertices);
        }
    }
    
    file.close();
    
    return vertices;
}

void minimalProcessFaceVertex(const std::string& vertexStr, std::vector<glimac::ShapeVertex>& vertices) {
    std::istringstream vStream(vertexStr);
    unsigned int vertexIndex,normalIndex;
    char slash;
    vStream >> vertexIndex >> slash >> slash >> normalIndex;
    
    // Adjust indices to 0-based
    vertexIndex--;
    normalIndex--;

    // Create ShapeVertex and add to vertices vector
    glimac::ShapeVertex ShapeVertex;
    ShapeVertex.position = vertices[vertexIndex].position;
    ShapeVertex.normal = vertices[normalIndex].normal;
    ShapeVertex.texCoords = glm::vec2{0,0};;
    vertices.push_back(ShapeVertex);
}

std::vector<glimac::ShapeVertex> minimalLoadOBJ(const std::string& filePath) {
    std::vector<glimac::ShapeVertex> vertices;
    
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier OBJ : " << filePath << std::endl;
        return vertices;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            glimac::ShapeVertex ShapeVertex;
            ShapeVertex.position = vertex;
            vertices.push_back(ShapeVertex);
        } else if (type == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            vertices.back().normal = normal;
        } else if (type == "vt") {
            glm::vec2 texCoord;
            iss >> texCoord.x >> texCoord.y;
            vertices.back().texCoords = texCoord;
        } else if (type == "f") {
            
            std::string vertex1, vertex2, vertex3, vertex4;
            iss >> vertex1 >> vertex2 >> vertex3 >> vertex4;
            
            // First triangle
            minimalProcessFaceVertex(vertex1, vertices);
            minimalProcessFaceVertex(vertex2, vertices);
            minimalProcessFaceVertex(vertex3, vertices);

            // Second triangle
            minimalProcessFaceVertex(vertex1, vertices);
            minimalProcessFaceVertex(vertex3, vertices);
            minimalProcessFaceVertex(vertex4, vertices);
        }
    }
    
    file.close();
    
    return vertices;
}