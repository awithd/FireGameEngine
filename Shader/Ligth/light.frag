uniform sampler2D img;
varying vec2 texcoord;
void main()
{
    gl_FragColor = texture2D(img, texcoord);
}

