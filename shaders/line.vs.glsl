#version 330 core

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position du sommet

// Matrices de transformation reçues en uniform
uniform mat4 uMVPMatrix;


void main() {
    // Passage en coordonnées homogènes
    vec4 vertexPosition = vec4(aVertexPosition, 1.);

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}