#ifndef FGEUVEOPENGLWIDGET_H
#define FGEUVEOPENGLWIDGET_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Core/FGEQGLFunctions.h>
#include <UVEditor/Primitive/FGEUVECoreRender.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/closest_point.hpp>



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
#include <RenderTarget/FGEMultisimpleRenderTarget.h>
#include <RenderTarget/FGERenderTarget.h>
#include <Gizmos/FGEGizmos.h>
#include <Light/FGELight.h>
#include <UVEditor/Selection/FGEUVEEditModeSelection.h>
#include <Text/FGEText.h>
#include <Grid/FGESquareGrid.h>
#include <QTextDocument>
#include <QSurfaceFormat>
#include <QOffscreenSurface>
#include <UVEditor/Primitive/FGEUVEOpenGLWidgetActions.h>
#include <Geometry/Extrude/FGEExtrudeLines.h>
#include <Geometry/Fill/FGEFill.h>
#include <Geometry/Delete/FGEDeleteFaces.h>
#include <3DViewport/SculptMesh/FGESculptMesh.h>
#include <3DViewport/SculptMesh/FGESculptItem.h>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;


class FGEUVEOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit FGEUVEOpenGLWidget(FGETriggerFunction *trigger, FGEDataProject *sp, QString name, void *dock, QWidget *parent = nullptr);
    ~FGEUVEOpenGLWidget();

    void initProjection();
    void swappeProjection(int mode);
    OpenGLFunctions * openGLFunctions() const;
    void triggerUpdateGL();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void addNewCube();
    void setDisplayMode(int value);

    void drawLegend(QPoint p, QPainter *painter);
    GLint getMaxSamples();

    QWidget *parent;
    int WIDTH, HEIGHT;
    FGETriggerFunction *trigger;
    FGEDataCameraProjection projection;
    FGEDataCameraView view;
    int initialized;
    FGEDataScene *scene;
    FGEDataProject *data_project;
    OpenGLFunctions *f;
    FGECamera *camera;
    FGEGLSL *shader;
    FGEUVECoreRender *render_primitive;


    FGERenderTarget *render_tarjet;
    FGERenderTarget *render_tarjet_selection;
    FGERenderTarget *render_tarjet_outline;

    GLuint shader_program_selection;

    FGEGizmos *gizmos;
    FGESculptMesh *sculpt;
    FGELight *light_tool;

    FGEUVEEditModeSelection *select_edit_mode;
    FGEText *draw_text;
    FGESquareGrid *grid;
    FGEUVEOpenGLWidgetActions *area_menu;


    int display_mode;
    int edit_mode;
    QString name_3dview;

    FGETransformation *temp_transformation;
    glm::mat4 rr_old_trans;
    glm::vec3 rr_pos;

    FGEDataTexture * background_texture;

    void *dock_parent;
    void initializeScene(FGEDataProject *data_project);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawBackground(OpenGLFunctions *_q, FGEGLSL *shader);
    void initBackgroundTexture();
    void initGBackgroundTexture();
    void createBackgroundBufferData(OpenGLFunctions *q, FGEGLSL *shader, const char *vertexPath, const char *fragmentPath);
    uint background_shader_program;
    uint background_VAO, background_VBO;


private:

public slots:
    void newBufferAdded();
    void slotUpdateGL();
    void updateInit();
    void updateAllWIdgetsOpenGl();
    void switch3DViewToEditMode(QString name_3dview, int type_mode);
    void switch3DViewToSculptMode(QString name_3dview, void *item);
};
#endif // FGEUVEOPENGLWIDGET_H
