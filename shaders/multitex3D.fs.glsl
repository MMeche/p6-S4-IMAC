#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;


uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

out vec4 fFragColor;

void main()
{
    vec4 sortie = vec4(0,0,0,0);
    if(abs(vNormal_vs.x) == 1 && abs(vPosition_vs.x)==1){
        sortie += texture(uTexture1,vTexCoords);
    }
    
    if(abs(vNormal_vs.z) == 1 && abs(vPosition_vs.z)==1){
        sortie += texture(uTexture2,vTexCoords);
    }

    if(vNormal_vs.y ==-1 && vPosition_vs.y==-1){
        sortie += vec4(float(249)/255,float(194)/255,float(128)/255,1.);
    }

    if(vNormal_vs.y == 1 && vPosition_vs.y==1){
        sortie += vec4(float(84)/255,float(197)/255,float(245)/255,1.);
    }
    fFragColor = sortie;
}