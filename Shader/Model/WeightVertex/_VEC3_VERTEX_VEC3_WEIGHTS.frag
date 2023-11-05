#version 420
in float _WEIGHT0;
in float _WEIGHT1;
in float _WEIGHT2;

out vec4 FragColor;

void main(void)
{
    FragColor = vec4(_WEIGHT0, _WEIGHT1, _WEIGHT2, 1);
}
