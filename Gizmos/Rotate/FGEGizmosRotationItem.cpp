#include "FGEGizmosRotationItem.h"

FGEGizmosRotationItem::FGEGizmosRotationItem(OpenGLFunctions *f)
{
    FGE3DGeometryCircle circle;
    FGE3DGeometryLine line;

    rxm = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rym = glm::mat4(1.0f);
    rzm = glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f),  glm::vec3(1.0f, 0.0f, 0.0f));

    // MESH
    circle.getBuffer(mesh_circle, 0.004, 360);    //transformation.scale3D(__cone, 0, 9, 0.5, 0.5, 0.5);

    f->glGenVertexArrays(1, &vao_circle);
    f->glGenBuffers(1, &vbo_circle);
    f->glBindVertexArray(vao_circle);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_circle);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_circle.size()*sizeof(float), &mesh_circle[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

    line.setVertex(glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.004,0.0));
    line.getBuffer(mesh_line);

    f->glGenVertexArrays(1, &vao_line);
    f->glGenBuffers(1, &vbo_line);
    f->glBindVertexArray(vao_line);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_line.size()*sizeof(float), &mesh_line[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

    xyz_axes.push_back(0.0f);
    xyz_axes.push_back(0.0f);
    xyz_axes.push_back(0.0f);
    xyz_axes.push_back(0.0f);
    xyz_axes.push_back(0.0f);
    xyz_axes.push_back(0.0f);

    f->glGenVertexArrays(1, &vao_xyza);
    f->glGenBuffers(1, &vbo_xyza);
    f->glBindVertexArray(vao_xyza);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_xyza);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, &xyz_axes[0], GL_STREAM_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);


    FGE3DGeometrySphere sphere;
    sphere.getBuffer(mesh_sphere, 0.1, 60, 60, false, object_count_triangle);

    f->glGenVertexArrays(1, &vao_sphere);
    f->glGenBuffers(1, &vbo_sphere);
    f->glBindVertexArray(vao_sphere);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_sphere.size()*sizeof(float), &mesh_sphere[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindVertexArray(0);



    std::vector <float> _vlines;
    _vlines.push_back(1.0f);
    _vlines.push_back(0.0f);
    _vlines.push_back(0.0f);
    _vlines.push_back(2.0f);
    _vlines.push_back(0.0f);
    _vlines.push_back(0.0f);
    _vlines.push_back(3.0f);
    _vlines.push_back(0.0f);
    _vlines.push_back(0.0f);

    f->glGenVertexArrays(1, &vao_vlines);
    f->glGenBuffers(1, &vbo_vlines);
    f->glBindVertexArray(vao_vlines);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_vlines);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, &_vlines[0], GL_STREAM_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);


    count_angle=0;
    f->glGenVertexArrays(1, &vao_angle);
    f->glGenBuffers(1, &vbo_angle);
    f->glBindVertexArray(vao_angle);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_angle);
    f->glBufferData(GL_ARRAY_BUFFER, sizeof(float)*((3*360*5)+6), NULL, GL_STREAM_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
}
