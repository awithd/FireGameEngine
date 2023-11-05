attribute vec3 VERTEX;
attribute vec3 NORMAL;
attribute vec2 TEXCOORD;
attribute vec4 JOINTS;
attribute vec4 WIGHTS;

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 gBones[133];

const int MAX_BONE_INFLUENCE = 4;


void main()
{

    int MAX_BONES = 133;

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


    gl_Position =  ModelViewProjectionMatrix * totalPosition;
}

