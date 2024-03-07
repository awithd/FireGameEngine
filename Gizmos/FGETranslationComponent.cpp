#include "FGETranslationComponent.h"

FGETranslationComponent::FGETranslationComponent()
{

    gizmo_rotation = new FGERotationGizmo();
    gizmo_rotation->color_x = glm::vec3(0.91, 0.17, 0.29);
    gizmo_rotation->color_y = glm::vec3(0.13, 0.77, 0.52);
    gizmo_rotation->color_z = glm::vec3(0.11, 0.33, 0.76);
    gizmo_rotation->color_w = glm::vec3(0.96, 0.96, 0.96);
    gizmo_rotation->color_c = glm::vec3(0.96, 0.96, 0.96);

    gizmo_rotation->source_vertex_shader =
                "attribute vec3 vertex;"
                "attribute vec3 normal;"
                "uniform vec3 color;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "varying vec3 _color;"
                "varying vec3 _normal;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "   vec4 n = projection * view * model * vec4(normal, 1.0);"
                "   _color = color;"
                "   _normal = n.xyz;"
                "}";

    gizmo_rotation->source_fragment_shader =
                "varying vec3 _color;"
                "uniform float blend;"
                "varying vec3 _normal;"
                "void main()"
                "{"
                "   float r = dot(_normal, vec3(0.0,0.0,1.0));"
                "   r = acos(r);"
                "   r = (r*180.0)/3.14159265358979323846;"
                "   if(r<90.0 && r>-90.0){"
                "       discard;"
                "   }else{"
                "       gl_FragColor = vec4(_color, blend);"
                "   }"
                "}";
    gizmo_rotation->source_fragment_shader_selection =
                "varying vec3 _color;"
                "varying vec3 _normal;"
                "void main()"
                "{"
                "   float r = dot(_normal, vec3(0.0,0.0,1.0));"
                "   r = acos(r);"
                "   r = (r*180.0)/3.14159265358979323846;"
                "   if(r<90.0 && r>-90.0){"
                "       discard;"
                "   }else{"
                "       gl_FragColor = vec4(_color, 1.0);"
                "   }"
                "}";
/*"varying vec3 _color;"
                "varying vec3 _normal;"
                "void main()"
                "{"
                "   float r = dot(_normal, vec3(0.0,0.0,1.0));"
                "   r = acos(r);"
                "   r = (r*180.0)/3.14159265358979323846;"
                "   vec3 v = cross(_normal, vec3(0.0,0.0,1.0));"
                "   if(v[2]<0.0) r = 360.0-r;"
                "   if(r<20.0 && r>180.0){"
                "       discard;"
                "   }else{"
                "       gl_FragColor = vec4(_color, blend);"
                "   }"
                "}";*/
    gizmo_rotation->axe_source_vertex_shader =
                "attribute vec3 vertex;"
                "uniform vec3 color;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "varying vec3 _color;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "   _color = color;"
                "}";

    gizmo_rotation->axe_source_fragment_shader =
                "varying vec3 _color;"
                "void main()"
                "{"
                "   gl_FragColor = vec4(_color, 1.0);"
                "}";

    gizmo_rotation->svsc =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    gizmo_rotation->sfsc =
                "uniform vec3 color;"
                "uniform vec3 center;"
                "void main()"
                "{"
                "   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));"
                "   gl_FragColor = vec4(color.xyz, 0.2);"
                "   else if(f>=70.0 && f<70.5) gl_FragColor = vec4(color.xyz, 0.1);"
                "   else if(f>=70.5 && f<70.8) gl_FragColor = vec4(color.xyz, 0.05);"
                "   else discard;"
                "}";
    gizmo_rotation->svsw =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    gizmo_rotation->sfsw =
                "uniform vec3 color;"
                "uniform vec3 center;"
                "void main()"
                "{"
                "   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));"
                "   if(f < 90.0) discard;"
                "   else if(f>=90.0 && f<90.3) gl_FragColor = vec4(color.xyz, 0.2);"
                "   else if(f>=90.3 && f<90.8) gl_FragColor = vec4(color.xyz, 0.5);"
                "   else if(f>=90.8 && f<93.0) gl_FragColor = vec4(color.xyz, 1.0);"
                "   else if(f>=93.0 && f<93.5) gl_FragColor = vec4(color.xyz, 0.5);"
                "   else if(f>=93.5 && f<93.8) gl_FragColor = vec4(color.xyz, 0.2);"
                "   else discard;"
                "}";

    gizmo_rotation->selection_svsc =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    gizmo_rotation->selection_sfsc =
                "uniform vec3 color;"
                "uniform vec3 center;"
                "void main()"
                "{"
                "   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));"
                "   if(f < 70.8) gl_FragColor = vec4(color.xyz, 1.0);"
                "   else discard;"
                "}";

    gizmo_rotation->selection_svsw =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    gizmo_rotation->selection_sfsw =
                "uniform vec3 color;"
                "uniform vec3 center;"
                "void main()"
                "{"
                "   float f = sqrt((gl_FragCoord.x-center.x)*(gl_FragCoord.x-center.x)+(gl_FragCoord.y-center.y)*(gl_FragCoord.y-center.y));"
                "   if(f < 90.0) discard;"
                "   else if(f>=90.0 && f<93.8) gl_FragColor = vec4(color.xyz, 1.0);"
                "   else discard;"
                "}";

    gizmo_rotation->lines.source_vertex_shader =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "   gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    gizmo_rotation->lines.source_fragment_shader =
                "uniform vec3 color;"
                "void main()"
                "{"
                "   gl_FragColor = vec4(color.xyz, 1.0);"
                "}";


    initMeshGizmoRotation(0.003);
    createCircle(0.0005);
    createMeshTranslate(0.0005, 0.00006);
    createMeshXYZTranslateForSelection(0.0005, 0.0003);
    initShader();
    initBuffer();
    initBufferXYZAxes();

    drag_selected = false;
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;

    current_transformation_mode = 0;

    points = glm::vec3(0.0f, 0.0f, 0.0f);
    points_2 = glm::vec3(0.0f, 0.0f, 0.0f);
    points_3 = glm::vec3(0.0f, 0.0f, 0.0f);
    _t3d1 = glm::vec3(0.0f, 0.0f, 0.0f);

}
FGETranslationComponent::~FGETranslationComponent()
{
    glDeleteVertexArrays(1, &vao_a);
    glDeleteVertexArrays(1, &vao_ya);
    glDeleteVertexArrays(1, &vao_za);
    glDeleteVertexArrays(1, &vao_a);
    glDeleteVertexArrays(1, &vao_c);
    glDeleteBuffers(1, &vbo_xa);
    glDeleteBuffers(1, &vbo_ya);
    glDeleteBuffers(1, &vbo_za);
    glDeleteBuffers(1, &vbo_a);
    glDeleteBuffers(1, &vbo_c);
    glDeleteProgram(shaderProgram_c_translate);
    glDeleteProgram(shaderProgram_xyz_translate);
    glDeleteProgram(shaderProgram_selection);

}


void FGETranslationComponent::initBuffer(){

    //////
    {
        glGenVertexArrays(1, &vao_a);
        glGenBuffers(1, &vbo_a);
        glGenVertexArrays(1, &vao_c);
        glGenBuffers(1, &vbo_c);

        //qDebug() << " sizeof(xyz_translate) " << sizeof(xyz_translate);

        glBindVertexArray(vao_a);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_a);
        glBufferData(GL_ARRAY_BUFFER, sizeof(xyz_translate), xyz_translate, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //qDebug() << " sizeof(circle_translate) " << sizeof(circle_translate);

        glBindVertexArray(vao_c);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_c);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circle_translate), circle_translate, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        glGenVertexArrays(1, &vao_xa);
        glGenVertexArrays(1, &vao_ya);
        glGenVertexArrays(1, &vao_za);
        glGenBuffers(1, &vbo_xa);
        glGenBuffers(1, &vbo_ya);
        glGenBuffers(1, &vbo_za);

        glBindVertexArray(vao_xa);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_xa);
        glBufferData(GL_ARRAY_BUFFER, sizeof(x_translate), x_translate, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glBindVertexArray(vao_ya);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ya);
        glBufferData(GL_ARRAY_BUFFER, sizeof(y_translate), y_translate, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glBindVertexArray(vao_za);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_za);
        glBufferData(GL_ARRAY_BUFFER, sizeof(z_translate), z_translate, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ////////////////////////////////    init buffer gizmo rotation
    {
        glGenVertexArrays(1, &gizmo_rotation->vao_x);
        glGenBuffers(1, &gizmo_rotation->vbo_x);
        glBindVertexArray(gizmo_rotation->vao_x);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->vbo_x);
        glBufferData(GL_ARRAY_BUFFER, 360*6*sizeof(float), &gizmo_rotation->mesh_x[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenVertexArrays(1, &gizmo_rotation->vao_y);
        glGenBuffers(1, &gizmo_rotation->vbo_y);
        glBindVertexArray(gizmo_rotation->vao_y);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->vbo_y);
        glBufferData(GL_ARRAY_BUFFER, 360*6*sizeof(float), &gizmo_rotation->mesh_y[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenVertexArrays(1, &gizmo_rotation->vao_z);
        glGenBuffers(1, &gizmo_rotation->vbo_z);
        glBindVertexArray(gizmo_rotation->vao_z);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->vbo_z);
        glBufferData(GL_ARRAY_BUFFER, 360*6*sizeof(float), &gizmo_rotation->mesh_z[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenVertexArrays(1, &gizmo_rotation->vao_c);
        glGenBuffers(1, &gizmo_rotation->vbo_c);
        glBindVertexArray(gizmo_rotation->vao_c);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->vbo_c);
        glBufferData(GL_ARRAY_BUFFER, 108*sizeof(float), &gizmo_rotation->mesh_c[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenVertexArrays(1, &gizmo_rotation->vao_w);
        glGenBuffers(1, &gizmo_rotation->vbo_w);
        glBindVertexArray(gizmo_rotation->vao_w);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->vbo_w);
        glBufferData(GL_ARRAY_BUFFER, 108*sizeof(float), &gizmo_rotation->mesh_w[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glGenVertexArrays(1, &gizmo_rotation->lines.vao);
        glGenBuffers(1, &gizmo_rotation->lines.vbo);
        glBindVertexArray(gizmo_rotation->lines.vao);
        glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->lines.vbo);
        glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), NULL, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    glGenVertexArrays(1, &vao_points);
    glGenBuffers(1, &vbo_points);
    glBindVertexArray(vao_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float), NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void FGETranslationComponent::initMeshGizmoRotation(float r)
{
    //r -= 0.0001;
    float nr = r+0.01;
    gizmo_rotation->diameter = r;
    gizmo_rotation->diameter_after_scale = r;

    for (int i = 0; i < 360; i++)   {
        float theta = 2.0f * 3.1415926f * float(i+1) / float(360);//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        float nx = nr * cos(theta)-x;
        float ny = nr * sin(theta)-y;

        gizmo_rotation->mesh_x[i*6] = 0.0;
        gizmo_rotation->mesh_x[i*6+1] = x;
        gizmo_rotation->mesh_x[i*6+2] = y;

        glm::vec3 _n = glm::normalize(glm::vec3(0.0, nx, ny));
        gizmo_rotation->mesh_x[i*6+3] = _n[0];
        gizmo_rotation->mesh_x[i*6+4] = _n[1];
        gizmo_rotation->mesh_x[i*6+5] = _n[2];

    }
    //r -= 0.0001;
    for (int i = 0; i < 360; i++)   {
        float theta = 2.0f * 3.1415926f * float(i+1) / float(360);//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        float nx = nr * cos(theta)-x;
        float ny = nr * sin(theta)-y;
        gizmo_rotation->mesh_y[i*6] = x;
        gizmo_rotation->mesh_y[i*6+1] = 0.0;
        gizmo_rotation->mesh_y[i*6+2] = y;

        glm::vec3 _n = glm::normalize(glm::vec3(nx, 0.0, ny));
        gizmo_rotation->mesh_y[i*6+3] = _n[0];
        gizmo_rotation->mesh_y[i*6+4] = _n[1];
        gizmo_rotation->mesh_y[i*6+5] = _n[2];

    }
    //r -= 0.0001;
    for (int i = 0; i < 360; i++)   {
        float theta = 2.0f * 3.1415926f * float(i+1) / float(360);//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        float nx = nr * cos(theta)-x;
        float ny = nr * sin(theta)-y;
        gizmo_rotation->mesh_z[i*6] = x;
        gizmo_rotation->mesh_z[i*6+1] = y;
        gizmo_rotation->mesh_z[i*6+2] = 0.0;

        glm::vec3 _n = glm::normalize(glm::vec3(nx, ny, 0.0));
        gizmo_rotation->mesh_z[i*6+3] = _n[0];
        gizmo_rotation->mesh_z[i*6+4] = _n[1];
        gizmo_rotation->mesh_z[i*6+5] = _n[2];

    }
    float q = r+0.001;

    GLfloat vertices[] = {
        -q, -q, -q,
         q, -q, -q,
         q,  q, -q,
         q,  q, -q,
        -q,  q, -q,
        -q, -q, -q,

        -q, -q,  q,
         q, -q,  q,
         q,  q,  q,
         q,  q,  q,
        -q,  q,  q,
        -q, -q,  q,

        -q,  q,  q,
        -q,  q, -q,
        -q, -q, -q,
        -q, -q, -q,
        -q, -q,  q,
        -q,  q,  q,

         q,  q,  q,
         q,  q, -q,
         q, -q, -q,
         q, -q, -q,
         q, -q,  q,
         q,  q,  q,

        -q, -q, -q,
         q, -q, -q,
         q, -q,  q,
         q, -q,  q,
        -q, -q,  q,
        -q, -q, -q,

        -q,  q, -q,
         q,  q, -q,
         q,  q,  q,
         q,  q,  q,
        -q,  q,  q,
        -q,  q, -q
    };

    for (int i = 0; i < 108; i++)   {
        gizmo_rotation->mesh_c[i] = vertices[i];
    }

    for (int i = 0; i < 108; i++)   {
        gizmo_rotation->mesh_w[i] = vertices[i];
    }

}


void FGETranslationComponent::createCircle(float r)
{
    for (int ii = 0; ii < 36; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(36);//get the current angle
        float x = r * cos(theta);//calculate the x component
        float y = r * sin(theta);//calculate the y component
        circle_translate[ii*3] = x;
        circle_translate[ii*3+1] = y;
        circle_translate[ii*3+2] = 0;
    }
}

void FGETranslationComponent::createMeshTranslate(float r, float k)
{

    int d = 0;
    int i=0;

    float w_a = 0.004, w_c = 0.001;

    float _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    float _x = r * cos(_theta);//calculate the x component
    float _y = r * sin(_theta);//calculate the y component

    float o_x = _x, o_y = _y, x, y;

    for (int ii = 1; ii < 8; ii++)   {

        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        xyz_translate[d+ii*18]   = w_a;
        xyz_translate[d+ii*18+1] = _x;
        xyz_translate[d+ii*18+2] = _y;

        xyz_translate[d+ii*18+3] = 1.0;
        xyz_translate[d+ii*18+4] = 0.0;
        xyz_translate[d+ii*18+5] = 0.0;

        xyz_translate[d+ii*18+6] = w_a+w_c;
        xyz_translate[d+ii*18+7] = 0.0;
        xyz_translate[d+ii*18+8] = 0.0;

        xyz_translate[d+ii*18+9] = 1.0;
        xyz_translate[d+ii*18+10] = 0.0;
        xyz_translate[d+ii*18+11] = 0.0;

        xyz_translate[d+ii*18+12] = w_a;
        xyz_translate[d+ii*18+13] = x;
        xyz_translate[d+ii*18+14] = y;

        xyz_translate[d+ii*18+15] = 1.0;
        xyz_translate[d+ii*18+16] = 0.0;
        xyz_translate[d+ii*18+17] = 0.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d+0] = w_a;
    xyz_translate[d+1] = _x;
    xyz_translate[d+2] = _y;

    xyz_translate[d+3] = 1.0;
    xyz_translate[d+4] = 0.0;
    xyz_translate[d+5] = 0.0;

    xyz_translate[d+6] = w_a+w_c;
    xyz_translate[d+7] = 0.0;
    xyz_translate[d+8] = 0.0;

    xyz_translate[d+9]  = 1.0;
    xyz_translate[d+10] = 0.0;
    xyz_translate[d+11] = 0.0;

    xyz_translate[d+12] = w_a;
    xyz_translate[d+13] = o_x;
    xyz_translate[d+14] = o_y;

    xyz_translate[d+15] = 1.0;
    xyz_translate[d+16] = 0.0;
    xyz_translate[d+17] = 0.0;

    d = 144;

    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        xyz_translate[d+ii*36]   = 0.0;
        xyz_translate[d+ii*36+1] = _x;
        xyz_translate[d+ii*36+2] = _y;

        xyz_translate[d+ii*36+3] = 1.0;
        xyz_translate[d+ii*36+4] = 0.0;
        xyz_translate[d+ii*36+5] = 0.0;

        xyz_translate[d+ii*36+6] = w_a;
        xyz_translate[d+ii*36+7] = _x;
        xyz_translate[d+ii*36+8] = _y;

        xyz_translate[d+ii*36+9] = 1.0;
        xyz_translate[d+ii*36+10] = 0.0;
        xyz_translate[d+ii*36+11] = 0.0;

        xyz_translate[d+ii*36+12] = 0.0;
        xyz_translate[d+ii*36+13] = x;
        xyz_translate[d+ii*36+14] = y;

        xyz_translate[d+ii*36+15] = 1.0;
        xyz_translate[d+ii*36+16] = 0.0;
        xyz_translate[d+ii*36+17] = 0.0;


        ////////////////////////

        xyz_translate[d+ii*36+18] = 0.0;
        xyz_translate[d+ii*36+19] = x;
        xyz_translate[d+ii*36+20] = y;


        xyz_translate[d+ii*36+21] = 1.0;
        xyz_translate[d+ii*36+22] = 0.0;
        xyz_translate[d+ii*36+23] = 0.0;

        xyz_translate[d+ii*36+24] = w_a;
        xyz_translate[d+ii*36+25] = x;
        xyz_translate[d+ii*36+26] = y;

        xyz_translate[d+ii*36+27] = 1.0;
        xyz_translate[d+ii*36+28] = 0.0;
        xyz_translate[d+ii*36+29] = 0.0;

        xyz_translate[d+ii*36+30] = w_a;
        xyz_translate[d+ii*36+31] = _x;
        xyz_translate[d+ii*36+32] = _y;

        xyz_translate[d+ii*36+33] = 1.0;
        xyz_translate[d+ii*36+34] = 0.0;
        xyz_translate[d+ii*36+35] = 0.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d] = 0.0;
    xyz_translate[d+1] = _x;
    xyz_translate[d+2] = _y;

    xyz_translate[d+3] = 1.0;
    xyz_translate[d+4] = 0.0;
    xyz_translate[d+5] = 0.0;

    xyz_translate[d+6] = w_a;
    xyz_translate[d+7] = _x;
    xyz_translate[d+8] = _y;

    xyz_translate[d+9]  = 1.0;
    xyz_translate[d+10] = 0.0;
    xyz_translate[d+11] = 0.0;

    xyz_translate[d+12] = 0.0;
    xyz_translate[d+13] = o_x;
    xyz_translate[d+14] = o_y;

    xyz_translate[d+15] = 1.0;
    xyz_translate[d+16] = 0.0;
    xyz_translate[d+17] = 0.0;

    /////

    xyz_translate[d+18] = 0.0;
    xyz_translate[d+19] = _x;
    xyz_translate[d+20] = _y;

    xyz_translate[d+21] = 1.0;
    xyz_translate[d+22] = 0.0;
    xyz_translate[d+23] = 0.0;

    xyz_translate[d+24] = w_a;
    xyz_translate[d+25] = _x;
    xyz_translate[d+26] = _y;

    xyz_translate[d+27] = 1.0;
    xyz_translate[d+28] = 0.0;
    xyz_translate[d+29] = 0.0;

    xyz_translate[d+30] = 0.0;
    xyz_translate[d+31] = o_x;
    xyz_translate[d+32] = o_y;

    xyz_translate[d+33] = 1.0;
    xyz_translate[d+34] = 0.0;
    xyz_translate[d+35] = 0.0;



    ///////////////////////////////////////////////////////////////////////////

    d = d+288;

    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = r * cos(_theta);//calculate the x component
    _y = r * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {

        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        xyz_translate[d+ii*18]   = _x;
        xyz_translate[d+ii*18+1] = w_a;
        xyz_translate[d+ii*18+2] = _y;

        xyz_translate[d+ii*18+3] = 0.0;
        xyz_translate[d+ii*18+4] = 1.0;
        xyz_translate[d+ii*18+5] = 0.0;

        xyz_translate[d+ii*18+6] = 0.0;
        xyz_translate[d+ii*18+7] = w_a+w_c;
        xyz_translate[d+ii*18+8] = 0.0;

        xyz_translate[d+ii*18+9] = 0.0;
        xyz_translate[d+ii*18+10] = 1.0;
        xyz_translate[d+ii*18+11] = 0.0;

        xyz_translate[d+ii*18+12] = x;
        xyz_translate[d+ii*18+13] = w_a;
        xyz_translate[d+ii*18+14] = y;

        xyz_translate[d+ii*18+15] = 0.0;
        xyz_translate[d+ii*18+16] = 1.0;
        xyz_translate[d+ii*18+17] = 0.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d+0] = _x;
    xyz_translate[d+1] = w_a;
    xyz_translate[d+2] = _y;

    xyz_translate[d+3] = 0.0;
    xyz_translate[d+4] = 1.0;
    xyz_translate[d+5] = 0.0;

    xyz_translate[d+6] = 0.0;
    xyz_translate[d+7] = w_a+w_c;
    xyz_translate[d+8] = 0.0;

    xyz_translate[d+9]  = 0.0;
    xyz_translate[d+10] = 1.0;
    xyz_translate[d+11] = 0.0;

    xyz_translate[d+12] = o_x;
    xyz_translate[d+13] = w_a;
    xyz_translate[d+14] = o_y;

    xyz_translate[d+15] = 0.0;
    xyz_translate[d+16] = 1.0;
    xyz_translate[d+17] = 0.0;

    d = d+144;
    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;
    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        xyz_translate[d+ii*36]   = _x;
        xyz_translate[d+ii*36+1] = 0.0;
        xyz_translate[d+ii*36+2] = _y;

        xyz_translate[d+ii*36+3] = 0.0;
        xyz_translate[d+ii*36+4] = 1.0;
        xyz_translate[d+ii*36+5] = 0.0;

        xyz_translate[d+ii*36+6] = _x;
        xyz_translate[d+ii*36+7] = w_a;
        xyz_translate[d+ii*36+8] = _y;

        xyz_translate[d+ii*36+9] = 0.0;
        xyz_translate[d+ii*36+10] = 1.0;
        xyz_translate[d+ii*36+11] = 0.0;

        xyz_translate[d+ii*36+12] = x;
        xyz_translate[d+ii*36+13] = 0.0;
        xyz_translate[d+ii*36+14] = y;

        xyz_translate[d+ii*36+15] = 0.0;
        xyz_translate[d+ii*36+16] = 1.0;
        xyz_translate[d+ii*36+17] = 0.0;


        ////////////////////////

        xyz_translate[d+ii*36+18] = x;
        xyz_translate[d+ii*36+19] = 0.0;
        xyz_translate[d+ii*36+20] = y;


        xyz_translate[d+ii*36+21] = 0.0;
        xyz_translate[d+ii*36+22] = 1.0;
        xyz_translate[d+ii*36+23] = 0.0;

        xyz_translate[d+ii*36+24] = x;
        xyz_translate[d+ii*36+25] = w_a;
        xyz_translate[d+ii*36+26] = y;

        xyz_translate[d+ii*36+27] = 0.0;
        xyz_translate[d+ii*36+28] = 1.0;
        xyz_translate[d+ii*36+29] = 0.0;

        xyz_translate[d+ii*36+30] = _x;
        xyz_translate[d+ii*36+31] = w_a;
        xyz_translate[d+ii*36+32] = _y;

        xyz_translate[d+ii*36+33] = 0.0;
        xyz_translate[d+ii*36+34] = 1.0;
        xyz_translate[d+ii*36+35] = 0.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d] = _x;
    xyz_translate[d+1] = 0.0;
    xyz_translate[d+2] = _y;

    xyz_translate[d+3] = 0.0;
    xyz_translate[d+4] = 1.0;
    xyz_translate[d+5] = 0.0;

    xyz_translate[d+6] = _x;
    xyz_translate[d+7] = w_a;
    xyz_translate[d+8] = _y;

    xyz_translate[d+9]  = 0.0;
    xyz_translate[d+10] = 1.0;
    xyz_translate[d+11] = 0.0;

    xyz_translate[d+12] = o_x;
    xyz_translate[d+13] = 0.0;
    xyz_translate[d+14] = o_y;

    xyz_translate[d+15] = 0.0;
    xyz_translate[d+16] = 1.0;
    xyz_translate[d+17] = 0.0;

    /////

    xyz_translate[d+18] = _x;
    xyz_translate[d+19] = 0.0;
    xyz_translate[d+20] = _y;

    xyz_translate[d+21] = 0.0;
    xyz_translate[d+22] = 1.0;
    xyz_translate[d+23] = 0.0;

    xyz_translate[d+24] = _x;
    xyz_translate[d+25] = w_a;
    xyz_translate[d+26] = _y;

    xyz_translate[d+27]  = 0.0;
    xyz_translate[d+28] = 1.0;
    xyz_translate[d+29] = 0.0;

    xyz_translate[d+30] = o_x;
    xyz_translate[d+31] = 0.0;
    xyz_translate[d+32] = o_y;

    xyz_translate[d+33] = 0.0;
    xyz_translate[d+34] = 1.0;
    xyz_translate[d+35] = 0.0;


    ///////////////////////////////////////////////////////////////////////////

    d = d+288;

    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = r * cos(_theta);//calculate the x component
    _y = r * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {

        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        xyz_translate[d+ii*18]   = _x;
        xyz_translate[d+ii*18+1] = _y;
        xyz_translate[d+ii*18+2] = w_a;

        xyz_translate[d+ii*18+3] = 0.0;
        xyz_translate[d+ii*18+4] = 0.0;
        xyz_translate[d+ii*18+5] = 1.0;

        xyz_translate[d+ii*18+6] = 0.0;
        xyz_translate[d+ii*18+7] = 0.0;
        xyz_translate[d+ii*18+8] = w_a+w_c;

        xyz_translate[d+ii*18+9] = 0.0;
        xyz_translate[d+ii*18+10] = 0.0;
        xyz_translate[d+ii*18+11] = 1.0;

        xyz_translate[d+ii*18+12] = x;
        xyz_translate[d+ii*18+13] = y;
        xyz_translate[d+ii*18+14] = w_a;

        xyz_translate[d+ii*18+15] = 0.0;
        xyz_translate[d+ii*18+16] = 0.0;
        xyz_translate[d+ii*18+17] = 1.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d+0] = _x;
    xyz_translate[d+1] = _y;
    xyz_translate[d+2] = w_a;

    xyz_translate[d+3] = 0.0;
    xyz_translate[d+4] = 0.0;
    xyz_translate[d+5] = 1.0;

    xyz_translate[d+6] = 0.0;
    xyz_translate[d+7] = 0.0;
    xyz_translate[d+8] = w_a+w_c;

    xyz_translate[d+9]  = 0.0;
    xyz_translate[d+10] = 0.0;
    xyz_translate[d+11] = 1.0;

    xyz_translate[d+12] = o_x;
    xyz_translate[d+13] = o_y;
    xyz_translate[d+14] = w_a;

    xyz_translate[d+15] = 0.0;
    xyz_translate[d+16] = 0.0;
    xyz_translate[d+17] = 1.0;

    d = d+144;
    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;
    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        xyz_translate[d+ii*36]   = _x;
        xyz_translate[d+ii*36+1] = _y;
        xyz_translate[d+ii*36+2] = 0.0;

        xyz_translate[d+ii*36+3] = 0.0;
        xyz_translate[d+ii*36+4] = 0.0;
        xyz_translate[d+ii*36+5] = 1.0;

        xyz_translate[d+ii*36+6] = _x;
        xyz_translate[d+ii*36+7] = _y;
        xyz_translate[d+ii*36+8] = w_a;

        xyz_translate[d+ii*36+9] = 0.0;
        xyz_translate[d+ii*36+10] = 0.0;
        xyz_translate[d+ii*36+11] = 1.0;

        xyz_translate[d+ii*36+12] = x;
        xyz_translate[d+ii*36+13] = y;
        xyz_translate[d+ii*36+14] = 0.0;

        xyz_translate[d+ii*36+15] = 0.0;
        xyz_translate[d+ii*36+16] = 0.0;
        xyz_translate[d+ii*36+17] = 1.0;


        ////////////////////////

        xyz_translate[d+ii*36+18] = x;
        xyz_translate[d+ii*36+19] = y;
        xyz_translate[d+ii*36+20] = 0.0;


        xyz_translate[d+ii*36+21] = 0.0;
        xyz_translate[d+ii*36+22] = 0.0;
        xyz_translate[d+ii*36+23] = 1.0;

        xyz_translate[d+ii*36+24] = x;
        xyz_translate[d+ii*36+25] = y;
        xyz_translate[d+ii*36+26] = w_a;

        xyz_translate[d+ii*36+27] = 0.0;
        xyz_translate[d+ii*36+28] = 0.0;
        xyz_translate[d+ii*36+29] = 1.0;

        xyz_translate[d+ii*36+30] = _x;
        xyz_translate[d+ii*36+31] = _y;
        xyz_translate[d+ii*36+32] = w_a;

        xyz_translate[d+ii*36+33] = 0.0;
        xyz_translate[d+ii*36+34] = 0.0;
        xyz_translate[d+ii*36+35] = 1.0;

        _x = x;
        _y = y;
    }

    xyz_translate[d] = _x;
    xyz_translate[d+1] = _y;
    xyz_translate[d+2] = 0.0;

    xyz_translate[d+3] = 0.0;
    xyz_translate[d+4] = 0.0;
    xyz_translate[d+5] = 1.0;

    xyz_translate[d+6] = _x;
    xyz_translate[d+7] = _y;
    xyz_translate[d+8] = w_a;

    xyz_translate[d+9]  = 0.0;
    xyz_translate[d+10] = 0.0;
    xyz_translate[d+11] = 1.0;

    xyz_translate[d+12] = o_x;
    xyz_translate[d+13] = o_y;
    xyz_translate[d+14] = 0.0;

    xyz_translate[d+15] = 0.0;
    xyz_translate[d+16] = 0.0;
    xyz_translate[d+17] = 1.0;

    /////

    xyz_translate[d+18] = _x;
    xyz_translate[d+19] = _y;
    xyz_translate[d+20] = 0.0;

    xyz_translate[d+21] = 0.0;
    xyz_translate[d+22] = 0.0;
    xyz_translate[d+23] = 1.0;

    xyz_translate[d+24] = _x;
    xyz_translate[d+25] = _y;
    xyz_translate[d+26] = w_a;

    xyz_translate[d+27]  = 0.0;
    xyz_translate[d+28] = 0.0;
    xyz_translate[d+29] = 1.0;

    xyz_translate[d+30] = o_x;
    xyz_translate[d+31] = o_y;
    xyz_translate[d+32] = 0.0;

    xyz_translate[d+33] = 0.0;
    xyz_translate[d+34] = 0.0;
    xyz_translate[d+35] = 1.0;

}

void FGETranslationComponent::createMeshXYZTranslateForSelection(float r, float k)
{

    int d = 0;

    float w_a = 0.004, w_c = 0.001;

    float _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    float _x = r * cos(_theta);//calculate the x component
    float _y = r * sin(_theta);//calculate the y component

    float o_x = _x, o_y = _y, x, y;

    for (int ii = 1; ii < 8; ii++)   {

        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        x_translate[ii*9]   = w_a;
        x_translate[ii*9+1] = _x;
        x_translate[ii*9+2] = _y;

        x_translate[ii*9+3] = w_a+w_c;
        x_translate[ii*9+4] = 0.0;
        x_translate[ii*9+5] = 0.0;


        x_translate[ii*9+6] = w_a;
        x_translate[ii*9+7] = x;
        x_translate[ii*9+8] = y;

        _x = x;
        _y = y;
    }

    x_translate[0] = w_a;
    x_translate[1] = _x;
    x_translate[2] = _y;


    x_translate[3] = w_a+w_c;
    x_translate[4] = 0.0;
    x_translate[5] = 0.0;


    x_translate[6] = w_a;
    x_translate[7] = o_x;
    x_translate[8] = o_y;

    d = 72;

    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        x_translate[d+ii*18]   = 0.0;
        x_translate[d+ii*18+1] = _x;
        x_translate[d+ii*18+2] = _y;

        x_translate[d+ii*18+3] = w_a;
        x_translate[d+ii*18+4] = _x;
        x_translate[d+ii*18+5] = _y;

        x_translate[d+ii*18+6] = 0.0;
        x_translate[d+ii*18+7] = x;
        x_translate[d+ii*18+8] = y;


        ////////////////////////

        x_translate[d+ii*18+9] = 0.0;
        x_translate[d+ii*18+10] = x;
        x_translate[d+ii*18+11] = y;


        x_translate[d+ii*18+12] = w_a;
        x_translate[d+ii*18+13] = x;
        x_translate[d+ii*18+14] = y;

        x_translate[d+ii*18+15] = w_a;
        x_translate[d+ii*18+16] = _x;
        x_translate[d+ii*18+17] = _y;

        _x = x;
        _y = y;
    }

    x_translate[d] = 0.0;
    x_translate[d+1] = _x;
    x_translate[d+2] = _y;

    x_translate[d+3] = w_a;
    x_translate[d+4] = _x;
    x_translate[d+5] = _y;

    x_translate[d+6] = 0.0;
    x_translate[d+7] = o_x;
    x_translate[d+8] = o_y;

    /////

    x_translate[d+9] = 0.0;
    x_translate[d+10] = _x;
    x_translate[d+11] = _y;

    x_translate[d+12] = w_a;
    x_translate[d+13] = _x;
    x_translate[d+14] = _y;

    x_translate[d+15] = 0.0;
    x_translate[d+16] = o_x;
    x_translate[d+17] = o_y;



    ///////////////////////////////////////////////////////////////////////////


    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = r * cos(_theta);//calculate the x component
    _y = r * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        y_translate[ii*9]   = _x;
        y_translate[ii*9+1] = w_a;
        y_translate[ii*9+2] = _y;

        y_translate[ii*9+3] = 0.0;
        y_translate[ii*9+4] = w_a+w_c;
        y_translate[ii*9+5] = 0.0;

        y_translate[ii*9+6] = x;
        y_translate[ii*9+7] = w_a;
        y_translate[ii*9+8] = y;

        _x = x;
        _y = y;
    }

    y_translate[0] = _x;
    y_translate[1] = w_a;
    y_translate[2] = _y;

    y_translate[3] = 0.0;
    y_translate[4] = w_a+w_c;
    y_translate[5] = 0.0;

    y_translate[6] = o_x;
    y_translate[7] = w_a;
    y_translate[8] = o_y;

    d = 72;

    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;
    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        y_translate[d+ii*18]   = _x;
        y_translate[d+ii*18+1] = 0.0;
        y_translate[d+ii*18+2] = _y;

        y_translate[d+ii*18+3] = _x;
        y_translate[d+ii*18+4] = w_a;
        y_translate[d+ii*18+5] = _y;

        y_translate[d+ii*18+6] = x;
        y_translate[d+ii*18+7] = 0.0;
        y_translate[d+ii*18+8] = y;


        ////////////////////////

        y_translate[d+ii*18+9] = x;
        y_translate[d+ii*18+10] = 0.0;
        y_translate[d+ii*18+11] = y;

        y_translate[d+ii*18+12] = x;
        y_translate[d+ii*18+13] = w_a;
        y_translate[d+ii*18+14] = y;

        y_translate[d+ii*18+15] = _x;
        y_translate[d+ii*18+16] = w_a;
        y_translate[d+ii*18+17] = _y;

        _x = x;
        _y = y;
    }

    y_translate[d] = _x;
    y_translate[d+1] = 0.0;
    y_translate[d+2] = _y;

    y_translate[d+3] = _x;
    y_translate[d+4] = w_a;
    y_translate[d+5] = _y;

    y_translate[d+6] = o_x;
    y_translate[d+7] = 0.0;
    y_translate[d+8] = o_y;

    /////

    y_translate[d+9] = _x;
    y_translate[d+10] = 0.0;
    y_translate[d+11] = _y;

    y_translate[d+12] = _x;
    y_translate[d+13] = w_a;
    y_translate[d+14] = _y;

    y_translate[d+15] = o_x;
    y_translate[d+16] = 0.0;
    y_translate[d+17] = o_y;


    ///////////////////////////////////////////////////////////////////////////


    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = r * cos(_theta);//calculate the x component
    _y = r * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;

    for (int ii = 1; ii < 8; ii++)   {

        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = r * cos(theta);//calculate the x component
        y = r * sin(theta);//calculate the y component

        z_translate[ii*9]   = _x;
        z_translate[ii*9+1] = _y;
        z_translate[ii*9+2] = w_a;

        z_translate[ii*9+3] = 0.0;
        z_translate[ii*9+4] = 0.0;
        z_translate[ii*9+5] = w_a+w_c;

        z_translate[ii*9+6] = x;
        z_translate[ii*9+7] = y;
        z_translate[ii*9+8] = w_a;

        _x = x;
        _y = y;
    }

    z_translate[0] = _x;
    z_translate[1] = _y;
    z_translate[2] = w_a;

    z_translate[3] = 0.0;
    z_translate[4] = 0.0;
    z_translate[5] = w_a+w_c;

    z_translate[6] = o_x;
    z_translate[7] = o_y;
    z_translate[8] = w_a;

    d = 72;
    _theta = 2.0f * 3.1415926f * float(0) / float(8);//get the current angle
    _x = k * cos(_theta);//calculate the x component
    _y = k * sin(_theta);//calculate the y component

    o_x = _x;
    o_y = _y;
    for (int ii = 1; ii < 8; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(8);//get the current angle
        x = k * cos(theta);//calculate the x component
        y = k * sin(theta);//calculate the y component

        z_translate[d+ii*18]   = _x;
        z_translate[d+ii*18+1] = _y;
        z_translate[d+ii*18+2] = 0.0;

        z_translate[d+ii*18+3] = _x;
        z_translate[d+ii*18+4] = _y;
        z_translate[d+ii*18+5] = w_a;

        z_translate[d+ii*18+6] = x;
        z_translate[d+ii*18+7] = y;
        z_translate[d+ii*18+8] = 0.0;


        ////////////////////////

        z_translate[d+ii*18+9] = x;
        z_translate[d+ii*18+10] = y;
        z_translate[d+ii*18+11] = 0.0;

        z_translate[d+ii*18+12] = x;
        z_translate[d+ii*18+13] = y;
        z_translate[d+ii*18+14] = w_a;

        z_translate[d+ii*18+15] = _x;
        z_translate[d+ii*18+16] = _y;
        z_translate[d+ii*18+17] = w_a;

        _x = x;
        _y = y;
    }

    z_translate[d] = _x;
    z_translate[d+1] = _y;
    z_translate[d+2] = 0.0;

    z_translate[d+3] = _x;
    z_translate[d+4] = _y;
    z_translate[d+5] = w_a;

    z_translate[d+6] = o_x;
    z_translate[d+7] = o_y;
    z_translate[d+8] = 0.0;

    /////

    z_translate[d+9] = _x;
    z_translate[d+10] = _y;
    z_translate[d+11] = 0.0;

    z_translate[d+12] = _x;
    z_translate[d+13] = _y;
    z_translate[d+14] = w_a;

    z_translate[d+15] = o_x;
    z_translate[d+16] = o_y;
    z_translate[d+17] = 0.0;

}

void FGETranslationComponent::initShader()
{
    initShaderForCircleTranslate();
    initShaderForAxesTranslate();
    initShaderForSelection();
    initShaderForXYZAxes();
    gizmo_rotation->shaderProgram = createShader(gizmo_rotation->source_vertex_shader, gizmo_rotation->source_fragment_shader);
    glBindAttribLocation(gizmo_rotation->shaderProgram, 0, "vertex");
    glBindAttribLocation(gizmo_rotation->shaderProgram, 1, "normal");

    gizmo_rotation->shader_program_center = createShader(gizmo_rotation->svsc, gizmo_rotation->sfsc);
    glBindAttribLocation(gizmo_rotation->shader_program_center, 0, "vertex");

    gizmo_rotation->shader_program_w = createShader(gizmo_rotation->svsw, gizmo_rotation->sfsw);
    glBindAttribLocation(gizmo_rotation->shader_program_w, 0, "vertex");

    gizmo_rotation->selection_shader_program = createShader(gizmo_rotation->source_vertex_shader, gizmo_rotation->source_fragment_shader_selection);
    glBindAttribLocation(gizmo_rotation->selection_shader_program, 0, "vertex");
    glBindAttribLocation(gizmo_rotation->selection_shader_program, 1, "normal");

    gizmo_rotation->selection_shader_program_center = createShader(gizmo_rotation->selection_svsc, gizmo_rotation->selection_sfsc);
    glBindAttribLocation(gizmo_rotation->selection_shader_program_center, 0, "vertex");

    gizmo_rotation->selection_shader_program_w = createShader(gizmo_rotation->selection_svsw, gizmo_rotation->selection_sfsw);
    glBindAttribLocation(gizmo_rotation->selection_shader_program_w, 0, "vertex");

    gizmo_rotation->axe_shader_program = createShader(gizmo_rotation->axe_source_vertex_shader, gizmo_rotation->axe_source_fragment_shader);
    glBindAttribLocation(gizmo_rotation->axe_shader_program, 0, "vertex");


    gizmo_rotation->lines.shaderProgram = createShader(gizmo_rotation->lines.source_vertex_shader, gizmo_rotation->lines.source_fragment_shader);
    glBindAttribLocation(gizmo_rotation->lines.shaderProgram, 0, "vertex");


}

unsigned int FGETranslationComponent::createShader(const char *s_v_s, const char *s_f_s)
{
    int success;
    char infoLog[512];

    unsigned int dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &s_v_s, NULL);
    glCompileShader(dvs);

        glGetShaderiv(dvs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(dvs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int dfs = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    glShaderSource(dfs, 1, &s_f_s, NULL);
    glCompileShader(dfs);

        glGetShaderiv(dfs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(dfs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, dvs);
    glAttachShader(shaderProgram, dfs);

    //glBindAttribLocation(shaderProgram, 0, "vertex");

    glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }

    glDeleteShader(dvs);
    glDeleteShader(dfs);

    return shaderProgram;
}

void FGETranslationComponent::initShaderForCircleTranslate()
{
    int success;
    char infoLog[512];

    const char *dvsc =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                //"uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "    gl_Position = projection * model * vec4(vertex, 1.0);"
                "}";

    const char *dfsc =
                "void main()"
                "{"
                "   gl_FragColor = vec4(1.0, 1.0, 1.0, 0.7);"
                "}";

    unsigned int dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &dvsc, NULL);
    glCompileShader(dvs);

        glGetShaderiv(dvs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(dvs, 512, NULL, infoLog);
            //qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int dfs = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    glShaderSource(dfs, 1, &dfsc, NULL);
    glCompileShader(dfs);

        glGetShaderiv(dfs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(dfs, 512, NULL, infoLog);
            //qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    shaderProgram_c_translate = glCreateProgram();
    glAttachShader(shaderProgram_c_translate, dvs);
    glAttachShader(shaderProgram_c_translate, dfs);

    glBindAttribLocation(shaderProgram_c_translate, 0, "vertex");

    glLinkProgram(shaderProgram_c_translate);

        glGetProgramiv(shaderProgram_c_translate, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram_c_translate, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }

    glDeleteShader(dvs);
    glDeleteShader(dfs);

}

void FGETranslationComponent::initShaderForAxesTranslate()
{
    int success;
    char infoLog[512];

    const char *vsst =
                "attribute vec3 vertex;"
                "attribute vec3 color;"
                "varying vec3 _color;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "    gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "   _color = color;"
                "}";

    const char *fsst =
                "varying vec3 _color;"
                "void main()"
                "{"
                "   gl_FragColor = vec4(_color, 1.0);"
                "}";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsst, NULL);
    glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    glShaderSource(fs, 1, &fsst, NULL);
    glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    shaderProgram_xyz_translate = glCreateProgram();
    glAttachShader(shaderProgram_xyz_translate, vs);
    glAttachShader(shaderProgram_xyz_translate, fs);

    glBindAttribLocation(shaderProgram_xyz_translate, 0, "vertex");
    glBindAttribLocation(shaderProgram_xyz_translate, 1, "color");

    glLinkProgram(shaderProgram_xyz_translate);

        glGetProgramiv(shaderProgram_xyz_translate, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram_xyz_translate, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }

    glDeleteShader(vs);
    glDeleteShader(fs);

}

void FGETranslationComponent::initBufferXYZAxes(){
    xyz_axes[0] = 0.0;
    xyz_axes[1] = 0.0;
    xyz_axes[2] = 0.0;
    xyz_axes[3] = 0.0;
    xyz_axes[4] = 0.0;
    xyz_axes[5] = 0.0;

    glGenVertexArrays(1, &vao_xyza);
    glGenBuffers(1, &vbo_xyza);

    glBindVertexArray(vao_xyza);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_xyza);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, &xyz_axes[0], GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void FGETranslationComponent::initShaderForXYZAxes()
{
    int success;
    char infoLog[512];

    const char *vsst =
                "attribute vec3 vertex;"
                "uniform vec3 color;"
                "varying vec3 _color;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "    gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "   _color = color;"
                "}";

    const char *fsst =
                "varying vec3 _color;"
                "void main()"
                "{"
                "   gl_FragColor = vec4(_color, 1.0);"
                "}";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsst, NULL);
    glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    glShaderSource(fs, 1, &fsst, NULL);
    glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    shaderProgram_xyz_axes = glCreateProgram();
    glAttachShader(shaderProgram_xyz_axes, vs);
    glAttachShader(shaderProgram_xyz_axes, fs);

    glBindAttribLocation(shaderProgram_xyz_axes, 0, "vertex");

    glLinkProgram(shaderProgram_xyz_axes);

        glGetProgramiv(shaderProgram_xyz_axes, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram_xyz_axes, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }

    glDeleteShader(vs);
    glDeleteShader(fs);

}

void FGETranslationComponent::initShaderForSelection()
{
    int success;
    char infoLog[512];

    const char *vsst =
                "attribute vec3 vertex;"
                "uniform mat4 model;"
                "uniform mat4 view;"
                "uniform mat4 projection;"
                "void main()"
                "{"
                "    gl_Position = projection * view * model * vec4(vertex, 1.0);"
                "}";

    const char *fsst =
                "uniform vec3 color;"
                "void main()"
                "{"
                "   gl_FragColor = vec4(color, 1.0);"
                "}";

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsst, NULL);
    glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    glShaderSource(fs, 1, &fsst, NULL);
    glCompileShader(fs);

        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    shaderProgram_selection = glCreateProgram();
    glAttachShader(shaderProgram_selection, vs);
    glAttachShader(shaderProgram_selection, fs);

    glBindAttribLocation(shaderProgram_selection, 0, "vertex");

    glLinkProgram(shaderProgram_selection);

        glGetProgramiv(shaderProgram_selection, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram_selection, 512, NULL, infoLog);
            qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }

    glDeleteShader(vs);
    glDeleteShader(fs);

}

//////////////////////////////// T translation gizmo/////////////////////////////////////
/*glm::mat4 &FGETranslationComponent::getModelMatrix(glm::mat4 &transformation_matrix, glm::mat4 &view_matrix, glm::mat4 &projection_matrix, FGEStructProject *struct_project, int WIDTH, int HEIGHT)
{
    glm::vec4 __p = /*struct_project->node_current->matrix*//*transformation_matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::mat4 __m = getRotationToParent(struct_project->node_current);

    glm::vec3 pos_s = glm::project(__t, view_matrix, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), view_matrix, projection_matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    /*glm::mat4 __rm = glm::mat4(1.0);
    __rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;*/
/*
    m_ = (m_ /  __m) ;
    return m_;
}*/
void FGETranslationComponent::drawGizmoTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    ////////////////////////////////////  center_object  ////////////////////////////////////
    glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::mat4 __m = getRotationToParent(struct_project->node_current);

    glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::mat4 __rm = glm::mat4(1.0);
    __rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;

    m_ = (m_ /  __m) ;

    glUseProgram(shaderProgram_xyz_translate);
    setMat4(shaderProgram_xyz_translate, "view", struct_project->scene_current->view->matrix);
    setMat4(shaderProgram_xyz_translate, "projection", struct_project->scene_current->projection->matrix);
    setMat4(shaderProgram_xyz_translate, "model", m_);

    glBindVertexArray(vao_a);
    glDrawArrays(GL_TRIANGLES, 0, 72*3);
}

void FGETranslationComponent::selectionGizmoTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    ////////////////////////////////////  draw x axe   ////////////////////////////////////
    /*glDepthFunc(GL_ALWAYS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
    glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::mat4 __m = getRotationToParent(struct_project->node_current);

    glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(200.0f/HEIGHT, 200.0f/HEIGHT, 200.0f/HEIGHT));

    glm::mat4 __rm = glm::mat4(1.0);
    __rm = glm::translate(__rm, glm::vec3(0.0));
    __rm = __rm*struct_project->node_current->transform.matrix_r;

    //m_ = (m_ *  __m) /__rm;

    glUseProgram(shaderProgram_selection);
    setMat4(shaderProgram_selection, "view", struct_project->scene_current->view->matrix);
    setMat4(shaderProgram_selection, "projection", struct_project->scene_current->projection->matrix);
    setMat4(shaderProgram_selection, "model", m_);

    setVec3(shaderProgram_selection, "color", glm::vec3(1.0, 0.0, 0.0));
    glBindVertexArray(vao_xa);
    glDrawArrays(GL_TRIANGLES, 0, 72);

    setVec3(shaderProgram_selection, "color", glm::vec3(0.0, 1.0, 0.0));
    glBindVertexArray(vao_ya);
    glDrawArrays(GL_TRIANGLES, 0, 72);

    setVec3(shaderProgram_selection, "color", glm::vec3(0.0, 0.0, 1.0));
    glBindVertexArray(vao_za);
    glDrawArrays(GL_TRIANGLES, 0, 72);

    setVec3(shaderProgram_selection, "color", glm::vec3(0.5, 0.5, 0.5));
    glBindVertexArray(vao_c);
    glDrawArrays(GL_POLYGON, 0, 36);
}

void FGETranslationComponent::drawAxeTranslation(FGEDataProject *struct_project, int WIDTH, int HEIGHT){
    if(drag_selected || x_move_selected || y_move_selected || z_move_selected){
        glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::mat4 __rm = glm::mat4(1.0);
        __rm = glm::translate(__rm, glm::vec3(0.0));
        __rm = __rm*struct_project->node_current->transform.matrix_r;

        glm::mat4 __m = getRotationToParent(struct_project->node_current);

        glm::vec3 color;
        glm::vec3 pos_s = glm::project(__t,struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        //qDebug() << "ggggg (" << pos_s[0]<< ", "<< pos_s[1]<< ")";

        glm::vec4 t_p1, t_p2;

        if(drag_selected){
            /*GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
            glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            updateGL();*/

        }else if(x_move_selected){

            /*t_p1 = glm::vec4(pos_w[0]-0.001, pos_w[1], pos_w[2], 1.0);
            t_p2 = glm::vec4(pos_w[0]+0.001, pos_w[1], pos_w[2], 1.0);*/
            t_p1 = glm::vec4(0.5, 0.0, 0.0, 1.0);
            t_p2 = glm::vec4(-0.5, 0.0, 0.0, 1.0);

            xyz_axes[0] = 1000.0;
            xyz_axes[1] = 0.0;
            xyz_axes[2] = 0.0;
            xyz_axes[3] = -1000.0;
            xyz_axes[4] = 0.0;
            xyz_axes[5] = 0.0;
            color = glm::vec3(1.0, 0.0, 0.0);

        }else if(y_move_selected){
            /*t_p1 = glm::vec4(pos_w[0], pos_w[1]-0.001, pos_w[2], 1.0);
            t_p2 = glm::vec4(pos_w[0], pos_w[1]+0.001, pos_w[2], 1.0);*/
            t_p1 = glm::vec4(0.0, 0.5, 0.0, 1.0);
            t_p2 = glm::vec4(0.0, -0.5, 0.0, 1.0);
            xyz_axes[0] = 0.0;
            xyz_axes[1] = 1000.0;
            xyz_axes[2] = 0.0;
            xyz_axes[3] = 0.0;
            xyz_axes[4] = -1000.0;
            xyz_axes[5] = 0.0;
            color = glm::vec3(0.0, 1.0, 0.0);

        }else if(z_move_selected){

            /*t_p1 = glm::vec4(pos_w[0], pos_w[1], pos_w[2]-0.001, 1.0);
            t_p2 = glm::vec4(pos_w[0], pos_w[1], pos_w[2]+0.001, 1.0);*/
            t_p1 = glm::vec4(0.0, 0.0, 0.5, 1.0);
            t_p2 = glm::vec4(0.0, 0.0, -0.5, 1.0);

            xyz_axes[0] = 0.0;
            xyz_axes[1] = 0.0;
            xyz_axes[2] = 1000.0;
            xyz_axes[3] = 0.0;
            xyz_axes[4] = 0.0;
            xyz_axes[5] = -1000.0;
            color = glm::vec3(0.0, 0.0, 1.0);
        }
        qDebug() << "__m*t_p1 (" << t_p1[0]<< ", "<< t_p1[1]<<  ", "<< t_p1[2]<< ")";
        qDebug() << "__m*t_p2 (" << t_p2[0]<< ", "<< t_p2[1]<<  ", "<< t_p2[2]<< ")";


        glm::mat4 __erm = glm::mat4(1.0);
        __erm = glm::translate(__erm, glm::vec3(0.0));
        __erm = __erm*struct_project->node_current->transform.matrix_r;

        //t_p1 = __erm*t_p1 ;
        t_p1 = (struct_project->node_current->matrix/__m)*t_p1;
        t_p2 = (struct_project->node_current->matrix/__m)*t_p2;


        current_eq_2d_line.p1 = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        current_eq_2d_line.p2 = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        points[0] = current_eq_2d_line.p1[0];
        points[1] = current_eq_2d_line.p1[1];
        points[2] = 0.0;

        points_2[0] = current_eq_2d_line.p2[0];
        points_2[1] = current_eq_2d_line.p2[1];
        points_2[2] = 0.0;

qDebug() << "t_p1 (" << t_p1[0]<< ", "<< t_p1[1]<<  ", "<< t_p1[2]<< ")";
qDebug() << "t_p2 (" << t_p2[0]<< ", "<< t_p2[1]<<  ", "<< t_p2[2]<< ")";
/*
points[0] = t_p1[0];
points[1] = t_p1[1];
points[2] = t_p1[2];

points_2[0] = t_p2[0];
points_2[1] = t_p2[1];
points_2[2] = t_p2[2];*/

//qDebug() << "ooooo (" << current_eq_2d_line.p1[0]<< ", "<< current_eq_2d_line.p1[1]<< ")";
//qDebug() << "iiiii (" << current_eq_2d_line.p2[0]<< ", "<< current_eq_2d_line.p2[1]<< ")";

/*
glm::mat4 m_ = glm::translate(glm::mat4(1.0f), struct_project->node_current->transform.translate);
m_ = glm::scale(m_, struct_project->node_current->transform.scale);
m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[0]),  glm::vec3(1.0f, 0.0f, 0.0f));
m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[1]),  glm::vec3(0.0f, 1.0f, 0.0f));
m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[2]),  glm::vec3(0.0f, 0.0f, 1.0f));
*/
//struct_project->node_current->transform.matrix = m_;


        glBindVertexArray(vao_xyza);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_xyza);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, xyz_axes);

        glUseProgram(shaderProgram_xyz_axes);

        setMat4(shaderProgram_xyz_axes, "view", struct_project->scene_current->view->matrix);
        setMat4(shaderProgram_xyz_axes, "projection", struct_project->scene_current->projection->matrix);
        setMat4(shaderProgram_xyz_axes, "model", struct_project->node_current->matrix/__m);
        setVec3(shaderProgram_xyz_axes, "color", color);

        glDrawArrays(GL_LINES, 0, 6);




    }
}

void FGETranslationComponent::drawListPoints(FGEDataProject *struct_project){

    float yy[3];



    glUseProgram(shaderProgram_xyz_axes);

    setMat4(shaderProgram_xyz_axes, "view", glm::mat4(1.0));
    setMat4(shaderProgram_xyz_axes, "projection", glm::ortho(0.0f, (float)struct_project->view_port_width, 0.0f, (float)struct_project->view_port_height, -1.0f, 100.0f));
    setMat4(shaderProgram_xyz_axes, "model", glm::mat4(1.0));
    setVec3(shaderProgram_xyz_axes, "color", glm::vec3(1.0, 0.2, 0.0));

    glPointSize(8.0);

    yy[0]  = points[0];
    yy[1]  = points[1];
    yy[2] = points[2];

    glBindVertexArray(vao_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, &yy[0]);
    glDrawArrays(GL_POINTS, 0, 1);

    setVec3(shaderProgram_xyz_axes, "color", glm::vec3(0.0, 0.4, 1.0));

    yy[0]  = points_2[0];
    yy[1]  = points_2[1];
    yy[2] = points_2[2];
    glBindVertexArray(vao_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, &yy[0]);
    glDrawArrays(GL_POINTS, 0, 1);

    setVec3(shaderProgram_xyz_axes, "color", glm::vec3(0.2, 1.0, 0.3));

    yy[0] = points_3[0];
    yy[1] = points_3[1];
    yy[2] = points_3[2];
    glBindVertexArray(vao_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, &yy[0]);
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(1.0);
    glBindVertexArray(0);

}


void FGETranslationComponent::draw3DListPoints(FGEDataProject *struct_project){

    float yy[3];

    glUseProgram(shaderProgram_xyz_axes);

    setMat4(shaderProgram_xyz_axes, "view", struct_project->scene_current->view->matrix);
    setMat4(shaderProgram_xyz_axes, "projection", struct_project->scene_current->projection->matrix);
    setMat4(shaderProgram_xyz_axes, "model", glm::mat4(1.0));
    setVec3(shaderProgram_xyz_axes, "color", glm::vec3(0.7, 0.2, 0.1));

    glPointSize(8.0);

    yy[0] = _t3d1[0];
    yy[1] = _t3d1[1];
    yy[2] = _t3d1[2];

    glBindVertexArray(vao_points);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3, &yy[0]);
    glDrawArrays(GL_POINTS, 0, 1);

    glBindVertexArray(0);

}

void FGETranslationComponent::updateAxesTranslation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT){

    if(drag_selected || x_move_selected || y_move_selected || z_move_selected){

        glm::mat4 _tm = getRotationToParent(struct_project->node_current);

        glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);
        glm::mat4 __m = glm::mat4(1.0);
        if(struct_project->node_current->parent!=NULL){
            __m = struct_project->node_current->parent->matrix;
        }
        //__m = __m*struct_project->node_current->matrix;

        //__m = struct_project->node_current->matrix;

        glm::vec2 b, o, a, s;
        glm::vec3 p = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        o[0] = p[0]+(pos_x - w_drag_cursor[0]);
        o[1] = p[1]+(pos_y - w_drag_cursor[1]);

        /*o[0] = pos_x;
        o[1] = pos_y;*/

        qDebug() << "_o (" << o[0]<< ", "<< o[1]<< ")";
        qDebug() << "_p (" << p[0]<< ", "<< p[1]<< ")";
        qDebug() << "_w_drag_cursor (" << w_drag_cursor[0]<< ", "<< w_drag_cursor[1]<< ")";
        qDebug() << "pos_ (" << pos_x<< ", "<< pos_y<< ")";



        //o[0] = event->x();
        //o[1] = HEIGHT-event->y();

        a = glm::vec2(current_eq_2d_line.p1[0], current_eq_2d_line.p1[1]);
        b = glm::vec2(current_eq_2d_line.p2[0], current_eq_2d_line.p2[1]);


        points[0] = a[0];
        points[1] = a[1];
        points[2] = 0.0;

        points_2[0] = b[0];
        points_2[1] = b[1];
        points_2[2] = 0.0;


        qDebug() << "a (" << a[0]<< ", "<< a[1]<< ")";
        qDebug() << "b (" << b[0]<< ", "<< b[1]<< ")";

        float _s = (b[1]-a[1])/(b[0]-a[0]);
        float _b = a[1] - a[0]*_s;

        //qDebug() << "_s _b (" << _s<< ", "<< _b<< ")";
        //qDebug() << "_q (" << o[0]<< ", "<< o[1]<< ")";

        glm::vec4 r = intersection2DLineRect(_s, _b, WIDTH, HEIGHT);

        if(r!=glm::vec4(0.0,0.0,0.0,0.0)){
            s = glm::closestPointOnLine(o, glm::vec2(r[0], r[1]), glm::vec2(r[2], r[3]));
        }else{
            s = glm::closestPointOnLine(o, glm::vec2(r[0], r[1]), glm::vec2(r[2], r[3]));
        }

        points_3[0] = s[0];
        points_3[1] = s[1];
        points_3[2] = 0.0;


        qDebug() << "S (" << s[0]<< ", "<< s[1]<< ")";
        //qDebug() << "p1 (" << r[0]<< ", "<< r[1]<< ")";
        //qDebug() << "p2 (" << r[2]<< ", "<< r[3]<< ")";

        glm::vec3 _p1 = glm::unProject(glm::vec3(s[0], s[1], 0.0), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 _p2 = glm::unProject(glm::vec3(s[0], s[1], 0.1), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec4 p1 = glm::vec4(_p1[0], _p1[1], _p1[2], 1.0f);
        glm::vec4 p2 = glm::vec4(_p2[0], _p2[1], _p2[2], 1.0f);


        /*glm::vec4 p1 = glm::vec4(_p1[0], _p1[1], _p1[2], 1.0f);
        glm::vec4 p2 = glm::vec4(_p2[0], _p2[1], _p2[2], 1.0f);
*/
        //__t = glm::vec3(0.0, 0.0, 0.0);

        if(drag_selected){
            /*GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
            glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            updateGL();*/

        }else if(x_move_selected){
            float t = (__t[1]-p1[1])/(p2[1]-p1[1]);
            __t[0] = (p2[0]-p1[0])*t+p1[0];

            w_drag_cursor = glm::vec2(pos_x, pos_y);
        }else if(y_move_selected){
            float t = (__t[0]-p1[0])/(p2[0]-p1[0]);
            __t[1] = (p2[1]-p1[1])*t+p1[1];

            w_drag_cursor = glm::vec2(pos_x, pos_y);
        }else if(z_move_selected){
            float t = (__t[0]-p1[0])/(p2[0]-p1[0]);
            __t[2] = (p2[2]-p1[2])*t+p1[2];

            w_drag_cursor = glm::vec2(pos_x, pos_y);
        }
        _t3d1 = __t;

        glm::vec4 tt = glm::vec4(__t[0], __t[1], __t[2], 1.0f);
        /*glm::mat4 my_ = glm::translate(glm::mat4(1.0f), __t);
        my_ = glm::scale(my_, glm::vec3(1.0, 1.0, 1.0));
        my_ = glm::rotate(my_, glm::radians((float)0.0), glm::vec3(1.0f, 0.0f, 0.0f));
        my_ = glm::rotate(my_, glm::radians((float)0.0), glm::vec3(0.0f, 1.0f, 0.0f));
        my_ = glm::rotate(my_, glm::radians((float)0.0), glm::vec3(0.0f, 0.0f, 1.0f));
*/

        //glm::mat4 m_ = glm::translate(glm::mat4(1.0f), __t);
        tt = __m/tt;
        //glm::vec4 tt = my_*glm::vec4(0.0, 0.0, 0.0, 1.0);
 /*       struct_project->node_current->transform.translate[0] = tt[0];
        struct_project->node_current->transform.translate[1] = tt[1];
        struct_project->node_current->transform.translate[2] = tt[2];
*/

        glm::mat4 m_;/* = glm::translate(glm::mat4(1.0f), struct_project->node_current->transform.translate);
        m_ = glm::scale(m_, struct_project->node_current->transform.scale);
        m_ = m_*struct_project->node_current->transform.matrix_r;


        struct_project->node_current->transform.matrix = m_;
*/
        //glm::vec4 __e = __m*struct_project->node_current->transform.matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);



        //glm::mat4 m_ = glm::translate(glm::mat4(1.0f), struct_project->node_current->transform.translate);
    //    m_ = glm::scale(m_, struct_project->node_current->transform.scale);
        /*m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[0]),  glm::vec3(1.0f, 0.0f, 0.0f));
        m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[1]),  glm::vec3(0.0f, 1.0f, 0.0f));
        m_ = glm::rotate(m_,  glm::radians((float)struct_project->node_current->transform.rotate[2]),  glm::vec3(0.0f, 0.0f, 1.0f));*/
        //struct_project->node_current->transform.matrix = struct_project->node_current->transform.matrix*m_;

    }
}

glm::mat4 FGETranslationComponent::getRotationToParent(FGEDataNode *node){
    if(node==NULL) return glm::mat4(1.0);
    glm::mat4 __m = glm::mat4(1.0), t = glm::mat4(1.0);

    if(node->parent!=NULL){
        //t = node->parent->transform.matrix_r;
    }
    //__m = node->transform.matrix_r;
    return t*__m;
}

////////////////////////////////end translation gizmo ///////////////////////////////

//////////////////////////////// R rotation gizmo/////////////////////////////////////

void FGETranslationComponent::drawGizmosRotation(FGEDataProject *struct_project, int WIDTH, int HEIGHT)
{
    glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(300.0f/HEIGHT, 300.0f/HEIGHT, 300.0f/HEIGHT));
    gizmo_rotation->diameter_after_scale = gizmo_rotation->diameter*300.0f/HEIGHT;
    //qDebug() << "*****************  gizmo_rotation->diameter_after_scale";

    glUseProgram(gizmo_rotation->shader_program_center);
    setMat4(gizmo_rotation->shader_program_center, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->shader_program_center, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->shader_program_center, "model", m_);
    setVec3(gizmo_rotation->shader_program_center, "color", gizmo_rotation->color_c);
    setVec3(gizmo_rotation->shader_program_center, "center", pos_s);

    glBindVertexArray(gizmo_rotation->vao_c);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glUseProgram(gizmo_rotation->shaderProgram);
    setMat4(gizmo_rotation->shaderProgram, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->shaderProgram, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->shaderProgram, "model", m_);
    ///////////////////// X ///////////////////////
    {
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_x);
        setFloat(gizmo_rotation->shaderProgram, "blend", 0.2);
        glBindVertexArray(gizmo_rotation->vao_x);
        glLineWidth(4.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);

        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_x);
        setFloat(gizmo_rotation->shaderProgram, "blend", 0.5);
        glBindVertexArray(gizmo_rotation->vao_x);
        glLineWidth(3.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_x);
        setFloat(gizmo_rotation->shaderProgram, "blend", 1.0);
        glBindVertexArray(gizmo_rotation->vao_x);
        glLineWidth(2.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);
    }


    ///////////////////// Y ///////////////////////

    {
        setFloat(gizmo_rotation->shaderProgram, "blend", 0.2);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_y);
        glBindVertexArray(gizmo_rotation->vao_y);
        glLineWidth(4.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);

        setFloat(gizmo_rotation->shaderProgram, "blend", 0.5);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_y);
        glBindVertexArray(gizmo_rotation->vao_y);
        glLineWidth(3.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);

        setFloat(gizmo_rotation->shaderProgram, "blend", 1.0);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_y);
        glBindVertexArray(gizmo_rotation->vao_y);
        glLineWidth(2.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);
    }


    ///////////////////// Z ///////////////////////

    {
        setFloat(gizmo_rotation->shaderProgram, "blend", 0.2);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_z);
        glBindVertexArray(gizmo_rotation->vao_z);
        glLineWidth(4.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);

        setFloat(gizmo_rotation->shaderProgram, "blend", 0.5);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_z);
        glBindVertexArray(gizmo_rotation->vao_z);
        glLineWidth(3.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);

        setFloat(gizmo_rotation->shaderProgram, "blend", 1.0);
        setVec3(gizmo_rotation->shaderProgram, "color", gizmo_rotation->color_z);
        glBindVertexArray(gizmo_rotation->vao_z);
        glLineWidth(2.0);
        glDrawArrays(GL_LINE_LOOP, 0, 360);
    }


    ///////////////////// END XYZ ///////////////////////

    ///////////////////// AROUND ///////////////////////

    glUseProgram(gizmo_rotation->shader_program_w);
    setMat4(gizmo_rotation->shader_program_w, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->shader_program_w, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->shader_program_w, "model", m_);

    setVec3(gizmo_rotation->shader_program_w, "color", gizmo_rotation->color_w);
    setVec3(gizmo_rotation->shader_program_w, "center", pos_s);

    glBindVertexArray(gizmo_rotation->vao_w);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glLineWidth(1.0);
}

void FGETranslationComponent::drawAxeRotation(FGEDataProject *struct_project, int WIDTH, int HEIGHT){
    if(gizmo_rotation->drag_selected || gizmo_rotation->w_move_selected || gizmo_rotation->x_move_selected || gizmo_rotation->y_move_selected || gizmo_rotation->z_move_selected){
        glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
        m_ = glm::scale(m_, glm::vec3(300.0f/HEIGHT, 300.0f/HEIGHT, 300.0f/HEIGHT));

        if(gizmo_rotation->drag_selected){
            /*glBindVertexArray(gizmo_rotation->vao_c);
            glUseProgram(gizmo_rotation->axe_shader_program);
            setMat4(gizmo_rotation->axe_shader_program, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "model", m_);
            setVec3(gizmo_rotation->axe_shader_program, "color", gizmo_rotation->color_c);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_LOOP, 0, 360);
            glLineWidth(1.0);*/

        }else if(gizmo_rotation->x_move_selected){

            glBindVertexArray(gizmo_rotation->vao_x);
            glUseProgram(gizmo_rotation->axe_shader_program);
            //qDebug() << "/////////// hhhhhh";
            setMat4(gizmo_rotation->axe_shader_program, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "model", m_);
            setVec3(gizmo_rotation->axe_shader_program, "color", gizmo_rotation->color_x);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_LOOP, 0, 360);
            glLineWidth(1.0);

            /////////////////////////////////////////////


            float _l[] = {
                gizmo_rotation->lines.p1[0], gizmo_rotation->lines.p1[1], gizmo_rotation->lines.p1[2],
                pos_w[0], pos_w[1], pos_w[2],
                gizmo_rotation->lines.p2[0], gizmo_rotation->lines.p2[1], gizmo_rotation->lines.p2[2]
            };

            glBindVertexArray(gizmo_rotation->lines.vao);
            glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->lines.vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

            glUseProgram(gizmo_rotation->lines.shaderProgram);
            setMat4(gizmo_rotation->lines.shaderProgram, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "model", glm::mat4(1.0f));
            setVec3(gizmo_rotation->lines.shaderProgram, "color", gizmo_rotation->color_x);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_STRIP, 0, 3);
            glLineWidth(1.0);



        }else if(gizmo_rotation->y_move_selected){
            glBindVertexArray(gizmo_rotation->vao_y);
            glUseProgram(gizmo_rotation->axe_shader_program);
            //qDebug() << "/////////// hhhhhh";
            setMat4(gizmo_rotation->axe_shader_program, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "model", m_);
            setVec3(gizmo_rotation->axe_shader_program, "color", gizmo_rotation->color_y);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_LOOP, 0, 360);
            glLineWidth(1.0);

            /////////////////////////////////////////////


            float _l[] = {
                gizmo_rotation->lines.p1[0], gizmo_rotation->lines.p1[1], gizmo_rotation->lines.p1[2],
                pos_w[0], pos_w[1], pos_w[2],
                gizmo_rotation->lines.p2[0], gizmo_rotation->lines.p2[1], gizmo_rotation->lines.p2[2]
            };

            glBindVertexArray(gizmo_rotation->lines.vao);
            glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->lines.vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

            glUseProgram(gizmo_rotation->lines.shaderProgram);
            setMat4(gizmo_rotation->lines.shaderProgram, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "model", glm::mat4(1.0f));
            setVec3(gizmo_rotation->lines.shaderProgram, "color", gizmo_rotation->color_y);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_STRIP, 0, 3);
            glLineWidth(1.0);



        }else if(gizmo_rotation->z_move_selected){

            glBindVertexArray(gizmo_rotation->vao_z);
            glUseProgram(gizmo_rotation->axe_shader_program);
            setMat4(gizmo_rotation->axe_shader_program, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->axe_shader_program, "model", m_);
            setVec3(gizmo_rotation->axe_shader_program, "color", gizmo_rotation->color_z);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_LOOP, 0, 360);
            glLineWidth(1.0);

            /////////////////////////////////////////////


            float _l[] = {
                gizmo_rotation->lines.p1[0], gizmo_rotation->lines.p1[1], gizmo_rotation->lines.p1[2],
                pos_w[0], pos_w[1], pos_w[2],
                gizmo_rotation->lines.p2[0], gizmo_rotation->lines.p2[1], gizmo_rotation->lines.p2[2]
            };

            glBindVertexArray(gizmo_rotation->lines.vao);
            glBindBuffer(GL_ARRAY_BUFFER, gizmo_rotation->lines.vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*9, _l);

            glUseProgram(gizmo_rotation->lines.shaderProgram);
            setMat4(gizmo_rotation->lines.shaderProgram, "view", struct_project->scene_current->view->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "projection", struct_project->scene_current->projection->matrix);
            setMat4(gizmo_rotation->lines.shaderProgram, "model", glm::mat4(1.0f));
            setVec3(gizmo_rotation->lines.shaderProgram, "color", gizmo_rotation->color_z);

            glLineWidth(3.0);
            glDrawArrays(GL_LINE_STRIP, 0, 3);
            glLineWidth(1.0);
        }
    }
}

bool FGETranslationComponent::updateAxeRotation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT){
    if(gizmo_rotation->drag_selected || gizmo_rotation->x_move_selected || gizmo_rotation->y_move_selected || gizmo_rotation->z_move_selected || gizmo_rotation->w_move_selected){
        glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
        glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

        glm::mat4 _tm = getRotationToParent(struct_project->node_current->parent);

        glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        glm::vec3 p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.0), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.1), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        glm::mat4 r_, m_ = glm::translate(glm::mat4(1.0f), struct_project->node_current->transform.translate);
        m_ = glm::scale(m_, struct_project->node_current->transform.scale);

        if(gizmo_rotation->drag_selected){
            /*GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera->current_position, camera->current_target, camera->current_up);
            glm::vec3 pos_s = glm::project(pos_sel_obj,view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            pos_sel_obj = glm::unProject(glm::vec3(event->x()-bwspso_x, HEIGHT - event->y() -bwspso_y, pos_s[2]), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            updateGL();*/

        }else if(gizmo_rotation->x_move_selected){
            float t, _z = p2[0]-p1[0];

            if(_z==0.0){
                return false;
            }else{
                t = (pos_w[0]-p1[0])/_z;
            }
            gizmo_rotation->lines.p2[0] = pos_w[0];
            gizmo_rotation->lines.p2[1] = (p2[1]-p1[1])*t+p1[1];
            gizmo_rotation->lines.p2[2] = (p2[2]-p1[2])*t+p1[2];

            glm::vec3 o = pos_w;
            if(distanceBetweenTwoPoints(o, gizmo_rotation->lines.p2)<0.0002){
                return false;
            }
            glm::vec3 _p1 = gizmo_rotation->lines.p2;

            float e = sqrt((o[1]-_p1[1])*(o[1]-_p1[1])+(o[2]-_p1[2])*(o[2]-_p1[2]));

            if(e==0.0){
                return false;
            }
            float m = gizmo_rotation->diameter_after_scale;
            gizmo_rotation->lines.p2[1] = o[1]+(_p1[1]-o[1])*m/e;
            gizmo_rotation->lines.p2[2] = o[2]+(_p1[2]-o[2])*m/e;


            float cos2a;
            if(gizmo_rotation->lines.p1!=gizmo_rotation->lines.p2){
                cos2a = glm::dot(glm::normalize(gizmo_rotation->lines.p1-o), glm::normalize(gizmo_rotation->lines.p2-o));
                cos2a = glm::acos(cos2a);
                glm::vec3 f = glm::cross(gizmo_rotation->lines.p1-o, gizmo_rotation->lines.p2-o);
                cos2a = (cos2a*180.0)/3.14159265358979323846;

                if(f[0]<0) cos2a = 360-cos2a;

            }else cos2a = 0;

            float rd = fmod(gizmo_rotation->saved_rotation[0]+cos2a, 360.0);
            w_drag_cursor = glm::vec2(pos_x, pos_y);
            glm::vec4 tx = _tm/glm::vec4(1.0,0.0,0.0, 1.0);
            r_ = glm::toMat4(glm::angleAxis( glm::radians(rd-struct_project->node_current->transform.rotate[0]), glm::normalize(glm::vec3(tx[0],tx[1],tx[2]))));
            struct_project->node_current->transform.rotate[0] = rd;
            struct_project->node_current->transform.matrix_r = r_*struct_project->node_current->transform.matrix_r;
            struct_project->node_current->transform.matrix = m_*struct_project->node_current->transform.matrix_r;//*struct_project->node_current->transform.matrix;
            return true;
        }else if(gizmo_rotation->y_move_selected){
            float t, _z = p2[1]-p1[1];
            if(_z==0.0){//qDebug() << "S000";
                return false;
            }else{
                t = (pos_w[1]-p1[1])/_z;
            }
            gizmo_rotation->lines.p2[1] = pos_w[1];
            gizmo_rotation->lines.p2[0] = (p2[0]-p1[0])*t+p1[0];
            gizmo_rotation->lines.p2[2] = (p2[2]-p1[2])*t+p1[2];

            glm::vec3 o = pos_w;
            if(distanceBetweenTwoPoints(o, gizmo_rotation->lines.p2)<0.0002){
                return false;
            }
            glm::vec3 _p1 = gizmo_rotation->lines.p2;
            float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[2]-_p1[2])*(o[2]-_p1[2]));
            if(e==0.0){//qDebug() << "S000";
                return false;
            }
            float m = gizmo_rotation->diameter_after_scale;
            gizmo_rotation->lines.p2[0] = o[0]+(_p1[0]-o[0])*m/e;
            gizmo_rotation->lines.p2[2] = o[2]+(_p1[2]-o[2])*m/e;


            float cos2a;
            if(gizmo_rotation->lines.p1!=gizmo_rotation->lines.p2){
                cos2a = glm::dot(glm::normalize(gizmo_rotation->lines.p1-o), glm::normalize(gizmo_rotation->lines.p2-o));
                cos2a = glm::acos(cos2a);
                glm::vec3 f = glm::cross(gizmo_rotation->lines.p1-o, gizmo_rotation->lines.p2-o);
                cos2a = (cos2a*180.0)/3.14159265358979323846;
                if(f[1]<0) cos2a = 360-cos2a;

            }else cos2a = 0;

            float rd = fmod(gizmo_rotation->saved_rotation[1]+cos2a, 360.0);
            w_drag_cursor = glm::vec2(pos_x, pos_y);
            glm::vec4 tx = _tm/glm::vec4(0.0,1.0,0.0, 1.0);
            r_ = glm::toMat4(glm::angleAxis( glm::radians(rd-struct_project->node_current->transform.rotate[1]), glm::normalize(glm::vec3(tx[0],tx[1],tx[2]))));
            struct_project->node_current->transform.rotate[1] = rd;
            struct_project->node_current->transform.matrix_r = r_*struct_project->node_current->transform.matrix_r;
            struct_project->node_current->transform.matrix = m_*struct_project->node_current->transform.matrix_r;//*struct_project->node_current->transform.matrix;
            return true;
        }else if(gizmo_rotation->z_move_selected){
            float t, _z = p2[2]-p1[2];
            if(_z==0.0){//qDebug() << "S000";
                return false;
            }else{
                t = (pos_w[2]-p1[2])/_z;
            }
            gizmo_rotation->lines.p2[2] = pos_w[2];
            gizmo_rotation->lines.p2[0] = (p2[0]-p1[0])*t+p1[0];
            gizmo_rotation->lines.p2[1] = (p2[1]-p1[1])*t+p1[1];

            glm::vec3 o = pos_w;
            if(distanceBetweenTwoPoints(o, gizmo_rotation->lines.p2)<0.0002){
                return false;
            }
            glm::vec3 _p1 = gizmo_rotation->lines.p2;
            float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[1]-_p1[1])*(o[1]-_p1[1]));
            if(e==0.0){//qDebug() << "S000";
                return false;
            }
            float m = gizmo_rotation->diameter_after_scale;
            gizmo_rotation->lines.p2[0] = o[0]+(_p1[0]-o[0])*m/e;
            gizmo_rotation->lines.p2[1] = o[1]+(_p1[1]-o[1])*m/e;


            float cos2a;
            if(gizmo_rotation->lines.p1!=gizmo_rotation->lines.p2){
                cos2a = glm::dot(glm::normalize(gizmo_rotation->lines.p1-o), glm::normalize(gizmo_rotation->lines.p2-o));
                cos2a = glm::acos(cos2a);
                glm::vec3 f = glm::cross(gizmo_rotation->lines.p1-o, gizmo_rotation->lines.p2-o);
                cos2a = (cos2a*180.0)/3.14159265358979323846;
                if(f[2]<0) cos2a = 360-cos2a;

            }else cos2a = 0;

            float rd = fmod(gizmo_rotation->saved_rotation[2]+cos2a, 360.0);
            w_drag_cursor = glm::vec2(pos_x, pos_y);
            glm::vec4 tx = _tm/glm::vec4(0.0,0.0,1.0, 1.0);
            r_ = glm::toMat4(glm::angleAxis( glm::radians(rd-struct_project->node_current->transform.rotate[2]), glm::normalize(glm::vec3(tx[0],tx[1],tx[2]))));
            struct_project->node_current->transform.rotate[2] = rd;
            struct_project->node_current->transform.matrix_r = r_*struct_project->node_current->transform.matrix_r;
            struct_project->node_current->transform.matrix = m_*struct_project->node_current->transform.matrix_r;//*struct_project->node_current->transform.matrix;
            return true;
        }else if(gizmo_rotation->w_move_selected){
            /*gizmo_rotation->lines.p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            glm::vec3 o = pos_w;
            if(distanceBetweenTwoPoints(o, gizmo_rotation->lines.p2)<0.0002){
                return false;
            }
            glm::vec3 _p1 = gizmo_rotation->lines.p2;
            float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[1]-_p1[1])*(o[1]-_p1[1]));
            if(e==0.0){//qDebug() << "S000";
                return false;
            }
            float m = gizmo_rotation->diameter_after_scale;
            gizmo_rotation->lines.p2[0] = o[0]+(_p1[0]-o[0])*m/e;
            gizmo_rotation->lines.p2[1] = o[1]+(_p1[1]-o[1])*m/e;


            float cos2a;
            if(gizmo_rotation->lines.p1!=gizmo_rotation->lines.p2){
                cos2a = glm::dot(glm::normalize(gizmo_rotation->lines.p1-o), glm::normalize(gizmo_rotation->lines.p2-o));
                cos2a = glm::acos(cos2a);
                glm::vec3 f = glm::cross(gizmo_rotation->lines.p1-o, gizmo_rotation->lines.p2-o);
                cos2a = (cos2a*180.0)/3.14159265358979323846;
                if(f[2]<0) cos2a = 360-cos2a;

            }else cos2a = 0;

            float rd = fmod(gizmo_rotation->saved_rotation[0]+cos2a, 360.0);
            w_drag_cursor = glm::vec2(pos_x, pos_y);

            r_ = glm::toMat4(glm::angleAxis( glm::radians(rd-struct_project->node_current->transform.rotate[2]), glm::normalize(glm::vec3(0.0,0.0,1.0))));
            struct_project->node_current->transform.rotate[2] = rd;
            struct_project->node_current->transform.matrix_r = r_*struct_project->node_current->transform.matrix_r;
            struct_project->node_current->transform.matrix = m_*struct_project->node_current->transform.matrix_r;//*struct_project->node_current->transform.matrix;
            */return false;
        }

    }
}

bool FGETranslationComponent::selectGizmoRotation(FGEDataProject *struct_project, int pos_x, int pos_y, int WIDTH, int HEIGHT)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned char res[4];
    /*glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);
    glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(300.0f/HEIGHT, 300.0f/HEIGHT, 300.0f/HEIGHT));
*/

    glm::vec4 __p = struct_project->node_current->matrix*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 __t = glm::vec3(__p[0], __p[1], __p[2]);

    glm::vec3 pos_s = glm::project(__t, struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::mat4 m_ = glm::translate(glm::mat4(1.0f), pos_w);
    m_ = glm::scale(m_, glm::vec3(300.0f/HEIGHT, 300.0f/HEIGHT, 300.0f/HEIGHT));


    glm::vec3 _pick;
    glm::vec3 p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.0), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 p2 = glm::unProject(glm::vec3(pos_x, pos_y, 0.1), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


    glUseProgram(gizmo_rotation->selection_shader_program_w);
    setMat4(gizmo_rotation->selection_shader_program_w, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->selection_shader_program_w, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->selection_shader_program_w, "model", m_);
    setVec3(gizmo_rotation->selection_shader_program_w, "color", glm::vec3(0.6, 0.6, 0.6));
    setVec3(gizmo_rotation->selection_shader_program_w, "center", pos_s);

    glBindVertexArray(gizmo_rotation->vao_w);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glUseProgram(gizmo_rotation->selection_shader_program_center);
    setMat4(gizmo_rotation->selection_shader_program_center, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->selection_shader_program_center, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->selection_shader_program_center, "model", m_);
    setVec3(gizmo_rotation->selection_shader_program_center, "color", glm::vec3(0.5, 0.5, 0.5));
    setVec3(gizmo_rotation->selection_shader_program_center, "center", pos_s);

    glBindVertexArray(gizmo_rotation->vao_c);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glUseProgram(gizmo_rotation->selection_shader_program);
    setMat4(gizmo_rotation->selection_shader_program, "view", struct_project->scene_current->view->matrix);
    setMat4(gizmo_rotation->selection_shader_program, "projection", struct_project->scene_current->projection->matrix);
    setMat4(gizmo_rotation->selection_shader_program, "model", m_);

    setVec3(gizmo_rotation->selection_shader_program, "color", glm::vec3(1.0, 0.0, 0.0));
    glBindVertexArray(gizmo_rotation->vao_x);
    glLineWidth(10.0);
    glDrawArrays(GL_LINE_LOOP, 0, 360);

    setVec3(gizmo_rotation->selection_shader_program, "color", glm::vec3(0.0, 1.0, 0.0));
    glBindVertexArray(gizmo_rotation->vao_y);
    glDrawArrays(GL_LINE_LOOP, 0, 360);

    setVec3(gizmo_rotation->selection_shader_program, "color", glm::vec3(0.0, 0.0, 1.0));
    glBindVertexArray(gizmo_rotation->vao_z);
    glDrawArrays(GL_LINE_LOOP, 0, 360);



    //
    glReadPixels(pos_x, pos_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
    qDebug() << "ROT POS : (" << pos_x<< ", "<< pos_y<< ")";
    qDebug() << "ROTATE : (" << res[0]<< ", "<< res[1]<< ", "<< res[2]<< ")";

    glLineWidth(1.0);

    gizmo_rotation->drag_selected = false;
    gizmo_rotation->x_move_selected = false;
    gizmo_rotation->y_move_selected = false;
    gizmo_rotation->z_move_selected = false;


    w_drag_cursor = glm::vec2(pos_x, pos_y);

    if(res[0]==128 && res[1]==128 && res[2]==128){

        gizmo_rotation->drag_selected = true;
    }else if(res[0]==255 && res[1]==0 && res[2]==0){
        float t, _z = p2[0]-p1[0];
        if(_z==0.0){
            return false;
        }else{
            t = (pos_w[0]-p1[0])/_z;
        }
        gizmo_rotation->lines.p1[0] = pos_w[0];
        gizmo_rotation->lines.p1[1] = (p2[1]-p1[1])*t+p1[1];
        gizmo_rotation->lines.p1[2] = (p2[2]-p1[2])*t+p1[2];
        glm::vec3 o = pos_w;
        glm::vec3 _p1 = gizmo_rotation->lines.p1;
        float e = sqrt((o[1]-_p1[1])*(o[1]-_p1[1])+(o[2]-_p1[2])*(o[2]-_p1[2]));
        if(e==0.0){
            return false;
        }
        float m = gizmo_rotation->diameter_after_scale;
        gizmo_rotation->lines.p1[1] = o[1]+(_p1[1]-o[1])*m/e;
        gizmo_rotation->lines.p1[2] = o[2]+(_p1[2]-o[2])*m/e;

        gizmo_rotation->lines.p2 = gizmo_rotation->lines.p1;
        gizmo_rotation->saved_rotation = struct_project->node_current->transform.rotate;
        gizmo_rotation->x_move_selected = true;
        return true;
    }else if(res[0]==0 && res[1]==255 && res[2]==0){
        float t, _z = p2[1]-p1[1];
        if(_z==0.0){
            return false;
        }else{
            t = (pos_w[1]-p1[1])/_z;
        }
        gizmo_rotation->lines.p1[1] = pos_w[1];
        gizmo_rotation->lines.p1[0] = (p2[0]-p1[0])*t+p1[0];
        gizmo_rotation->lines.p1[2] = (p2[2]-p1[2])*t+p1[2];
        glm::vec3 o = pos_w;
        glm::vec3 _p1 = gizmo_rotation->lines.p1;
        float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[2]-_p1[2])*(o[2]-_p1[2]));
        if(e==0.0){
            return false;
        }
        float m = gizmo_rotation->diameter_after_scale;
        gizmo_rotation->lines.p1[0] = o[0]+(_p1[0]-o[0])*m/e;
        gizmo_rotation->lines.p1[2] = o[2]+(_p1[2]-o[2])*m/e;

        gizmo_rotation->lines.p2 = gizmo_rotation->lines.p1;
        gizmo_rotation->saved_rotation = struct_project->node_current->transform.rotate;
        gizmo_rotation->y_move_selected = true;
        return true;
    }else if(res[0]==0 && res[1]==0 && res[2]==255){
        float t, _z = p2[2]-p1[2];
        if(_z==0.0){
            return false;
        }else{
            t = (pos_w[2]-p1[2])/_z;
        }
        gizmo_rotation->lines.p1[2] = pos_w[2];
        gizmo_rotation->lines.p1[0] = (p2[0]-p1[0])*t+p1[0];
        gizmo_rotation->lines.p1[1] = (p2[1]-p1[1])*t+p1[1];
        glm::vec3 o = pos_w;
        glm::vec3 _p1 = gizmo_rotation->lines.p1;
        float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[1]-_p1[1])*(o[1]-_p1[1]));
        if(e==0.0){
            return false;
        }
        float m = gizmo_rotation->diameter_after_scale;
        gizmo_rotation->lines.p1[0] = o[0]+(_p1[0]-o[0])*m/e;
        gizmo_rotation->lines.p1[1] = o[1]+(_p1[1]-o[1])*m/e;

        gizmo_rotation->lines.p2 = gizmo_rotation->lines.p1;
        gizmo_rotation->saved_rotation = struct_project->node_current->transform.rotate;
        gizmo_rotation->z_move_selected = true;
        return true;
    }else if(res[0]==64 && res[1]==64 && res[2]==64){
        qDebug() << "S W ";
        /*gizmo_rotation->lines.p1 = glm::unProject(glm::vec3(pos_x, pos_y, 0.3), struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        glm::vec3 o = pos_w;
        glm::vec3 _p1 = gizmo_rotation->lines.p1;
        float e = sqrt((o[0]-_p1[0])*(o[0]-_p1[0])+(o[1]-_p1[1])*(o[1]-_p1[1]));
        if(e==0.0){
            return false;
        }
        float m = gizmo_rotation->diameter_after_scale;
        gizmo_rotation->lines.p1[0] = o[0]+(_p1[0]-o[0])*m/e;
        gizmo_rotation->lines.p1[1] = o[1]+(_p1[1]-o[1])*m/e;

        gizmo_rotation->lines.p2 = gizmo_rotation->lines.p1;
        gizmo_rotation->saved_rotation = struct_project->node_current->transform.rotate;
        gizmo_rotation->w_move_selected = true;*/
        return false;
    }
}

////////////////////////////////end rotation gizmo ///////////////////////////////


bool FGETranslationComponent::getCurrentTransformationMode(int _ctm){
    if(current_transformation_mode==_ctm) return true;
    else return false;
}

void FGETranslationComponent::setCurrentTransformationMode(int _ctm){
    current_transformation_mode=_ctm;
}
bool FGETranslationComponent::isDragTranslation(){
    if(x_move_selected || y_move_selected || z_move_selected) return true;
    else return false;
}
bool FGETranslationComponent::isDragRotaion(){
    if(gizmo_rotation->x_move_selected || gizmo_rotation->y_move_selected || gizmo_rotation->z_move_selected || gizmo_rotation->w_move_selected || gizmo_rotation->drag_selected) return true;
    else return false;
}
float FGETranslationComponent::distanceBetweenTwoPoints(glm::vec3 p1, glm::vec3 p2){
    if(p1==p2) return 0.2;
    return sqrt(((p2[0]-p1[0])*(p2[0]-p1[0]))+((p2[1]-p1[1])*(p2[1]-p1[1]))+((p2[2]-p1[2])*(p2[2]-p1[2])));
}


glm::mat4 FGETranslationComponent::RotationQuat(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT){
    glm::vec3 _u = camera->current_position-camera->current_target;
    glm::vec3 pos_s = glm::project(struct_project->node_current->transform.translate,struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), glm::mat4(1.0f), struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


    float cos2 = glm::dot(glm::normalize(_u), glm::normalize(glm::vec3(1.0,0.0,1.0)));
    cos2 = glm::acos(cos2);
    cos2 = (cos2*180.0)/3.14159265358979323846;

    glm::vec3 f = glm::cross(glm::normalize(_u), glm::normalize(glm::vec3(1.0,0.0,1.0)));
    qDebug() << "* f[0] " << f[0];
    qDebug() << "* f[1] " << f[1];
    qDebug() << "* f[2] " << f[2];

    //glm::mat4 m_ = glm::rotate(glm::mat4(1.0f), cos2, f);
    //glm::quat q(glm::cos(cos2/2), f[0]*glm::sin(cos2/2), f[1]*glm::sin(cos2/2), f[2]*glm::sin(cos2/2));
    glm::mat4 m_ = glm::toMat4(glm::angleAxis( glm::radians(cos2), glm::normalize(f)));
    return glm::translate(glm::mat4(1.0f), pos_w)*m_;
}

glm::mat4 FGETranslationComponent::RotationRot(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT){
    glm::vec3 pos_s = glm::project(struct_project->node_current->transform.translate,struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), glm::mat4(1.0f), struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 _u = camera->current_position-pos_w;


    float cos2 = glm::dot(glm::normalize(glm::vec3(0.0,1.0,0.0)), glm::normalize(_u));
    cos2 = glm::acos(cos2);
    cos2 = 270-(cos2*180.0)/3.14159265358979323846;

    glm::vec3 f = glm::cross(glm::normalize(glm::vec3(0.0,1.0,0.0)), glm::normalize(_u));
    qDebug() << "* f[0] " << f[0];
    qDebug() << "* f[1] " << f[1];
    qDebug() << "* f[2] " << f[2];

    glm::mat4 m_ = glm::rotate(glm::mat4(1.0f), glm::radians(cos2), f);
    return glm::translate(glm::mat4(1.0f), pos_w)*m_;
}

glm::mat4 FGETranslationComponent::RotationOri(FGECamera *camera, FGEDataProject *struct_project, int WIDTH, int HEIGHT){
    glm::vec3 pos_s = glm::project(struct_project->node_current->transform.translate,struct_project->scene_current->view->matrix, struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.2), glm::mat4(1.0f), struct_project->scene_current->projection->matrix, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 _gu = pos_w-camera->current_position;
    glm::vec3 _u = camera->current_up;
    _u[0] = -_u[0];
    _u[1] = -_u[1];
    _u[2] = -_u[2];
    glm::mat4 m_ = glm::orientation(glm::normalize(glm::vec3(1.0,1.0,1.0)), glm::normalize(glm::vec3(0.0,0.0,1.0)));
    return glm::translate(glm::mat4(1.0f), pos_w)*m_;
}

glm::quat FGETranslationComponent::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
    start = glm::normalize(start);
    dest = glm::normalize(dest);

    float cosTheta = glm::dot(start, dest);
    glm::vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
        if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = glm::normalize(rotationAxis);
        return glm::angleAxis(glm::radians(180.0f), rotationAxis);
    }

    rotationAxis = glm::cross(start, dest);

    float s = sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;

    return glm::quat(
        s * 0.5f,
        rotationAxis.x * invs,
        rotationAxis.y * invs,
        rotationAxis.z * invs
    );

}


void FGETranslationComponent::setMat4(unsigned int sh, const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(sh, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void FGETranslationComponent::setVec3(unsigned int sh, const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(sh, name.c_str()), 1, &value[0]);
}
void FGETranslationComponent::setFloat(unsigned int sh, const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(sh, name.c_str()), value);
}

glm::vec3 FGETranslationComponent::normal(glm::vec3 n)
{
    float v = glm::max(n[0]*n[0], glm::max(n[1]*n[1], n[2]*n[2]));
    v = sqrt(v)*2;
    n[0] = n[0]/v;
    n[1] = n[1]/v;
    n[2] = n[2]/v;
    return n;
}

glm::vec4 FGETranslationComponent::intersection2DLineRect(float s, float b, int width, int height){
    bool fr = false;
    glm::vec4 r;
    float y, x;

    {
        x = 0.0;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = 0.0;
                r[1] = y;
                fr = true;
                //qDebug() << "1 ";
            }else {
                r[2] = 0.0;
                r[3] = y;//qDebug() << "01 ";
                return r;
            }
        }
    }
    {
        y = 0.0;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = 0.0;
                fr = true;//qDebug() << "2 ";
            }else {
                r[2] = x;
                r[3] = 0.0;//qDebug() << "02 ";
                return r;
            }
        }
    }
    {
        x = width;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = width;
                r[1] = y;//qDebug() << "3 ";
                fr = true;
            }else {
                r[2] = width;
                r[3] = y;//qDebug() << "03 ";
                return r;
            }
        }
    }
    {
        y = height;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = height;
                fr = true;//qDebug() << "4 ";
            }else {
                r[2] = x;
                r[3] = height;//qDebug() << "04 ";
                return r;
            }
        }
    }
//qDebug() << "5 ";
    return glm::vec4(0.0,0.0,0.0,0.0);
}
