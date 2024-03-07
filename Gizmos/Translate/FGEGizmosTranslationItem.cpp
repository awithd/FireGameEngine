#include "FGEGizmosTranslationItem.h"

FGEGizmosTranslationItem::FGEGizmosTranslationItem(OpenGLFunctions *f)
{
    FGE3DGeometryCone cone;
    FGE3DGeometryLine line;
    FGE3DGeometryPlane plane;
    FGE3DGeometryGridLines plane10;

    rxm = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rym = glm::mat4(1.0f);
    rzm = glm::rotate(glm::mat4(1.0f),  glm::radians(90.0f),  glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0.008, 0.008, 0.0));
    this->txymp = glm::rotate(m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    this->tzxmp = glm::translate(glm::mat4(1.0f), glm::vec3(0.008, 0.0, 0.008));
    m = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.008, 0.008));
    this->tyzmp = glm::rotate(m, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


    this->rxy = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //this->tyzmp = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //this->tyzmp = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));



    FGE3DGeometryTransformation transformation;

    cone.setNormal(false);

    // MESH
    cone.getBuffer(mesh_cone, 0.0016, 0.005, 10, false, object_count_triangle);
    transformation.translate3D(mesh_cone, 0, 3, 0.0, 0.015, 0.0);
    //transformation.scale3D(__cone, 0, 9, 0.5, 0.5, 0.5);

    f->glGenVertexArrays(1, &vao_cone);
    f->glGenBuffers(1, &vbo_cone);
    f->glBindVertexArray(vao_cone);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_cone);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_cone.size()*sizeof(float), &mesh_cone[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

    line.setVertex(glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,0.015,0.0));
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


    plane.getBuffer(mesh_plane, 0.005, 1, 0.005, 1, mpcv, 1);
    //transformation.translate3D(mesh_plane, 0, 3, 0.0050, 0.0000, -0.0050);
    //transformation.scale3D(__cone, 0, 9, 0.5, 0.5, 0.5);

    f->glGenVertexArrays(1, &vao_plane);
    f->glGenBuffers(1, &vbo_plane);
    f->glBindVertexArray(vao_plane);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_plane);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_plane.size()*sizeof(float), &mesh_plane[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);

    plane10.getBuffer(mesh_plane10, 200, 200, 200, 200, mpcv10);
    //transformation.translate3D(mesh_plane10, 0, 3, -5.0, 0.0, -5.0);
    //transformation.scale3D(__cone, 0, 9, 0.5, 0.5, 0.5);

    f->glGenVertexArrays(1, &vao_plane10);
    f->glGenBuffers(1, &vbo_plane10);
    f->glBindVertexArray(vao_plane10);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_plane10);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_plane10.size()*sizeof(float), &mesh_plane10[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);


    FGE3DGeometrySphere sphere;
    sphere.getBuffer(mesh_sphere, 0.003, 60, 60, false, sphere_count_triangle);

    f->glGenVertexArrays(1, &vao_sphere);
    f->glGenBuffers(1, &vbo_sphere);
    f->glBindVertexArray(vao_sphere);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo_sphere);
    f->glBufferData(GL_ARRAY_BUFFER, mesh_sphere.size()*sizeof(float), &mesh_sphere[0], GL_STATIC_DRAW);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    f->glEnableVertexAttribArray(0);
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindVertexArray(0);
}
