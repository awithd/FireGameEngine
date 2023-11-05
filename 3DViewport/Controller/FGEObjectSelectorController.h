#ifndef FGEOBJECTSELECTORCONTROLLER_H
#define FGEOBJECTSELECTORCONTROLLER_H

#define GLM_ENABLE_EXPERIMENTAL



#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEDefinition.h>
#include <Core/FGEQGLFunctions.h>
#include <3DViewport/Primitive/FGECoreRenderPrimitive.h>
#include <StructData/FGEDataCamera.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <Gizmos/FGEGizmos.h>
#include <Selector/FGEMeshSelector.h>

/**
 * @brief The FGEObjectSelectorController class manages user interactions with both Gizmos and Meshes.
 *
 * This class is responsible for handling mouse click, move, and release events on Gizmos
 * and Meshes based on the specified interaction type. It provides a unified interface for
 * selecting and interacting with objects in the scene.
 *
 * The FGEObjectSelectorController allows you to seamlessly switch between Gizmo and Mesh
 * interaction modes, making it a versatile tool for various interaction scenarios.
 */

class FGEObjectSelectorController
{
public:
    FGEObjectSelectorController(FGEDataProject *data_project, FGEGizmos *gizmos);

    bool gizmoPressMouse(OpenGLFunctions *glf, glm::vec2 &curs_pos);
    bool gizmoMoveMouse(OpenGLFunctions *f, glm::vec2 &curs_pos);
    bool gizmoReleaseMouse();

    bool objectPressMouse(OpenGLFunctions *f, glm::vec2 &curs_pos);
    bool objectMoveMouse(OpenGLFunctions *f, glm::vec2 &curs_pos);
    bool objectReleaseMouse(OpenGLFunctions *f, glm::vec2 &curs_pos);

    void setTransformation(FGETransformation *transformation);


    /**
     * @brief Renders the Gizmo for interaction and selection.
     *
     * This function is responsible for rendering the Gizmo on the screen based on the selected
     * nodes and their transformations. It prepares the rendering context, including OpenGL and
     * QPainter, and then calls the appropriate methods to display the Gizmo accordingly.
     *
     * @param f A pointer to the OpenGLFunctions object for rendering.
     * @param painter A QPainter object for rendering 2D elements.
     */
    void renderGizmo(OpenGLFunctions *f, QPainter &painter);


    void initTransformation();

    FGEMeshSelector *selection_mesh;
    FGEDataProject *data_project;
    FGETransformation *transformation;
    FGETransformation *transformation_forshow;
    FGEGizmos *gizmos;

    bool release_st;

    glm::vec3 veiw_pos;
    FGELight *light_tool;
    glm::vec2 cursor;
    FGEDataCameraView *view;
    FGEDataCameraProjection *projection;
    GLuint shader_program_selection;
    QOpenGLContext *oglc;
    FGERenderTarget *render_tarjet_selection;
    GLuint WIDTH;
    GLuint HEIGHT;
    FGEStateOpperations *opperations_state;
    glm::vec2 curs_pos;
    void *slf;

    glm::mat4 hcm;

private:
    bool _isReadyForOperation();

};

#endif // FGEOBJECTSELECTORCONTROLLER_H
