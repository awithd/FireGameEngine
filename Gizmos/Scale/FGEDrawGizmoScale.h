#ifndef FGEDRAWGIZMOSCALE_H
#define FGEDRAWGIZMOSCALE_H

#include <Gizmos/Scale/FGEGizmoScaleDefinition.h>

class FGESTRDEquation2DLine{
 public:
    float s;
    float b;
    float flot;
    float clot;
    glm::vec3 world_point_a, world_point_b, world_c;
    glm::vec3 screen_point_a, screen_point_b, screen_c;

};

class FGECursorEventScale{
 public:
    glm::vec2 press_select;
    glm::vec2 release_select;
    glm::vec2 move_select;

};

class FGEDrawGizmoScale
{
public:
    FGEDrawGizmoScale(OpenGLFunctions *f, FGEGizmoConstraintAxis *constraint_axis, FGESUBSelectedTransformationMode *mode);

    ///
    /// \brief drawAxes draw simple scale gizmo.
    void draw(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);

    ///
    /// \brief drawAxes draw x, y, z, xy, xz, yz axes when picked.
    void drawAxes(OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int WIDTH, int HEIGHT);

    ///
    /// \brief select used to select one of the axes x, y, z, xy, xz, yz when picked.
    bool select(FGERenderTarget *render_target, QOpenGLContext *oglc, OpenGLFunctions *f, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, int mx, int my, int WIDTH, int HEIGHT);

    ///
    /// \brief updateTransformation update transformation & 3d position click when drag mouse over axe gizmo
    void updateTransformation(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT);



    FGEGLSL                 *shader;
    FGEGizmosScaleItem      *translation_item;
    FGEGizmoConstraintAxis  *constraint_axis;
    glm::vec3               current_pick;
    glm::vec3               press_normal_plane;

    ///
    /// \brief sel_transf_mode when user choose global ,local, screen modes.
    FGESUBSelectedTransformationMode *sel_transf_mode;



private:
    void drawGizmoScale(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom, glm::vec3 &center_screen);
    void translateToScreen(OpenGLFunctions *f, FGETransformation *transform, float scaleFactor, bool is_selection, bool is_perspective, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, int sx);
    void drawXYAxes(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &ortho_, glm::mat4 &model, glm::vec3 &pos_c, glm::mat4 &factorZoom);
    void drawXAxe(OpenGLFunctions *f, glm::mat4 &ModelViewProjectionMatrix, glm::vec3 color);
    FGESTRDEquation2DLine current_eq_2d_line;
    bool getPositionPickOnLocal(bool first, glm::vec3 &pos, FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 cursor, int WIDTH, int HEIGHT);
    void drawXYZAxesSelection(OpenGLFunctions *f, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, glm::mat4 &factorZoom, glm::vec3 &center_screen);

};

#endif // FGEDRAWGIZMOSCALE_H
