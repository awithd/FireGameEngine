#version 330

layout (location = 1) in float ID;
layout (location = 2) in vec3 VERTEX;


@weights_array

@bones_array

uniform mat4 ModelViewProjectionMatrix;
uniform int bone;
uniform int black;

varying vec3 color;

float hue2rgb(float f1, float f2, float hue) {
    if (hue < 0.0)
        hue += 1.0;
    else if (hue > 1.0)
        hue -= 1.0;
    float res;
    if ((6.0 * hue) < 1.0)
        res = f1 + (f2 - f1) * 6.0 * hue;
    else if ((2.0 * hue) < 1.0)
        res = f2;
    else if ((3.0 * hue) < 2.0)
        res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
    else
        res = f1;
    return res;
}

vec3 hsl2rgb(vec3 hsl) {
    vec3 rgb;

    if (hsl.y == 0.0) {
        rgb = vec3(hsl.z); // Luminance
    } else {
        float f2;

        if (hsl.z < 0.5)
            f2 = hsl.z * (1.0 + hsl.y);
        else
            f2 = hsl.z + hsl.y - hsl.y * hsl.z;

        float f1 = 2.0 * hsl.z - f2;

        rgb.r = hue2rgb(f1, f2, hsl.x + (1.0/3.0));
        rgb.g = hue2rgb(f1, f2, hsl.x);
        rgb.b = hue2rgb(f1, f2, hsl.x - (1.0/3.0));
    }
    return rgb;
}

vec3 Gradient (float param)
{
    param = clamp(param, 0, 1);

    // we are treating these colors as HSL now:
    vec3 ColorA =vec3(0.0, 0.5, 0.5);
    vec3 ColorB =vec3(1.0, 0.5, 0.5);

    // so now we need to convert them to plain old RGB
    // note how the blending equation remains the same
    return hsl2rgb(param * ColorA + (1-param) * ColorB); // simple blending equation
}



void main()
{
    vec4 totalPosition = vec4(0.0);
    color = vec3(0.0,0.0,0.0);

    float param = 0;

    @code_weight



    if(black==0.0){
        //color = vec4(Gradient(param), 1.0);
        if (param <= 0.5) {
                color = mix(vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0), param * 2.0);
            } else {
                color = mix(vec3(0.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), (param - 0.5) * 2.0);
            }
    }else{
        color = vec3(0.0, 0.0, 0.0);
    }
    gl_Position =  ModelViewProjectionMatrix * totalPosition;
    //color = vec4(1,1,0,1);
}
