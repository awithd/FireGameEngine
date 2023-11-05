attribute vec3 VERTEX;
attribute vec3 NORMAL;
attribute vec2 TEXCOORD;
attribute vec4 JOINTS;
attribute vec4 WIGHTS;

varying vec2 TexCoords;
varying vec3 color;
varying float mode_v;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int mode;

const int MAX_BONE_INFLUENCE = 4;

uniform mat4 gBones[133];

void main()
{

    int MAX_BONES = 133;

    float w = (WIGHTS.x+WIGHTS.y+WIGHTS.z+WIGHTS.w)+0.001;

    vec4 ww = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 totalPosition = vec4(0.0);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        int b = int(JOINTS[i]);
        if( b == -1)
            continue;
        if(b >=MAX_BONES)
        {
            totalPosition = vec4(VERTEX, 1.0);
            break;
        }

        vec4 localPosition = gBones[b] * vec4(VERTEX, 1.0);
        totalPosition += localPosition * WIGHTS[i];
    }

    if(mode==0){
        TexCoords = TEXCOORD;
        color = WIGHTS.xyz;
    }
    mode_v = float(mode);

    gl_Position =  projection * view * model * totalPosition;
}

