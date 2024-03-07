#include "FGEUVEOpenGLWidget.h"

FGEUVEOpenGLWidget::FGEUVEOpenGLWidget(FGETriggerFunction *trigger, FGEDataProject *data_project, QString name, void *dock, QWidget *parent) : QOpenGLWidget(parent)
{
    this->dock_parent = dock;
    this->initialized=0;
    this->scene = NULL;
    this->parent = parent;
    this->name_3dview = name;

    this->trigger = trigger;
    this->data_project = data_project;
    this->display_mode = 3;
    this->edit_mode = 1;

    this->render_primitive = new FGEUVECoreRender();

    this->temp_transformation = new FGETransformation(NULL, NULL);


    QOffscreenSurface surf;
    surf.create();

    QOpenGLContext ctx;
    ctx.create();
    ctx.makeCurrent(&surf);

    qDebug () <<"OpenGL version : "<< (const char*)ctx.functions()->glGetString(GL_VERSION);

    QSurfaceFormat fmt;
    fmt.setSamples(8);
    setFormat(fmt);



    //this->data_project->textur++;
    //this->struct_project_textur = this->data_project->textur;

}

FGEUVEOpenGLWidget::~FGEUVEOpenGLWidget()
{
    //trans_comp->~FGETranslationComponent();

}

void FGEUVEOpenGLWidget::newBufferAdded(){
    /*makeCurrent();
    this->render_primitive->updateBuffer(this->f);
    update();*/
    doneCurrent();
}
void FGEUVEOpenGLWidget::slotUpdateGL(){
    //qDebug() << "uuuuuuuuuuuu  slotUpdateGL";
    update();
}

void FGEUVEOpenGLWidget::triggerUpdateGL(){

    //FGESceneOS *cursc = struct_project->scene_current;
    /*if(this->projection->is_perspective){
        //cursc->projection->scaleFactor = 1.0f;
        //qDebug() << "i" << cursc->projection->perspective.near;
        this->projection->matrix = glm::perspective(
                    this->projection->perspective.fovy,
                    this->projection->perspective.aspect,
                    this->projection->perspective.near,
                    this->projection->perspective.far
        );
    }else{
        //qDebug() << "m";

        this->projection->scaleFactor = this->camera->SUPER_VAL_ZOOM/glm::length(this->camera->current_eye);

        this->projection->matrix = glm::ortho(
                    this->projection->ortho.left,
                    this->projection->ortho.right,
                    this->projection->ortho.bottom,
                    this->projection->ortho.top,
                    this->projection->ortho.znear,
                    this->projection->ortho.zfar
        );
    }*/

    //qDebug() << "v";
    update();
}


void FGEUVEOpenGLWidget::setDisplayMode(int value)
{
    this->display_mode = value;
}

OpenGLFunctions * FGEUVEOpenGLWidget::openGLFunctions() const
{    
    //return context()->versionFunctions<QOpenGLFunctions_3_0>();
    return QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_0>();
}

void FGEUVEOpenGLWidget::initializeGL()
{ //qDebug() << "ffff";

    initializeOpenGLFunctions();
    this->f = openGLFunctions();

    this->f->glEnable(GL_MULTISAMPLE);





    this->camera = new FGECamera();
    this->camera->init(&this->view, &this->projection);
    this->camera->key_shift = false;

    this->camera->current_position = glm::vec3(0.0f, 0.0f,  0.0f);
    this->camera->current_eye = glm::vec3(0.5f, 0.5f,  1.0f);
    this->camera->current_target = glm::vec3(0.5f, 0.5f,  0.0f);
    this->camera->current_up = glm::vec3(0.0f, 1.0f,  0.0f);

    this->shader = new FGEGLSL();


    this->background_texture = new FGEDataTexture();
    this->background_texture->setName("checker-pattern.jpg");
    this->background_texture->setPath("/home/corolo/Qt/FireGameEngine/Images");
    this->initBackgroundTexture();
    this->createBackgroundBufferData(this->f, this->shader, "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/Background.vert", "/home/corolo/Qt/FireGameEngine/Shader/UVEditor/Background.frag");


    this->render_primitive->setDataProject(this->data_project);
    this->render_primitive->setShader(this->shader);
    this->render_primitive->updateBuffer(this->f);

    //qDebug()<< " ////ffffffffff////";

    this->view->matrix = glm::lookAt(this->camera->current_position+this->camera->current_eye, this->camera->current_position+this->camera->current_target, this->camera->current_up);

    this->shader->clearAttribLocation();
    this->shader->appendAttribLocation(0, "vertex");
    this->shader_program_selection = shader->initShader(this->f, "/home/corolo/Qt/FireGameEngine/Shader/Scene/VertexShaderSelection.vert", "/home/corolo/Qt/FireGameEngine/Shader/Scene/FragmentShaderSelection.frag");


    this->select_edit_mode = new FGEUVEEditModeSelection();
    this->select_edit_mode->init(this->f, this->data_project, this->shader);
    this->select_edit_mode->setRenderDevice(this->render_primitive->render_device);


    /*
    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "aPos");
    shader->appendAttribLocation(1, "aTexCoords");
    GLuint sprt = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.frag");
    this->render_tarjet_selection = new FGERenderTarget(f, sprt, 0, 0, 0.0);

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "aPos");
    shader->appendAttribLocation(1, "aTexCoords");
    GLuint __shader_program = shader->initShader(this->f, "/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.frag");
    ////GLuint __shader_program = shader->initShader("/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.vertex", "/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.fragment");

    this->render_tarjet = new FGERenderTarget(this->f, __shader_program, 0, 0, 0.0);

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "aPos");
    shader->appendAttribLocation(1, "aTexCoords");
    __shader_program = shader->initShader(this->f, "/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.frag");
    this->render_tarjet_outline = new FGERenderTarget(this->f, __shader_program, 0, 0, 0.9);
*/


    this->render_tarjet_selection = new FGERenderTarget(this->f, this->shader, 0, 0, 0.0, "/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.frag");
    this->render_tarjet = new FGERenderTarget(this->f, this->shader, 0, 0, 0.0, "/home/corolo/Qt/FireGameEngine/Shader/Screen/VertexShader.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/FragmentShader.frag");
    this->render_tarjet_outline = new FGERenderTarget(this->f, this->shader, 0, 0, 0.9,  "/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.vert", "/home/corolo/Qt/FireGameEngine/Shader/Screen/OutlinePostprocessing.frag");

    this->light_tool = new FGELight(this->f);
    this->gizmos = new FGEGizmos(this->f);
    this->gizmos->transforma_orientation->setMode(3);

    this->sculpt = new FGESculptMesh(this->f);


    /// INITIALIZE GRID
    this->grid = new FGESquareGrid();
    this->grid->init(f, this->shader, FGE_Z_NORMAL);


    this->area_menu = new FGEUVEOpenGLWidgetActions(this->data_project, this->trigger, this);

    QObject::connect(this->trigger, SIGNAL(__updateAllWIdgetsOpenGl()), this,  SLOT(updateAllWIdgetsOpenGl()));

    //raw_text = new FGEText(this->f);
    //draw_text->addText(0, "0", 10.0f, 10.0f, 0.3f, glm::vec3(0.8, 1.0f, 0.4f));
    //draw_text->addText(1, "0", 60.0f, 10.0f, 0.3f, glm::vec3(0.8, 1.0f, 0.4f));

    /*QObject::connect(this->trigger, SIGNAL(__updateBuffer()), this,  SLOT(newBufferAdded()));
    QObject::connect(this->trigger, SIGNAL(__updateScene()), this,  SLOT(slotUpdateGL()));
    QObject::connect(this->trigger, SIGNAL(__switch3DViewToEditMode(QString, int)), this,  SLOT(switch3DViewToEditMode(QString, int)));
    QObject::connect(this->trigger, SIGNAL(__switch3DViewToSculptMode(QString, void*)), this,  SLOT(switch3DViewToSculptMode(QString, void*)));*/

}

void FGEUVEOpenGLWidget::switch3DViewToSculptMode(QString name_3dview, void *item) {

    if(this->name_3dview==name_3dview){
        FGESculptItem *_item = (FGESculptItem*)item;
        this->data_project->current_sculpt_item = _item;
        this->edit_mode = 4;
        this->update();
    }
}
void FGEUVEOpenGLWidget::switch3DViewToEditMode(QString name_3dview, int type_mode) {
    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    if(this->name_3dview==name_3dview){
        this->edit_mode = type_mode;
        this->data_project->current_sculpt_item = NULL;
        ///FGEDataNode *item = sns->getCurrentNode();
        /*if(type_mode==1){
            this->render_primitive->buffer_gl->initSimple(this->f, item->simple);
        }else if(type_mode==3){
            this->render_primitive->buffer_gl->initLinesForSelection(this->f, item->simple);
        }else if(type_mode==3){
            this->render_primitive->buffer_gl->initFacesForSelection(this->f, item->simple);
        }*/
        this->update();
    }
}

GLint FGEUVEOpenGLWidget::getMaxSamples() {

    GLint maxSamples = 0;
    QOffscreenSurface sfc;
    sfc.create();
    QOpenGLContext ctx;
    if(ctx.create()) {
        ctx.makeCurrent(&sfc);
        glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
        ctx.doneCurrent();
    }
    return maxSamples;
}

void FGEUVEOpenGLWidget::updateInit(){
    makeCurrent();
    this->render_primitive->updateBuffer(this->f);
    update();
    doneCurrent();
}
void FGEUVEOpenGLWidget::updateAllWIdgetsOpenGl(){
    update();
}

void FGEUVEOpenGLWidget::initProjection()
{
    if(!this->projection->is_set){
        float fovPerPixel = 0.1 * 3.14159265358979323846 / 180;
        float fovy = (float)HEIGHT * fovPerPixel;
        this->projection->perspective.fovy = fovy;

        this->projection->scaleFactor = 3.0f;
        this->projection->is_perspective = true;

        this->projection->perspective.is_set = true;
        this->projection->perspective.far = 300.0;
        this->projection->perspective.near = 0.01;
        this->projection->perspective.radians = 45.0;
        this->projection->perspective.aspect =  (float)WIDTH / (float)HEIGHT;
        this->projection->perspective.matrix = glm::perspective(
                    this->projection->perspective.fovy,
                    this->projection->perspective.aspect,
                    this->projection->perspective.near,
                    this->projection->perspective.far
        );
        this->projection->matrix = this->projection->perspective.matrix;

        this->projection->ortho.is_set = true;
        this->projection->ortho.znear = -1.0;
        this->projection->ortho.zfar = 300.0;
        if (WIDTH <= HEIGHT){
            this->projection->ortho.bottom      = -1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->projection->ortho.top         = 1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->projection->ortho.left        = -1.0;
            this->projection->ortho.right       = 1.0;
        }else{
            this->projection->ortho.bottom      = -1.0;
            this->projection->ortho.top         = 1.0;
            this->projection->ortho.left        =  -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
            this->projection->ortho.right       =  1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
        }

        this->projection->ortho.matrix = glm::ortho(
                    this->projection->ortho.left,
                    this->projection->ortho.right,
                    this->projection->ortho.bottom,
                    this->projection->ortho.top,
                    this->projection->ortho.znear,
                    this->projection->ortho.zfar
        );
        this->projection->is_set = true;
    }
}

void FGEUVEOpenGLWidget::paintGL()
{

        makeCurrent();

        this->f = openGLFunctions();
        QPainter painter(this);

        painter.beginNativePainting();
        //painter.setRenderHint(QPainter::Antialiasing);

        initProjection();

        //FGEDataNode *etn = cursc->node;
        FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();



        {
            //////////////////////////////////////////
            //// SIMPLE RENDER TARGET ////////////////
            ///
            this->render_tarjet->bind(this->f);
            this->f->glDisable(GL_DEPTH_TEST);
            this->f->glDepthFunc(GL_LESS);
            this->f->glEnable(GL_BLEND);
            this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            this->f->glClearColor(255, 255, 255, 255);
            this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //this->f->glDepthRange(0.01, 100.0);
            //this->grid->draw(f, this->shader, this->view, this->projection, glm::vec3(0.6, 0.6, 0.6));
            this->drawBackground(f, this->shader);

            this->render_primitive->renderUV(
                        this->f,
                        camera->current_eye,
                        this->view,
                        this->projection,
                        0,
                        0,
                        this->edit_mode
                        );


            this->render_tarjet->release(this->f, context());


        }
        this->f->glEnable(GL_DEPTH_TEST);
        this->f->glDepthFunc(GL_ALWAYS);
        this->f->glEnable(GL_BLEND);
        this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*
        if(this->edit_mode==0){
            //////////////////////////////////////////
            //// OUTLINE RENDER TARGET ////////////////
            ///
            this->render_tarjet_outline->bind(this->f);
            this->f->glEnable(GL_DEPTH_TEST);
            this->f->glDepthFunc(GL_ALWAYS);
            this->f->glEnable(GL_BLEND);
            this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            this->f->glClearColor(0.0, 0.0, 0.0, 1.0);
            this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            this->render_primitive->renderSelectedObjects(
                        this->f,
                        this->data_project->selected_nodes,
                        (void*)this,
                        camera->current_eye,
                        this->WIDTH,
                        this->HEIGHT,
                        this->view,
                        this->projection,
                        0,
                        5);


            this->render_tarjet_outline->release(this->f, context());

        }*/


        this->render_tarjet->render(this->f, this->shader);
        /*if(this->edit_mode==0){
            this->render_tarjet_outline->renderSelected(this->f, this->shader, this->WIDTH, this->HEIGHT);
        }*/


/*
        if(this->select->isDrug()){

            this->select->drawArea(this->f);

        }else if(this->select_edit_mode->isDrug()){

            this->select_edit_mode->drawArea(this->f);
        }else{

            if(this->edit_mode==0){
                if(!this->data_project->selected_nodes->isEmpty()){
           *//*         gizmos->setProjection(this->projection->matrix);
                    gizmos->setView(this->view->matrix);
                    gizmos->setScaleFactor(this->projection->scaleFactor);
                    gizmos->perspectiveIs(this->projection->is_perspective);

                    painter.endNativePainting();

                    FGETransformation *transformation = this->data_project->selected_nodes->getCurrentNode()->transform;


                    gizmos->drawGizmo(this->f, transformation, painter);
                    painter.beginNativePainting();
                }
            }else */
        if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
                if(!sns->isEmpty()){
                    glm::vec3 pos = sns->getCenterSelectedUVPoint();

                    gizmos->setProjection(this->projection->matrix);
                    gizmos->setView(this->view->matrix);
                    gizmos->setScaleFactor(this->projection->scaleFactor);
                    gizmos->perspectiveIs(false);

                    FGETransformation *transformation = new FGETransformation(NULL, NULL);
                    //transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                    transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                    painter.endNativePainting();
                    qDebug()<<"tttt drawGizmo : ("<<pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")";

                    gizmos->drawGizmo(this->f, transformation, painter);
                    delete transformation;
                    painter.beginNativePainting();

                }
        }
            /*}else if(this->edit_mode==2){
                if(!data_project->selected_nodes->isEmpty()){
                    glm::vec3 pos;
                    FGEDataNode *item_node;
                    if(data_project->selected_nodes->getSelectionCenterForce(pos)){
                        gizmos->setProjection(this->projection->matrix);
                        gizmos->setView(this->view->matrix);
                        gizmos->setScaleFactor(this->projection->scaleFactor);
                        gizmos->perspectiveIs(this->projection->is_perspective);

                        FGETransformation *transformation = new FGETransformation(NULL, NULL);
                        transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                        transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                        painter.endNativePainting();
                        gizmos->drawGizmo(this->f, transformation, painter);
                        delete transformation;
                        painter.beginNativePainting();
                    }

                }

            }else if(this->edit_mode==3){
                if(!data_project->selected_nodes->isEmpty()){
                    glm::vec3 pos;
                    FGEDataNode *item_node;
                    if(data_project->selected_nodes->getSelectionCenterForce(pos)){
                        gizmos->setProjection(this->projection->matrix);
                        gizmos->setView(this->view->matrix);
                        gizmos->setScaleFactor(this->projection->scaleFactor);
                        gizmos->perspectiveIs(this->projection->is_perspective);

                        FGETransformation *transformation = new FGETransformation(NULL, NULL);
                        transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                        transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                        painter.endNativePainting();
                        gizmos->drawGizmo(this->f, transformation, painter);
                        delete transformation;
                        painter.beginNativePainting();
                    }

                }

            }


        }*/



//drawLegend(QPoint(WIDTH/2-50,HEIGHT/2-30), &painter);
        //QPainter painter(this);

        painter.endNativePainting();

        f->glDepthFunc(GL_ALWAYS);

        painter.end();
        f->glDepthFunc(GL_LESS);

        doneCurrent();
}

void FGEUVEOpenGLWidget::drawLegend(QPoint p, QPainter *painter)
{
    ///const int Margin = 11;
    const int Padding = 6;

    QTextDocument textDocument;
    textDocument.setDefaultStyleSheet("* { color: #FFEFEF }");
    textDocument.setHtml("<h4 align=\"center\">Vowel Categories</h4>"
                         "<p align=\"center\"><table width=\"100%\">"
                         "<tr><td>Open:<td>a<td>e<td>o<td>&ouml"
                         "</table>");
    textDocument.setTextWidth(textDocument.size().width());

    QRect rect(QPoint(0, 0), textDocument.size().toSize()
                             + QSize(2 * Padding, 2 * Padding));
    //painter->translate(width() - rect.width() - Margin,
    //                   height() - rect.height() - Margin);
    painter->translate(p);
    painter->setPen(QColor(255, 239, 255));
    painter->setBrush(QColor(255, 0, 0, 255));
    painter->drawRect(rect);

    painter->translate(Padding, Padding);
    textDocument.drawContents(painter);
}

void FGEUVEOpenGLWidget::resizeGL(int w, int h)
{
    this->f = openGLFunctions();
    this->f->glViewport(0, 0, w, h);

    WIDTH = w;
    HEIGHT = h;

    gizmos->gizmos_rotation->init(w, h);
    gizmos->setViewportWH(w, h);

    data_project->view_port_width = w;
    data_project->view_port_height = h;


    this->render_tarjet->update(this->f, WIDTH, HEIGHT);
    this->render_tarjet_selection->update(this->f, WIDTH, HEIGHT);
    this->render_tarjet_outline->update(this->f, WIDTH, HEIGHT);

    this->projection->is_perspective = false;

    if (WIDTH <= HEIGHT){
        this->projection->ortho.bottom      = -1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
        this->projection->ortho.top         = 1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
        this->projection->ortho.left        = -1.0;
        this->projection->ortho.right       = 1.0;
    }else{
        this->projection->ortho.bottom      = -1.0;
        this->projection->ortho.top         = 1.0;
        this->projection->ortho.left        =  -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
        this->projection->ortho.right       =  1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
    }
    this->projection->matrix = glm::ortho(
                this->projection->ortho.left,
                this->projection->ortho.right,
                this->projection->ortho.bottom,
                this->projection->ortho.top,
                this->projection->ortho.znear,
                this->projection->ortho.zfar
    );


}


void FGEUVEOpenGLWidget::initializeScene(FGEDataProject *data_project)
{
    this->data_project = data_project;
    initialized=1;
    update();
}

void FGEUVEOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();
    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();


    //this->setFocus();
    if (event->button() == Qt::MiddleButton)
    {
        camera->setKeyShift(true);
        camera->drag2DMousePress(event, WIDTH, HEIGHT, this->view->matrix, this->projection->matrix, this->projection->scaleFactor);
        update();
    }else if (event->button() == Qt::RightButton){

        area_menu->show(mapToGlobal(event->pos()), edit_mode);

    }else{

        glm::vec2 curs_pos = glm::vec2(event->position().x(), HEIGHT - event->position().y());

        if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
            if(!sns->isEmpty()){
                glm::vec3 pos = sns->getCenterSelectedUVPoint();

                //if(data_project->selected_nodes->getSelectionCenterForce(pos)){
                    gizmos->setProjection(this->projection->matrix);
                    gizmos->setView(this->view->matrix);
                    gizmos->setScaleFactor(this->projection->scaleFactor);
                    gizmos->perspectiveIs(this->projection->is_perspective);

                    this->temp_transformation->init(NULL, NULL);
                    this->temp_transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                    this->rr_old_trans = this->temp_transformation->getLocalTransformation();

                    if(gizmos->pressMouse(this->f, curs_pos, this->temp_transformation, context(), this->render_tarjet_selection)){
                        doneCurrent();
                        this->trigger->updateDock(dock_parent);
                        return;
                    }
                //}


            }
        }


        {
            /*FGESceneOS *cursc = struct_project->scene_current;
            ////qDebug() << "t1";
            initObjects(cursc->node);
            ////

            initProjection(cursc);*/

            //this->f->glBindFramebuffer(GL_FRAMEBUFFER, addFBO(FBOIndex::TEST));
            if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
                if(this->select_edit_mode->pressSelect((void*)this,
                                                       this->f,
                                                       this->edit_mode,
                                                       this->camera->current_eye,
                                                       curs_pos,
                                                       this->view,
                                                       this->projection,
                                                       this->shader_program_selection,
                                                       context(),
                                                       this->render_tarjet_selection,
                                                       this->WIDTH,
                                                       this->HEIGHT)){
                    /*this->trigger->updateDock(dock_parent);//trigger((void *)this);
                    emit this->trigger->updatePropertiesObject(1);*/
                    //doneCurrent();

                    doneCurrent();
                    this->trigger->updateDock(dock_parent);
                    return;
                }else{
                    update();
                }

            }

        }

    }
    doneCurrent();
}

void FGEUVEOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();
    //this->setFocus();
    glm::vec2 curs_pos = glm::vec2(event->position().x(), HEIGHT - event->position().y());
    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    //this->setFocus();

    //cursor_x_t->text = QString::number(event->x()).toStdString();
    //cursor_y_t->text = QString::number(event->y()).toStdString();

    if (event->buttons() == Qt::MiddleButton) {
        camera->drag2DMouseMove(event, WIDTH, HEIGHT, this->view->matrix, this->projection->matrix, this->projection->scaleFactor);
        update();
    }else{

        if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
            if(!sns->isEmpty()){
                gizmos->setProjection(this->projection->matrix);
                gizmos->setView(this->view->matrix);
                gizmos->setScaleFactor(this->projection->scaleFactor);
                gizmos->perspectiveIs(this->projection->is_perspective);

                glm::mat4 o_lt = this->temp_transformation->getLocalTransformation();

                if(gizmos->moveMouse(this->f, curs_pos, this->temp_transformation)){

                    glm::mat4 lt = this->temp_transformation->getLocalTransformation();
                    glm::mat4 _lm = lt/o_lt;

                    sns->updateUVMesh(this->f, _lm);

                    emit this->trigger->updatePropertiesObject(0);
                    emit this->trigger->updateAllWIdgetsOpenGl();
                    doneCurrent();
                    return;
                }
            }
        }

        if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
            this->select_edit_mode->moveSelect(this->f, curs_pos, WIDTH, HEIGHT);
            update();
        }

    }


    doneCurrent();
}

void FGEUVEOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();
    FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();

    this->setFocus();

    ///glm::vec2 curs_pos = glm::vec2(event->position().x(), HEIGHT - event->position().y());

    if(this->edit_mode==0){
            if(gizmos->releazeMouse()){
                if(!sns->isEmpty()){
                    this->trigger->updateDock(dock_parent);
                    update();
                    doneCurrent();
                    return;
                }
            }

    }else if(this->edit_mode==1 || this->edit_mode==2 || this->edit_mode==3){
        /*if(this->select_edit_mode->releazeSelect((void*)this, this->f, this->edit_mode, curs_pos, light_tool, this->view, this->projection, this->shader_program_selection, context(), this->render_tarjet_selection, this->WIDTH, this->HEIGHT)){
            this->trigger->trigger((void *)this);
            update();
        }else{*/
            if(gizmos->releazeMouse()){
                if(!sns->isEmpty()){
                    this->trigger->updateDock(dock_parent);
                    update();
                    doneCurrent();
                    return;
                }
            }
        //}
    }

    doneCurrent();

}

void FGEUVEOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();

    if(event->key() == Qt::Key_Shift){
        this->data_project->keyboard_state->key_shift = true;
        camera->setKeyShift(true);
        update();
    }else if(event->key() == Qt::Key_E){
    }else if(event->key() == Qt::Key_F){
    }else if(event->key() == Qt::Key_D){
    }
    doneCurrent();

    /**else if(event->key() == Qt::Key_Up){
        //qDebug() << "--Key_Up";
        ___lightPos[2] -= 0.5;
        update();
    }else if(event->key() == Qt::Key_Down){
        ___lightPos[2] += 0.5;
        update();
    }else if(event->key() == Qt::Key_Left){
        ___lightPos[0] -= 0.5;
        update();
    }else if(event->key() == Qt::Key_Right){
        ___lightPos[0] += 0.5;
        update();
    }else if(event->key() == Qt::Key_X){
        ___lightPos[1] += 0.5;
        update();
    }else if(event->key() == Qt::Key_C){
        ___lightPos[1] -= 0.5;
        update();
    }*/

}

void FGEUVEOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();

    if(event->key() == Qt::Key_Shift){
        this->data_project->keyboard_state->key_shift = false;
        camera->setKeyShift(false);
        update();
    }
    doneCurrent();
}


void FGEUVEOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    camera->zoom(event);
    update();
    event->accept();
}


void FGEUVEOpenGLWidget::initGBackgroundTexture()
{
    makeCurrent();
    this->f = openGLFunctions();
    initBackgroundTexture();
    doneCurrent();
}

void FGEUVEOpenGLWidget::initBackgroundTexture()
{

    // load and create a texture
    // -------------------------
    f->glEnable(GL_TEXTURE_2D);
    f->glActiveTexture(GL_TEXTURE0);
    uint tex_id;
    if(this->background_texture->texture()!=0){
        tex_id = this->background_texture->texture();
        f->glDeleteTextures(1, &tex_id);
    }
    f->glGenTextures(1, &tex_id);
    this->background_texture->setTexture(tex_id);

    //if(ft==0) f->glActiveTexture(GL_TEXTURE0);
    //if(ft==1) f->glActiveTexture(GL_TEXTURE1);

    f->glBindTexture(GL_TEXTURE_2D, this->background_texture->texture()); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    //int width, height, nrChannels;

    this->background_texture->name().replace("%20", " ");
    QImage im(this->background_texture->path()+"/"+this->background_texture->name());
    im= im.convertToFormat(QImage::Format_RGBA8888).mirrored();
    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, im.width(), im.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im.bits());

    f->glGenerateMipmap(GL_TEXTURE_2D);

}


void FGEUVEOpenGLWidget::createBackgroundBufferData(OpenGLFunctions *q, FGEGLSL *shader, const char *vertexPath, const char *fragmentPath)
{

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "VERTEX");
    shader->appendAttribLocation(1, "TEXCOORD");
    this->background_shader_program = shader->initShader(q, vertexPath, fragmentPath);

    float quadVertices[] = {
            // positions   // texCoords
            0.0f, 1.0f,  0.0f, 1.0f,
            0.0f, 0.0f,  0.0f, 0.0f,
            1.0f, 0.0f,  1.0f, 0.0f,

            0.0f, 1.0f,  0.0f, 1.0f,
            1.0f, 0.0f,  1.0f, 0.0f,
            1.0f, 1.0f,  1.0f, 1.0f
        };

    q->glGenVertexArrays(1, &this->background_VAO);
    q->glGenBuffers(1, &this->background_VBO);
    q->glBindVertexArray(this->background_VAO);
    q->glBindBuffer(GL_ARRAY_BUFFER, this->background_VBO);
    q->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    q->glEnableVertexAttribArray(0);
    q->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    q->glEnableVertexAttribArray(1);
    q->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
void FGEUVEOpenGLWidget::drawBackground(OpenGLFunctions *_q, FGEGLSL *shader){
    glm::mat4 scaleview;
    if(!this->projection->is_perspective){
        scaleview = glm::scale(glm::mat4(1.0f), glm::vec3(this->projection->scaleFactor))*this->view->matrix;
    }else{
        scaleview = this->view->matrix;
    }
    glm::mat4 ModelViewProjectionMatrix = this->projection->matrix*scaleview;

    _q->glDisable(GL_DEPTH_TEST);
    _q->glUseProgram(this->background_shader_program);
        shader->setMat4(_q, this->background_shader_program, "ModelViewProjectionMatrix", ModelViewProjectionMatrix);
        shader->setInt(_q, this->background_shader_program, "screenTexture", 0);
        _q->glActiveTexture(GL_TEXTURE0);
        _q->glBindTexture(GL_TEXTURE_2D, this->background_texture->texture());	// use the color attachment texture as the texture of the quad plane
        _q->glBindVertexArray(this->background_VAO);
        _q->glDrawArrays(GL_TRIANGLES, 0, 6);
        _q->glBindVertexArray(0);
    _q->glUseProgram(0);
    _q->glEnable(GL_DEPTH_TEST);

}
