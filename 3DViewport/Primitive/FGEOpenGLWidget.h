#ifndef FGEOPENGLWIDGET_H
#define FGEOPENGLWIDGET_H

#define GLM_ENABLE_EXPERIMENTAL



#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEDefinition.h>
#include <Core/FGEQGLFunctions.h>
#include <3DViewport/Primitive/FGECoreRenderPrimitive.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <QPainter>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <stdio.h>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QOpenGLVersionFunctionsFactory>

#include <StructData/FGEDataProject.h>
#include <Camera/FGECamera.h>
#include <GLSL/FGEGLSL.h>
#include <3DViewport/Primitive/FGEStateOpperations.h>
#include <RenderTarget/FGEMultisimpleRenderTarget.h>
#include <RenderTarget/FGERenderTarget.h>
#include <Gizmos/FGEGizmos.h>
#include <Light/FGELight.h>
#include <3DViewport/Primitive/FGECreateCubeModel.h>
#include <View/FGEViewOpperation.h>
#include <Text/FGEText.h>
#include <Grid/FGEGrid.h>
#include <QTextDocument>
#include <QSurfaceFormat>
#include <QOffscreenSurface>
#include <3DViewport/Primitive/FGEOpenGLWidgetActions.h>
#include <3DViewport/AddObject/FGECreateNewObject.h>
#include <Geometry/Extrude/FGEExtrudeLines.h>
#include <Geometry/Fill/FGEFill.h>
#include <Geometry/Delete/FGEDeleteFaces.h>
#include <3DViewport/SculptMesh/FGESculptItem.h>
#include <3DViewport/SculptMesh/FGESculptMesh.h>
#include <3DViewport/Armature/FGEPaintingSkinWeights.h>

#include <3DViewport/Armature/FGEArmatureEdit.h>
#include <3DViewport/Armature/FGEArmaturePose.h>


#include <3DViewport/Controller/FGEObjectSelectorController.h>



#include <Selector/FGEEditMeshSelector.h>
#include <Selector/FGEMeshSelector.h>
#include <Selector/FGESelectionArmature.h>
#include <Selector/FGESelectionArmatureEditable.h>
#include <Selector/FGESelectionArmaturePaintWeight.h>

#include <StructData/Skin/FGEDataSkinConfiguration.h>


class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class FGEOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit FGEOpenGLWidget(FGETriggerFunction *trigger, FGECreateNewObject *create_new_object, FGEDataProject *sp, QString name, void *dock, QWidget *parent = nullptr);
    ~FGEOpenGLWidget();
    OpenGLFunctions * openGLFunctions() const;
    void triggerUpdateGL();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void addNewCube();
    void setDisplayMode(int value);
    void findNewAngles(FGEDataBone *endEffector, FGEDataBone *base, glm::vec3 target, int iterations);
    void drawLegend(QPoint p, QPainter &painter);
    GLint getMaxSamples();

    void setCurrentCamera(FGEDataCamera* camera);

    QWidget *parent;
    int WIDTH, HEIGHT;
    FGETriggerFunction *trigger;

    FGEDataCamera *current_data_camera;
    FGEDataCamera *data_camera;

    int initialized;
    FGEDataScene *scene;
    FGEDataProject *data_project;
    OpenGLFunctions *f;
    FGECamera *camera;
    FGEGLSL *shader;
    //FGECoreRenderPrimitive *render_primitive;


    FGERenderTarget *render_tarjet;
    FGERenderTarget *render_tarjet_selection;
    FGERenderTarget *render_tarjet_outline;

    GLuint shader_program_selection;

    FGEGizmos *gizmos;
    FGESculptMesh *sculpt;
    FGEPaintingSkinWeights *painting_skin_weights;
    FGELight *light_tool;

    FGEEditMeshSelector *selection_mesh_editable;
    FGESelectionArmature *selection_armature;
    FGESelectionArmatureEditable *selection_armature_editable;
    FGESelectionArmaturePaintWeight *selection_armature_paint_weight;


    FGEViewOpperation *view_opp;
    FGEText *draw_text;
    FGEGrid *grid;
    FGEOpenGLWidgetActions *area_menu;
    FGECreateNewObject *create_new_object;
    FGEItemCreateNewObject *item_create_new_object;

    int driver_behavior;

    int edit_mode;
    QString name_3dview;

    FGETransformation *temp_transformation;
    glm::mat4 rr_old_trans;
    glm::vec3 rr_pos;

    void *dock_parent;
    void initializeScene(FGEDataProject *data_project);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void initObjectModule();

    bool CCDMode(FGEDataBone* endEffector, FGEDataBone* base, glm::vec4 &point_g_target);


    void restorBonePosition(FGEDataBone *first_child, float length, glm::vec4 &_psm0, glm::vec4 &_psm1);

    FGEStateOpperations *opperations_state;
    FGEArmatureEdit *armature_edit;
    FGEArmaturePose *armature_pose;
    FGEObjectSelectorController *object_module;

    FGEDataSkinConfiguration *skin_conf;



    FGEOpenGLSceneRenderer *render_device;
    FGEPrepareGLBuffer *buffer_gl;

private:

    bool gizmoMeshPressMouse(glm::vec2 &curs_pos);
    bool gizmoMeshMoveMouse(glm::vec2 &curs_pos);
    bool gizmoMeshReleaseMouse(glm::vec2 &curs_pos);




    bool selectionEditPressMouse(glm::vec2 &curs_pos);
    bool selectionEditMoveMouse(glm::vec2 &curs_pos);
    bool selectionEditReleaseMouse(glm::vec2 &curs_pos);

    bool gizmoArmaturePressMouse(glm::vec2 &curs_pos);
    bool gizmoArmatureMoveMouse(glm::vec2 &curs_pos);
    bool sculptPressMouse(glm::vec2 &curs_pos);
    bool sculptMoveMouse(glm::vec2 &curs_pos);


    bool selectionArmaturePosePressMouse(glm::vec2 &curs_pos);
    bool selectionArmatureEditPressMouse(glm::vec2 &curs_pos);
    bool selectArmaturePressMouse(glm::vec2 &curs_pos);


    bool paintWeightsMouse(glm::vec2 &curs_pos);

public slots:
    void view_oppUpdateCameraToSelectedAxe();
    void newBufferAdded();
    void slotUpdateGL();
    void updateInit();
    void updateAllWIdgetsOpenGl();
    void switch3DViewToEditMode(QString name_3dview, int type_mode);
    void switch3DViewToArmatureEditMode(QString name_3dview, int type_mode);
    void switch3DViewToSculptMode(QString name_3dview, void *item);

    void updateMeshSelect(QString name_3dview, int mesh_select);
    void updateInteractionModePrimitive(QString name_3dview, int interaction_mode);
};
#endif // FGEOPENGLWIDGET_H
