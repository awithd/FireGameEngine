#version 420

layout (location = 1) in  vec3 VERTEX;
layout (location = 2) in float WEIGHT0;
layout (location = 3) in float WEIGHT1;
layout (location = 4) in float WEIGHT2;

uniform mat4 ModelViewProjectionMatrix;

out float _WEIGHT0;
out float _WEIGHT1;
out float _WEIGHT2;

void main()
{
    _WEIGHT0 = WEIGHT0;
    _WEIGHT1 = WEIGHT1;
    _WEIGHT2 = WEIGHT2;

    gl_Position =  ModelViewProjectionMatrix * vec4(VERTEX, 1.0);
}
