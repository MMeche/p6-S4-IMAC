#include "shape_vertices.hpp"
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <vector>
#include "common.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"

namespace glimac {

std::vector<ShapeVertex> cone_vertices(float height, float radius, size_t discLat, size_t discHeight) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{

    const auto fDiscLat    = static_cast<float>(discLat);
    const auto fDiscHeight = static_cast<float>(discHeight);

    const float phi = 2.f * glm::pi<float>() / fDiscLat;
    const float h   = height / fDiscHeight;

    std::vector<ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discHeight; ++j)
    {
        for (size_t i = 0; i < discLat; ++i)
        {
            const auto fj = static_cast<float>(j);
            const auto fi = static_cast<float>(i);

            ShapeVertex vertex{};
            vertex.texCoords.x = fi / fDiscLat;
            vertex.texCoords.y = fj / fDiscHeight;

            vertex.position.x = radius * (height - fj * h) * std::sin(fi * phi) / height;
            vertex.position.y = fj * h;
            vertex.position.z = radius * (height - fj * h) * std::cos(fi * phi) / height;

            vertex.normal.x = std::sin(fi * phi);
            vertex.normal.y = radius / height;
            vertex.normal.z = std::cos(fi * phi);
            vertex.normal   = glm::normalize(vertex.normal);

            data.push_back(vertex);
        }
    }

    std::vector<ShapeVertex> vertices{};
    // Construit les vertex finaux en regroupant les données en triangles :
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme :
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for (size_t j = 0; j < discHeight; ++j)
    {
        const size_t offset = j * discLat;
        for (size_t i = 0; i < discLat; ++i)
        {
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + (i + 1) % discLat]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i + discLat]);
        }
    }

    return vertices;
}

std::vector<ShapeVertex> cube_vertices(float size){
    std::vector<ShapeVertex> vertices;

    std::vector<glm::vec3> positions = {
        {-size, -size, -size}, 
        {-size, -size, size},  
        {-size, size, -size},  
        {-size, size, size}, 

        {size, -size, -size},  
        {size, -size, size},   
        {size, size, -size},   
        {size, size, size}     
    };
    std::vector<glm::vec<4,int,glm::defaultp>> faces = {
        {0, 1, 3, 2}, // Front
        {1, 5, 7, 3}, // Right
        {5, 4, 6, 7}, // Back
        {4, 0, 2, 6}, // Left
        {2, 3, 7, 6}, // Top
        {4, 5, 1, 0}  // Bottom
    };    

    std::vector<glm::vec2> texCoords = {
        {0,0},{1,0},{1,1},{0,1} //Same for every faces
    };

    std::vector<glm::vec3> normals = {
        {1, 0, 0}, // Front
        {0, 0, -1},  // Right
        {-1, 0, 0},  // Back
        {0, 0, 1}, // Left
        {0, 1, 0},  // Top
        {0, -1, 0}  // Bottom
    };

    for(size_t i = 0; i < faces.size(); i++){
        const auto& face = faces[i];
        const auto& normal = normals[i];
        
        for(size_t j = 0 ; j < 6 ; j++){
            ShapeVertex vertex;
            if(j<4){
            vertex.position = positions[face[j]];
            vertex.texCoords = texCoords[j];
            }
            if(j==4){
                vertex.position = positions[face[0]];
                vertex.texCoords = texCoords[0];
            }
            if(j==5){
                vertex.position = positions[face[2]];
                vertex.texCoords = texCoords[2];
            }
            vertex.normal = normal;
            vertices.push_back(vertex);
        }
    }
    return vertices;
}

} // namespace glimac
