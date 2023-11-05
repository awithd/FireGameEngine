#version 330

layout (location = 1) in float ID;
layout (location = 2) in vec3 VERTEX;

@weights_array

@bones_array

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelMatrix;
uniform int mode;

varying float IDLINE;

void main()
{
    vec4 totalPosition = vec4(0.0);

    @code_weight

    gl_Position =  ModelViewProjectionMatrix * totalPosition;
    if(mode==3 || mode==0){
        IDLINE = ID;
    }
}
