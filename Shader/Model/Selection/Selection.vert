#version 330
layout (location = 1) in float ID;
layout (location = 2) in vec3 VERTEX;

@weights_array

@bones_array

uniform mat4 ModelViewProjectionMatrix;


void main()
{


    vec4 totalPosition = vec4(0.0);

    @code_weight



    gl_Position =  ModelViewProjectionMatrix * totalPosition;
}
