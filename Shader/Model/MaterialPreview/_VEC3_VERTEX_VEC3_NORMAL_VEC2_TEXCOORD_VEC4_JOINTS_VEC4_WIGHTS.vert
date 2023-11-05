@version
attribute vec3 VERTEX;
attribute vec3 NORMAL;
attribute vec2 TEXCOORD;
@weights_array
@bones_array
@max_bones

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 ModelMatrix;

varying vec2 TexCoords;
varying vec3 FragPos;
varying vec3 Normal;

mat3 transpose(mat3 matrix);
float det(mat2 matrix);
mat3 inverse(mat3 matrix);

void main()
{


    vec4 totalPosition = vec4(0.0);

    @code_weight

    FragPos = vec3(ModelMatrix * vec4(VERTEX, 1.0));
    TexCoords = TEXCOORD;

    mat3 _m;
    _m[0][0] = ModelMatrix[0][0];
    _m[1][0] = ModelMatrix[1][0];
    _m[2][0] = ModelMatrix[2][0];

    _m[0][1] = ModelMatrix[0][1];
    _m[1][1] = ModelMatrix[1][1];
    _m[2][1] = ModelMatrix[2][1];

    _m[0][2] = ModelMatrix[0][2];
    _m[1][2] = ModelMatrix[1][2];
    _m[2][2] = ModelMatrix[2][2];

    mat3 mm = inverse(_m);
    Normal = transpose(mm) * NORMAL;


    gl_Position =  ModelViewProjectionMatrix * totalPosition;
}


mat3 transpose(mat3 matrix) {
    vec3 row0 = matrix[0];
    vec3 row1 = matrix[1];
    vec3 row2 = matrix[2];
    mat3 result = mat3(
        vec3(row0.x, row1.x, row2.x),
        vec3(row0.y, row1.y, row2.y),
        vec3(row0.z, row1.z, row2.z)
    );
    return result;
}

float det(mat2 matrix) {
    return matrix[0].x * matrix[1].y - matrix[0].y * matrix[1].x;
}

mat3 inverse(mat3 matrix) {
    vec3 row0 = matrix[0];
    vec3 row1 = matrix[1];
    vec3 row2 = matrix[2];

    vec3 minors0 = vec3(
        det(mat2(row1.y, row1.z, row2.y, row2.z)),
        det(mat2(row1.z, row1.x, row2.z, row2.x)),
        det(mat2(row1.x, row1.y, row2.x, row2.y))
    );
    vec3 minors1 = vec3(
        det(mat2(row2.y, row2.z, row0.y, row0.z)),
        det(mat2(row2.z, row2.x, row0.z, row0.x)),
        det(mat2(row2.x, row2.y, row0.x, row0.y))
    );
    vec3 minors2 = vec3(
        det(mat2(row0.y, row0.z, row1.y, row1.z)),
        det(mat2(row0.z, row0.x, row1.z, row1.x)),
        det(mat2(row0.x, row0.y, row1.x, row1.y))
    );

    mat3 adj = transpose(mat3(minors0, minors1, minors2));

    return (1.0 / dot(row0, minors0)) * adj;
}
