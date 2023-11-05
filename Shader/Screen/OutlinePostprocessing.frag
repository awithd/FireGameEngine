
varying vec2        Texcoord;
uniform sampler2D   screenTexture;
uniform float       width;
uniform float       height;


void main()
{

    vec4 top         = vec4(texture2D(screenTexture, vec2(Texcoord.x, Texcoord.y + 1.0*(1.0/height))));
    vec4 bottom      = vec4(texture2D(screenTexture, vec2(Texcoord.x, Texcoord.y - 1.0*(1.0/height))));
    vec4 center      = vec4(texture2D(screenTexture, vec2(Texcoord.x, Texcoord.y)));
    vec4 left        = vec4(texture2D(screenTexture, vec2(Texcoord.x - 1.0*(1.0/width), Texcoord.y)));
    vec4 right       = vec4(texture2D(screenTexture, vec2(Texcoord.x + 1.0*(1.0/width), Texcoord.y)));

    float sy = center[1];
    float _x = Texcoord.x;
    float _y = Texcoord.y;

    if(_x==0.0){
        if(_y==0.0){
            sy += (top[1] + right[1]);
        }else if(_y==height){
            sy += (bottom[1] + right[1]);
        }else{
            sy += (top[1] + bottom[1] + right[1]);
        }
    }else if(_x==width){
        if(_y==0.0){
            sy += (top[1] + left[1]);
        }else if(_y==height){
            sy += (bottom[1] + left[1]);
        }else{
            sy += (top[1] + bottom[1] + left[1]);
        }
    }else{
        if(_y==0.0){
            sy += (top[1] + left[1] + right[1]);
        }else if(_y==height){
            sy += (bottom[1] + left[1] + right[1]);
        }else{
            sy += (top[1] + bottom[1] + left[1] + right[1]);
        }
    }

    //float sx = (top[0] + bottom[0] + left[0] + right[0]);
    //float sy = (top[1] + bottom[1] + left[1] + right[1]);
    //float sz = (top[2] + bottom[2] + left[2] + right[2]);


    //vec4 currentSampleTex = vec4(texture2D(screenTexture, Texcoord.st));

    /*if(currentSampleTex[1]==0.0){
        discard;
    }else{*/
        if(sy<=3.0 && sy>0.0){
            gl_FragColor = vec4(1, 1, 0, 1.0);
        }else{
            discard;
        }
    //}

}

