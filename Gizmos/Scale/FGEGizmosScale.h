#ifndef FGEGIZMOSSCALE_H
#define FGEGIZMOSSCALE_H



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

class FGEGizmosScale
{
public:
    FGEGizmosScale(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode);
    glm::mat4 etter_udyy(FGEDataNode *nd);

    void draw2DGrid(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &projection);

    bool getCurrentTransformationMode(int _ctm);
    void setCurrentTransformationMode(int _ctm);
    bool isDragScale();
    glm::vec4 intersection2DLineRect(float s, float b, int width, int height);
    void updateAxesScale(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT);
    glm::vec3 getVertical2DLine(glm::vec3 p1, glm::vec3 p2);
    void clearDrag();
    bool GetRayToLineSegmentIntersection(glm::vec2 rayOrigin, glm::vec2 rayDirection, glm::vec2 point1, glm::vec2 point2, glm::vec2 point);
    glm::vec2 NormalizeVector(glm::vec2 pt);
    glm::vec2 GetRayIntersectionPoint(glm::vec2 origin, glm::vec2 vector, double distance);
    glm::vec4 intersection2DRayRect(glm::vec2 p1, glm::vec2 p2, int width, int height);
    FGEGizmosScaleItem *translation_item;
    FGEGLSL *shader;
    int transformation_type;


    glm::mat4 __grid_model;

    glm::vec2 w_drag_cursor;
    FGECursorEventScale cursor_event;
    glm::vec2 tyrt;

    int current_transformation_mode;
    FGESTRDEquation2DLine current_eq_2d_line;

    glm::vec3 point_1,point_2,point_3;

    glm::vec3 linepoint_1,linepoint_2;

    FGESUBSelectedTransformationMode *sel_transf_mode;

private:
    glm::mat4 getRotationMatrix2V(glm::vec3 pos, glm::vec3 v1, glm::vec3 eyeu);


};

#endif // FGEGIZMOSSCALE_H
