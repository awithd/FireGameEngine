#include "FGEOpenGLWidget.h"

FGEOpenGLWidget::FGEOpenGLWidget(FGETriggerFunction *trigger, FGECreateNewObject *create_new_object, FGEDataProject *data_project, QString name, void *dock, QWidget *parent) : QOpenGLWidget(parent)
{


    qDebug() << "eeeeee";
    this->opperations_state = new FGEStateOpperations();

    this->dock_parent = dock;
    this->initialized=0;
    this->scene = NULL;
    this->parent = parent;
    this->name_3dview = name;
    this->create_new_object = create_new_object;

    this->trigger = trigger;
    this->data_project = data_project;

    this->opperations_state->viewport_shading = FGE_VIEWPORT_SHADING_MATERIAL;
    this->opperations_state->object_model = FGE_OBJECT_MESH;
    this->opperations_state->interaction_mode = FGE_INTERACTION_MODE_OBJECT;
    this->opperations_state->mesh_select = FGE_MESH_SELECT_FACE;


    this->render_device = new FGEOpenGLSceneRenderer();
    this->buffer_gl = new FGEPrepareGLBuffer();

    this->temp_transformation = new FGETransformation(NULL, NULL);

    this->driver_behavior = 0;

    QOffscreenSurface surf;
    surf.create();

    QOpenGLContext ctx;
    ctx.create();
    ctx.makeCurrent(&surf);

    ////qDebug () <<"OpenGL version : "<< (const char*)ctx.functions()->glGetString(GL_VERSION);

    QSurfaceFormat fmt;
    fmt.setSamples(8);
    setFormat(fmt);



     FGEDataAnimation * animation = data_project->first_animation;
     while(animation!=NULL){
         animation->prepare(0.0416666);
         animation=animation->next;
     }



     //projection = new FGEDataCameraProjection();
     //view = new FGEDataCameraView();


    //this->data_project->textur++;
    //this->struct_project_textur = this->data_project->textur;

}

FGEOpenGLWidget::~FGEOpenGLWidget()
{
    //trans_comp->~FGETranslationComponent();

}

void FGEOpenGLWidget::newBufferAdded(){
    makeCurrent();
qDebug() << "newBufferAdded";
    if(this->data_project!=NULL && this->f!=NULL){
        qDebug() << "init_buffer_nodes : "<<this->data_project->init_buffer_nodes.size();
        for(int i=0; i<this->data_project->init_buffer_nodes.size(); i++){
            this->buffer_gl->initBufferNode(this->f, this->data_project->init_buffer_nodes.at(i));
        }
        qDebug() << "2";
        this->data_project->init_buffer_nodes.clear();
        this->buffer_gl->initTextureBuffer(this->f, this->data_project);
    }

    update();
    doneCurrent();
}
void FGEOpenGLWidget::slotUpdateGL(){
    ////////qDebug() << "uuuuuuuuuuuu  slotUpdateGL";
    update();
}

void FGEOpenGLWidget::triggerUpdateGL(){

    this->current_data_camera->updateProjection();
    update();
}


void FGEOpenGLWidget::setDisplayMode(int value)
{
    this->opperations_state->viewport_shading = value;
    update();
}

OpenGLFunctions * FGEOpenGLWidget::openGLFunctions() const
{
    return QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_0>();
}

void FGEOpenGLWidget::initializeGL()
{ ////////qDebug() << "ffff";

    initializeOpenGLFunctions();
    this->f = openGLFunctions();

    //getMaxSamples();

    // initialize buffer of used mesh (bone, gizmo, other static object)
    //


    this->skin_conf = new FGEDataSkinConfiguration();



    this->f->glEnable(GL_MULTISAMPLE);

    this->editor_data_camera = new FGEDataCamera();
    this->current_data_camera = this->editor_data_camera;
    this->camera = new FGECamera(this->current_data_camera);


    //this->camera->init(&this->view, &this->projection);
    //this->camera->key_shift = false;


    this->shader = this->data_project->shader;

    ///this->render_primitive->init(this->f, this->data_project, this->shader);
    this->render_device->init(f, this->data_project, this->shader);
    this->buffer_gl->initGlobalBufferBone(f, data_project->global_buffer_bone, this->shader);

    //this->render_primitive->setDataProject(this->data_project);
    //this->render_primitive->setShader(this->shader);
    //this->render_primitive->updateBuffer(this->f);
    //qDebug()<< " ////ffffffffff////";

    //this->view->matrix = glm::lookAt(this->camera->current_position+this->camera->current_eye, this->camera->current_position+this->camera->current_target, this->camera->current_up);

    this->shader->clearAttribLocation();
    this->shader->appendAttribLocation(0, "vertex");
    this->shader_program_selection = shader->initShader(this->f, "/home/corolo/Qt/FireGameEngine/Shader/Scene/VertexShaderSelection.vert", "/home/corolo/Qt/FireGameEngine/Shader/Scene/FragmentShaderSelection.frag");


    this->selection_mesh_editable = new FGEEditMeshSelector();
    this->selection_mesh_editable->init(this->f, this->data_project, this->shader);
    this->selection_mesh_editable->setRenderDevice(this->render_device);


    this->selection_armature = new FGESelectionArmature();
    this->selection_armature->init(this->f, this->data_project, this->shader);
    this->selection_armature->setRenderDevice(this->render_device);

    this->selection_armature_editable = new FGESelectionArmatureEditable();
    this->selection_armature_editable->init(this->f, this->data_project, this->shader);
    this->selection_armature_editable->setRenderDevice(this->render_device);

    this->selection_armature_paint_weight = new FGESelectionArmaturePaintWeight();
    this->selection_armature_paint_weight->init(this->f, this->data_project, this->shader);
    this->selection_armature_paint_weight->setRenderDevice(this->render_device);

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
    this->gizmos->setDataCamera(this->current_data_camera);
    this->sculpt = new FGESculptMesh(this->f);
    this->painting_skin_weights = new FGEPaintingSkinWeights(this->f);

    item_create_new_object = new FGEItemCreateNewObject();
    item_create_new_object->init(this->f, this->create_new_object->first_pos, this->create_new_object->second_pos);
    this->create_new_object->init(this->f);

    view_opp = new FGEViewOpperation(this->f/*draw_text*/, FGE_TYPE_VIEW_3DDIM);

    /// INITIALIZE GRID
    this->grid = new FGEGrid();
    this->grid->init(f, this->shader, FGE_Y_NORMAL);


    this->area_menu = new FGEOpenGLWidgetActions(this->data_project, this->trigger, this);


    //raw_text = new FGEText(this->f);
    //draw_text->addText(0, "0", 10.0f, 10.0f, 0.3f, glm::vec3(0.8, 1.0f, 0.4f));
    //draw_text->addText(1, "0", 60.0f, 10.0f, 0.3f, glm::vec3(0.8, 1.0f, 0.4f));

    QObject::connect(this->trigger, SIGNAL(__updateBuffer()), this,  SLOT(newBufferAdded()));
    QObject::connect(this->trigger, SIGNAL(__updateScene()), this,  SLOT(slotUpdateGL()));
    QObject::connect(this->trigger, SIGNAL(__updateAllWIdgetsOpenGl()), this,  SLOT(updateAllWIdgetsOpenGl()));
    QObject::connect(this->trigger, SIGNAL(__switch3DViewToEditMode(QString, int)), this,  SLOT(switch3DViewToEditMode(QString, int)));
    QObject::connect(this->trigger, SIGNAL(__switch3DViewToSculptMode(QString, void*)), this,  SLOT(switch3DViewToSculptMode(QString, void*)));
    QObject::connect(this->trigger, SIGNAL(__switch3DViewToArmatureEditMode(QString, int)), this,  SLOT(switch3DViewToArmatureEditMode(QString, int)));
    QObject::connect(this->trigger, SIGNAL(__updateInteractionModePrimitive(QString,int)), this,  SLOT(updateInteractionModePrimitive(QString, int)));
    QObject::connect(this->trigger, SIGNAL(__updateMeshSelect(QString,int)), this,  SLOT(updateMeshSelect(QString, int)));


    this->armature_edit = new FGEArmatureEdit(this->data_project);
    this->armature_pose = new FGEArmaturePose(this->data_project);

    //this->render_primitive->prepareRenderDevice(this->f, this->shader);

    this->object_module = new FGEObjectSelectorController(this->data_project, this->gizmos);
    this->object_module->selection_mesh->init(this->f, this->data_project, this->shader);
    this->object_module->selection_mesh->setRenderDevice(this->render_device);

    //qDebug()<< " ////للللل////";
}

void FGEOpenGLWidget::switch3DViewToSculptMode(QString name_3dview, void *item) {

    if(this->name_3dview==name_3dview){
        FGESculptItem *_item = (FGESculptItem*)item;
        this->data_project->current_sculpt_item = _item;
        this->edit_mode = 4;
        this->update();
    }
}

void FGEOpenGLWidget::switch3DViewToEditMode(QString name_3dview, int type_mode) {

    if(this->name_3dview==name_3dview){
        this->opperations_state->interaction_mode = type_mode;
        this->data_project->current_sculpt_item = NULL;
        ///FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();
        ///FGEDataNode *item = sns->getCurrentNode();
        ////////qDebug()<< "name item : "<<item->name;
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

void FGEOpenGLWidget::switch3DViewToArmatureEditMode(QString name_3dview, int type_mode) {

    if(this->name_3dview==name_3dview){
        if(type_mode==FGE_INTERACTION_MODE_OBJECT){
            if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){
                this->opperations_state->object_model=FGE_OBJECT_MESH;
            }
        }else{
            this->opperations_state->object_model = FGE_OBJECT_ARMATURE;
        }

        this->opperations_state->interaction_mode = type_mode;
        this->data_project->current_sculpt_item = NULL;

        qDebug()<< "type_mode : "<<type_mode;
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

void FGEOpenGLWidget::updateMeshSelect(QString name_3dview, int mesh_select) {
    if(this->name_3dview==name_3dview){
        this->opperations_state->mesh_select = mesh_select;
        this->update();
    }
}

void FGEOpenGLWidget::updateInteractionModePrimitive(QString name_3dview, int interaction_mode) {
    if(this->name_3dview==name_3dview){
        this->opperations_state->interaction_mode = interaction_mode;
        this->update();
    }
}

void FGEOpenGLWidget::updateAllWIdgetsOpenGl(){
    update();
}

GLint FGEOpenGLWidget::getMaxSamples() {

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

void FGEOpenGLWidget::setCurrentCamera(FGEDataCamera *_current_data_camera)
{
    if(_current_data_camera!=NULL) {
        this->current_data_camera = _current_data_camera;
        this->camera->setCamera(this->current_data_camera);
        this->current_data_camera->updateProjection();
    }
    update();
}

void FGEOpenGLWidget::updateInit(){
    makeCurrent();
    //qDebug() <<"7777777";
    //this->render_primitive->updateBuffer(this->f);

    ////////qDebug() <<"rrrrrrrrrrr t0 : ";
    update();
    ////////qDebug() <<"rrrrrrrrrrr t1 : ";
    doneCurrent();
    ////////qDebug() <<"rrrrrrrrrrr t2 : ";
}

/*void FGEOpenGLWidget::swappeProjection(int mode){
    ////////qDebug() << "swappeProjection : "<<mode;
    if(mode==0){
        this->current_data_camera->projection->is_perspective = true;
    }else if(mode==1){
        this->current_data_camera->projection->is_perspective = false;
    }

    if(this->current_data_camera->projection->is_perspective) {
        this->current_data_camera->projection->perspective.aspect =  (float)WIDTH / (float)HEIGHT;
        float fovPerPixel = 0.1 * 3.14159265358979323846 / 180;
        float fov = (float)HEIGHT * fovPerPixel;

        this->current_data_camera->projection->matrix = glm::perspective(
                    fov,
                    this->current_data_camera->projection->perspective.aspect,
                    this->current_data_camera->projection->perspective.near,
                    this->current_data_camera->projection->perspective.far
        );
    }else{
        if (WIDTH <= HEIGHT){
            this->current_data_camera->projection->ortho.bottom      = -1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.top         = 1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.left        = -1.0;
            this->current_data_camera->projection->ortho.right       = 1.0;
        }else{
            this->current_data_camera->projection->ortho.bottom      = -1.0;
            this->current_data_camera->projection->ortho.top         = 1.0;
            this->current_data_camera->projection->ortho.left        =  -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
            this->current_data_camera->projection->ortho.right       =  1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
        }
        this->current_data_camera->projection->matrix = glm::ortho(
                    this->current_data_camera->projection->ortho.left,
                    this->current_data_camera->projection->ortho.right,
                    this->current_data_camera->projection->ortho.bottom,
                    this->current_data_camera->projection->ortho.top,
                    this->current_data_camera->projection->ortho.znear,
                    this->current_data_camera->projection->ortho.zfar
        );
    }


    update();
}*/

/*void FGEOpenGLWidget::initProjection()
{
    if(!this->current_data_camera->projection->is_set){
        float fovPerPixel = 0.1 * 3.14159265358979323846 / 180;
        float fovy = (float)HEIGHT * fovPerPixel;
        this->current_data_camera->projection->perspective.fovy = fovy;

        this->current_data_camera->projection->scaleFactor = 3.0f;
        this->current_data_camera->projection->is_perspective = true;

        this->current_data_camera->projection->perspective.is_set = true;
        this->current_data_camera->projection->perspective.far = 300.0;
        this->current_data_camera->projection->perspective.near = 0.01;
        this->current_data_camera->projection->perspective.radians = 45.0;
        this->current_data_camera->projection->perspective.aspect =  (float)WIDTH / (float)HEIGHT;
        this->current_data_camera->projection->perspective.matrix = glm::perspective(
                    this->current_data_camera->projection->perspective.fovy,
                    this->current_data_camera->projection->perspective.aspect,
                    this->current_data_camera->projection->perspective.near,
                    this->current_data_camera->projection->perspective.far
        );
        this->current_data_camera->projection->matrix = this->current_data_camera->projection->perspective.matrix;

        this->current_data_camera->projection->ortho.is_set = true;
        this->current_data_camera->projection->ortho.znear = -1.0;
        this->current_data_camera->projection->ortho.zfar = 300.0;
        if (WIDTH <= HEIGHT){
            this->current_data_camera->projection->ortho.bottom      = -1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.top         = 1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.left        = -1.0;
            this->current_data_camera->projection->ortho.right       = 1.0;
        }else{
            this->current_data_camera->projection->ortho.bottom      = -1.0;
            this->current_data_camera->projection->ortho.top         = 1.0;
            this->current_data_camera->projection->ortho.left        =  -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
            this->current_data_camera->projection->ortho.right       =  1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
        }

        this->current_data_camera->projection->ortho.matrix = glm::ortho(
                    this->current_data_camera->projection->ortho.left,
                    this->current_data_camera->projection->ortho.right,
                    this->current_data_camera->projection->ortho.bottom,
                    this->current_data_camera->projection->ortho.top,
                    this->current_data_camera->projection->ortho.znear,
                    this->current_data_camera->projection->ortho.zfar
        );
        this->current_data_camera->projection->is_set = true;
    }
}*/


void FGEOpenGLWidget::paintGL()
{

        makeCurrent();
        this->f = openGLFunctions();
        QPainter painter(this);

        this->camera->updateCameraAndView();
        this->gizmos->setDataCamera(this->current_data_camera);

        //this->render_primitive->updateBuffer(this->f);

        //initProjection();

        FGEDataScene *current_scene = data_project->current_scene;

        //FGEDataNode *etn = cursc->node;

        painter.beginNativePainting();

        {
            //////////////////////////////////////////
            //// SIMPLE RENDER TARGET ////////////////
            ///
            this->render_tarjet->bind(this->f);
            this->f->glEnable(GL_DEPTH_TEST);
            this->f->glDepthFunc(GL_LESS);
            this->f->glClearColor(current_scene->color[0], current_scene->color[1], current_scene->color[2], current_scene->color[3]);
            this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //this->f->glDepthMask(false);

            //qDebug()<< " ////ن////";
            this->f->glEnable(GL_BLEND);
            this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            /*this->f->glEnable(GL_CULL_FACE);
            this->f->glFrontFace(GL_CW);*/

            //this->f->glDepthRange(0.01, 100.0);
            glm::mat4 mm = camera->getMVPMatrix();
            this->grid->draw(f, this->shader, mm, this->current_data_camera->view, this->current_data_camera->projection, glm::vec3(0.6, 0.6, 0.6), glm::vec2(WIDTH, HEIGHT), 1, 0.0, 1000.0);
            //this->f->glDepthRange(1.0, 0.0);

            /*this->f->glEnable(GL_DEPTH_TEST);
            this->f->glDepthFunc(GL_LESS);
            this->f->glEnable(GL_BLEND);
            this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            //this->f->glClearColor(cursc->color[0], cursc->color[1], cursc->color[2], cursc->color[3]);

            this->f->glClearColor(0.443, 0.443, 0.443, 1.0);
            this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
            //this->grid->draw(f, this->shader, this->view, this->projection, glm::vec3(0.4, 0.4, 0.4), glm::vec2(WIDTH, HEIGHT), 0.1, 1);

            //this->grid->draw(f, this->shader, this->view, this->projection, glm::vec3(0.6, 0.6, 0.6), glm::vec2(WIDTH, HEIGHT), 0.1, 2, 0.0, 15.0);
            //this->grid->draw(f, this->shader, this->view, this->projection, glm::vec3(0.6, 0.6, 0.6), glm::vec2(WIDTH, HEIGHT), 10, 2, 50.0, 1000.0);
            //qDebug() <<"render_primitive;";
            this->opperations_state->selection_drag = this->object_module->selection_mesh->isDrug();

            if(this->render_device!=NULL){
                this->render_device->veiw_pos = camera->getCurrentEye();
                this->render_device->projection_view_matrix = this->current_data_camera->projection->matrix*this->current_data_camera->view->matrix;

                //qDebug()<< " ////ه////";
                this->render_device->draw(this->f, this->opperations_state);
                //qDebug()<< " ////ا////";
            }



            //this->f->glDepthMask(true);

            //qDebug() <<"paint 2 : ";


            this->render_tarjet->release(this->f, context());


        }
////////qDebug() <<"end render_primitive;";
        this->render_tarjet->render(this->f, this->shader);

        painter.endNativePainting();

        /*this->f->glEnable(GL_DEPTH_TEST);
        this->f->glDepthFunc(GL_ALWAYS);
        this->f->glEnable(GL_BLEND);
        this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

        //qDebug()<< " ////ي////";
    ////qDebug("\033[31m paint 2\033[0m");
    ////////qDebug() <<"paint this->edit_mode : "<<this->edit_mode;

        if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            //////////////////////////////////////////
            //// OUTLINE RENDER TARGET ////////////////
            ///
            //FGEDataSelectedNodesStage* snsv = NULL;;
            if(this->edit_mode==FGE_INTERACTION_MODE_OBJECT){
                //snsv = this->data_project->selected_nodes->getCurrentStageNode();
            }else if(this->edit_mode==7){
                //snsv = this->data_project->selected_nodes->getFirstStageNode();
            }
            ////////qDebug() <<"paint snsv : "<<snsv->isEmpty();
            this->render_tarjet_outline->bind(this->f);
            /*this->f->glEnable(GL_DEPTH_TEST);
            this->f->glDepthFunc(GL_ALWAYS);
            this->f->glEnable(GL_BLEND);
            this->f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
            this->f->glClearColor(0.0, 0.0, 0.0, 1.0);
            this->f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            qDebug() <<"00000aint snsv : ";
            if(this->render_device!=NULL){

                this->render_device->veiw_pos = camera->getCurrentEye();
                this->render_device->projection_view_matrix = this->current_data_camera->projection->matrix*this->current_data_camera->view->matrix;
                this->render_device->drawOutlineObjects(this->f, this->data_project->selected_nodes, this->opperations_state);
            }

            this->render_tarjet_outline->release(this->f, context());

        }

        ////qDebug("\033[31m paint 3\033[0m");
        if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
            this->render_tarjet_outline->renderSelected(this->f, this->shader, this->WIDTH, this->HEIGHT);
        }

        //qDebug()<< " ////م////";

        ////qDebug("\033[31m paint 4\033[0m");
        view_opp->drawAxes(this->f, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, this->data_project, WIDTH, HEIGHT);


        //if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
        //    if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                //if(this->skin_conf->isBoneControl()){
                    if(this->render_device!=NULL){
                        this->render_device->veiw_pos = camera->getCurrentEye();
                        this->render_device->projection_view_matrix = this->current_data_camera->projection->matrix*this->current_data_camera->view->matrix;
                        this->render_device->drawOnlyArmatures(this->f, this->opperations_state);
                    }

                //}
        //    }
        //}

        ////////qDebug()<<"\033[34m "<<this->edit_mode<<" \033[0m";
        ////qDebug("\033[37m 00000000 \033[0m");

        if(this->object_module->selection_mesh->isDrug()){
            ////qDebug("\033[37m select->isDrug \033[0m");
            this->object_module->selection_mesh->drawArea(this->f);
        }else if(this->selection_mesh_editable->isDrug()){

            this->selection_mesh_editable->drawArea(this->f);
        }else{


            ////qDebug()<<"\033[38m object_model :  1\033[0m"<<this->opperations_state->object_model;
            ////qDebug()<<"\033[38m interaction_mode :  1\033[0m"<<this->opperations_state->interaction_mode;
            if(this->opperations_state->object_model==FGE_OBJECT_MESH){
                if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){

                    /*FGETransformation *transformation;
                    if(this->data_project->selected_nodes->getSize()==1){
                        transformation = this->data_project->selected_nodes->first_selected_item->item->transform;
                    }else{
                        transformation = this->data_project->selected_nodes->transformation;
                    }*/
                    this->initObjectModule();
                    this->object_module->renderGizmo(this->f, painter);


                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                    if(this->opperations_state->mesh_select==FGE_MESH_SELECT_VERTEX ||
                    this->opperations_state->mesh_select==FGE_MESH_SELECT_EDGE ||
                    this->opperations_state->mesh_select==FGE_MESH_SELECT_FACE ){

                        if(!this->data_project->selected_nodes->selected_nodes.isEmpty()){
                            glm::vec3 pos;


                            FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();

                            if(sn->calculateCenterOfSelectedVerticesOfNodes(pos))
                            {
                                qDebug()<<"M pos : ("<<pos.x<<", "<<pos.y<<", "<<pos.z<<")";
                                gizmos->setProjection(this->current_data_camera->projection->matrix);
                                gizmos->setView(this->current_data_camera->view->matrix);
                                gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
                                gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);

                                FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                glm::quat rt;
                                if(sn->getGlobalQuaternionFirstSelectedNode(rt)){
                                    transformation->setLocalQuaternion(rt);
                                }

                                transformation->updateLocalCalculation();

                                painter.endNativePainting();
                                gizmos->drawGizmo(this->f, transformation, painter);
                                delete transformation;
                                painter.beginNativePainting();

                            }

                        }
                    }
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_SCULPT){
                    glm::vec3 pos = glm::vec3(data_project->current_sculpt_item->position[0], data_project->current_sculpt_item->position[1], data_project->current_sculpt_item->position[2]);
                    glm::vec3 nrml = glm::vec3(data_project->current_sculpt_item->normal[0], data_project->current_sculpt_item->normal[1], data_project->current_sculpt_item->normal[2]);

                    glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);

                    float cos2a = glm::dot(glm::normalize(glm::vec3(0.0, 1.0, 0.0)), glm::normalize(nrml));
                    glm::vec3 fnr = glm::normalize(glm::cross(glm::normalize(glm::vec3(0.0, 1.0, 0.0)), glm::normalize(nrml)));
                    float angle = glm::acos(cos2a);
                    angle = (angle*180.0)/3.14159265358979323846;

                    if(angle!=0){
                        model = model*glm::toMat4(glm::angleAxis( glm::radians(angle), glm::vec3(fnr[0], fnr[1], fnr[2])));
                    }

                    this->sculpt->draw(this->f, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, model);

                }
            }else if(this->opperations_state->object_model==FGE_OBJECT_CURVE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_SURFACE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_TEXT){

            }else if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){

                /*if(data_project->keyboard_state->key_a){
                }else{*/
                    //if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                        //if(!data_project->selected_armatures->isEmpty()){
                            ////////qDebug()<<"\033[38m ooooooooo 1\033[0m";

                            gizmos->setProjection(this->current_data_camera->projection->matrix);
                            gizmos->setView(this->current_data_camera->view->matrix);
                            gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
                            gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);
                            painter.endNativePainting();
                            if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                                if(gizmos->isTranslation()){
                                    glm::vec3 pos;
                                    bool st = data_project->selected_armatures->getSelectionCenterForceBones(pos, false);
                                    if(st){
                                        FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                        //transformation->setParent(sns->getCurrentNode()->transform);
                                        transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                                        transformation->updateLocalCalculation();
                                        gizmos->drawGizmo(this->f, transformation, painter);
                                        delete transformation;
                                    }
                                }

                            }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                                if(gizmos->isTranslation()){
                                    data_project->selected_armatures->detectParentItems();
                                    QVector<FGEDataBone*> parents = data_project->selected_armatures->selected_parents_items;
                                    if(parents.size()==1){
                                        glm::vec3 pos;
                                        bool st = data_project->selected_armatures->getSelectionCenterForceBones(pos, true);
                                        FGEDataBone* par =parents.at(0);
                                        if(par->parent==NULL){
                                            glm::vec4 _pos = par->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
                                            pos = glm::vec3(_pos);
                                            if(st){
                                                FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                                transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);
                                                transformation->updateLocalCalculation();
                                                gizmos->drawGizmo(this->f, transformation, painter);
                                                delete transformation;
                                            }

                                        }
                                    }
                                }else if(gizmos->isRotation()){

                                    data_project->selected_armatures->detectParentItems();
                                    QVector<FGEDataBone*> parents = data_project->selected_armatures->selected_parents_items;
                                    if(parents.size()==1){
                                        FGEDataBone* bn = parents.at(0);
                                        //FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                        //QVector<FGEDataSelectedItemArmature*> selected_armatures = data_project->selected_armatures->selected_armatures;
                                        //if(selected_armatures.size()==1){
                                            //FGEDataSelectedItemArmature* sia = selected_armatures.at(0);
                                            //bn->transform->portTo(transformation);
                                            //transformation->setParent(sia->armature->transform);

                                            gizmos->drawGizmo(this->f, bn->transform, painter);

                                        //}
                                    }
                                }



                                //////qDebug()<<"\033[38m pos : \033[0m" <<pos[0]<<", "<<pos[1]<<", "<<pos[2];
                                //////qDebug()<<"\033[38m st : \033[0m"<<st;

                            }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                                if(this->skin_conf->isWeightControl()){
                                    int X = this->mapFromGlobal(QCursor::pos()).x();
                                    int Y = this->mapFromGlobal(QCursor::pos()).y();
                                    glm::vec2 curs_pos = glm::vec2(X, HEIGHT - Y);
                                    this->painting_skin_weights->draw(this->f, curs_pos, this->skin_conf->radius, this->skin_conf->strength);
                                }
                            }

                            painter.beginNativePainting();
                        //}
                    //}else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){

                    //}else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                        /*if(!sns->isEmpty()){
                            FGEDataNode *_item = sns->getCurrentNode();
                            if(_item!=NULL){
                                for(int i=0; i<_item->simples.size(); i++){
                                    FGEDataSimple* simple = _item->simples.at(i);
                                    if(simple->armature!=NULL){
                                        if(!simple->armature->selected.isEmpty()){
                                            FGEDataBone* selected = simple->armature->selected.at(0).second;
                                            gizmos->setProjection(this->projection->matrix);
                                            gizmos->setView(this->view->matrix);
                                            gizmos->setScaleFactor(this->projection->scaleFactor);
                                            gizmos->perspectiveIs(this->projection->is_perspective);

                                            //glm::vec3 pos;
                                            FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                            transformation->setParent(selected->transform);
                                            //transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                            painter.endNativePainting();
                                            gizmos->drawGizmo(this->f, transformation, painter);
                                            delete transformation;
                                            painter.beginNativePainting();
                                        }
                                    }
                                }
                            }
                        }*/
                   // }
                //}
            }

            /*if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){

            }else if(this->opperations_state->object_model==FGE_OBJECT_MESH){

                    if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){




                }else if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){

                }
                ////////qDebug()<<"\033[37m is 3 \033[0m";

            }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_SCULPT){
                            }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){ // DRAW GIZMO AT SELECTED BONE

            }*//*else if(this->edit_mode==6){
                if(gizmos->isMouseOpperation(FGE_MOUSE_POSE_BONE_IK_TRANLATION)){
                    FGEDataBone* selected_bone = this->data_project->getSelectedBone();
                    if(selected_bone!=NULL){
                        gizmos->setProjection(this->projection->matrix);
                        gizmos->setView(this->view->matrix);
                        gizmos->setScaleFactor(this->projection->scaleFactor);
                        gizmos->perspectiveIs(this->projection->is_perspective);

                        //glm::vec3 pos;
                        ///FGETransformation *transformation = new FGETransformation(NULL, NULL);
                        ///transformation->setParent(selected_bone->transform);
                        //transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                        gizmos->tempTransformationType(1);
                        painter.endNativePainting();
                        gizmos->drawGizmo(this->f, this->temp_transformation, painter);
                        gizmos->restorTransformationType();
                        ///delete transformation;
                        painter.beginNativePainting();

                    }
                }*/
                /*
                if(!data_project->selected_nodes->isEmpty()){
                    FGEDataNode *_item = this->data_project->selected_nodes->getCurrentNode();
                    if(_item!=NULL){
                        FGEDataSimple* simple = _item->simple;
                        if(simple->armature!=NULL){
                            if(!simple->armature->selected.isEmpty()){
                                FGEDataBone* selected = simple->armature->selected.at(0);
                                gizmos->setProjection(this->projection->matrix);
                                gizmos->setView(this->view->matrix);
                                gizmos->setScaleFactor(this->projection->scaleFactor);
                                gizmos->perspectiveIs(this->projection->is_perspective);

                                //glm::vec3 pos;
                                FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                transformation->setParent(selected->transform);
                                //transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                gizmos->tempTransformationType(2);
                                painter.endNativePainting();
                                gizmos->drawGizmo(this->f, transformation, painter);
                                gizmos->restorTransformationType();
                                delete transformation;
                                painter.beginNativePainting();
                            }

                        }
                    }
                }*/
            //}
                                /*FGEDataBone* selected = simple->armature->selected.at(0);
                                glm::mat4 sbm = simple->armature->transformationBone(selected);
                                glm::vec4 pos = sbm*glm::vec4(0.0, 0.0, 0.0, 1.0);
//////qDebug() << "@@@ armature->transformationBone : (" << pos[0]<<", "<<pos[1]<<", "<<pos[2]<<")";
                                gizmos->setProjection(this->projection->matrix);
                                gizmos->setView(this->view->matrix);
                                gizmos->setScaleFactor(this->projection->scaleFactor);
                                gizmos->perspectiveIs(this->projection->is_perspective);

                                FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                transformation->setParent(selected->transform);
                                transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);


                                if(simple->armature->type_selection==1){
                                    FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                    transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                                    transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                    painter.endNativePainting();
                                    gizmos->drawGizmo(this->f, transformation, painter);
                                    delete transformation;
                                    painter.beginNativePainting();

                                }else if(simple->armature->type_selection==0){
                                    FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                    transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                                    transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                    painter.endNativePainting();
                                    gizmos->drawGizmo(this->f, transformation, painter);
                                    delete transformation;
                                    painter.beginNativePainting();

                                }else if(simple->armature->type_selection==2){
                                    FGETransformation *transformation = new FGETransformation(NULL, NULL);
                                    transformation->setParent(this->data_project->selected_nodes->getCurrentNode()->transform);
                                    glm::mat4 sbm = simple->armature->transformationBone(selected);

                                    glm::vec3 j = selected->tip_pos-selected->base_pos;
                                    float s = glm::length(j);
                                    glm::mat4 trans = glm::translate(sbm, glm::vec3(0.0, 0.0, s));
                                    pos = trans*glm::vec4(0.0, 0.0, 0.0, 1.0);;

                                    transformation->setLocalVectorTranslation(pos[0], pos[1], pos[2]);

                                    painter.endNativePainting();
                                    gizmos->drawGizmo(this->f, transformation, painter);
                                    delete transformation;
                                    painter.beginNativePainting();

                                }*/
        }

        ////qDebug("\033[31m paint 6\033[0m");
        painter.beginNativePainting();
        create_new_object->draw(this->f, item_create_new_object, item_create_new_object->shaderProgram_plane, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, this->current_data_camera->projection->is_perspective, this->WIDTH, this->HEIGHT);
        painter.endNativePainting();


        ////qDebug("\033[31m paint 7\033[0m");



        //f->glDepthFunc(GL_ALWAYS);

        //f->glPushAttrib(GL_ALL_ATTRIB_BITS);
        //painter.setRenderHint(QPainter::Antialiasing);
        ///drawLegend(QPoint(WIDTH/2-50,HEIGHT/2-30), painter);

        //f->glPopAttrib();
        //f->glDepthFunc(GL_ALWAYS);

        painter.end();
        //f->glDepthFunc(GL_LESS);

        doneCurrent();

}

void FGEOpenGLWidget::drawLegend(QPoint p, QPainter &painter)
{
    const int Margin = 11;
    const int Padding = 6;
    painter.begin(this);
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
    painter.translate(p);
    painter.setPen(QColor(255, 239, 255));
    painter.setBrush(QColor(255, 0, 0, 255));
    painter.drawRect(rect);


    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect, Qt::AlignCenter, "Qt");

    painter.translate(Padding, Padding);
    textDocument.drawContents(&painter);

}

void FGEOpenGLWidget::resizeGL(int w, int h)
{
    this->f = openGLFunctions();
    this->f->glViewport(0, 0, w, h);

    WIDTH = w;
    HEIGHT = h;

    this->current_data_camera->screenHeight = h;
    this->current_data_camera->screenWidth = w;

    gizmos->gizmos_rotation->init(w, h);
    gizmos->setViewportWH(w, h);

    data_project->view_port_width = w;
    data_project->view_port_height = h;

    view_opp->initSizeScreen(WIDTH, HEIGHT);
    //draw_text->init(WIDTH, HEIGHT);

    this->render_tarjet->update(this->f, WIDTH, HEIGHT);
    this->render_tarjet_selection->update(this->f, WIDTH, HEIGHT);
    this->render_tarjet_outline->update(this->f, WIDTH, HEIGHT);



    if(this->current_data_camera->projection->is_perspective) {
        this->current_data_camera->projection->perspective.aspect =  (float)WIDTH / (float)HEIGHT;
        float fovPerPixel = 0.1 * 3.14159265358979323846 / 180;
        float fov = (float)HEIGHT * fovPerPixel;

        this->current_data_camera->projection->matrix = glm::perspective(
                    fov,
                    this->current_data_camera->projection->perspective.aspect,
                    this->current_data_camera->projection->perspective.near,
                    this->current_data_camera->projection->perspective.far
        );
    }else{
        if (WIDTH <= HEIGHT){
            this->current_data_camera->projection->ortho.bottom      = -1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.top         = 1.0*(GLfloat)HEIGHT / (GLfloat)WIDTH;
            this->current_data_camera->projection->ortho.left        = -1.0;
            this->current_data_camera->projection->ortho.right       = 1.0;
        }else{
            this->current_data_camera->projection->ortho.bottom      = -1.0;
            this->current_data_camera->projection->ortho.top         = 1.0;
            this->current_data_camera->projection->ortho.left        =  -1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
            this->current_data_camera->projection->ortho.right       =  1.0*(GLfloat)WIDTH / (GLfloat)HEIGHT;
        }
        this->current_data_camera->projection->matrix = glm::ortho(
                    this->current_data_camera->projection->ortho.left,
                    this->current_data_camera->projection->ortho.right,
                    this->current_data_camera->projection->ortho.bottom,
                    this->current_data_camera->projection->ortho.top,
                    this->current_data_camera->projection->ortho.znear,
                    this->current_data_camera->projection->ortho.zfar
        );
    }


}

void FGEOpenGLWidget::addNewCube()
{
    //FGECreateCubeModel newCube(this->data_project, -3.0, );
    //this->render_primitive->reInit(this->f, this->shader, this->data_project);
    update();

}
void FGEOpenGLWidget::initializeScene(FGEDataProject *data_project)
{
    this->data_project = data_project;
    initialized=1;
    update();
}


/////////////////////////////////////////////////////////////////////////
void FGEOpenGLWidget::view_oppUpdateCameraToSelectedAxe()
{
    ////////qDebug() << "@@@ up caremra : " << view_opp->hover_axe;

    view_opp->updateCameraToSelectedAxe(camera, this->data_project, this->current_data_camera->view->matrix);
    update();
    if(view_opp->key_camera>=10) {
        ////////qDebug() << "@@@ clode up caremra";
        view_opp->key_camera = 0;
        //view_opp->animation_camera = false;
        //view_opp->timer->stop();
    }else{
        ////////qDebug() << "@@@ ttttttt";
        QTimer::singleShot(30, this, SLOT(view_oppUpdateCameraToSelectedAxe()));
    }
}




bool FGEOpenGLWidget::gizmoArmaturePressMouse(glm::vec2 &curs_pos){
    FGEDataBone* selected_bone = this->data_project->getSelectedBone();
    if(selected_bone!=NULL){
        /*FGEDataArmature* selected_armature = this->data_project->getSelectedArmature();
        bool inv_ken = false;
        if(selected_armature!=NULL){
            for(int i=0; i<selected_armature->list_ik.size(); i++){
                FGEDataInverseKinematics* ik = selected_armature->list_ik.at(i);
                inv_ken = ik->hasTargetBone(selected_bone);
            }
        }*/
        gizmos->setProjection(this->current_data_camera->projection->matrix);
        gizmos->setView(this->current_data_camera->view->matrix);
        gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
        gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);


        if(this->data_project->selectedArmatureHasInverseKinematics()){
            gizmos->setMouseOpperation(FGE_MOUSE_POSE_BONE_IK_TRANLATION);

            //this->temp_transformation->init(selected_bone->parent->transform, NULL);
            //glm::mat m = selected_bone->transform->getLocalTransformation();
            //this->temp_transformation->setLocalTransformation(m);
            //glm::vec4 v = selected_bone->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
            //this->temp_transformation->setLocalVectorTranslation(v[0],v[1],v[2]);

            this->temp_transformation->init(NULL, NULL);
            /*glm::vec4 v = selected_bone->transform->getGlobalTransformation()*glm::vec4(0,0,0,1);
            this->temp_transformation->setLocalVectorTranslation(v[0],v[1],v[2]);*/
            glm::mat4 m0 = selected_bone->transform->getGlobalTransformation();
            this->temp_transformation->setLocalTransformation(m0);
            this->temp_transformation->updateLocalCalculation();
            this->trigger->updateDock(dock_parent);


            /*glm::vec3 lt = selected_bone->transform->getLocalVectorTranslation();
            glm::vec3 lr = selected_bone->transform->getLocalVectorRotation();
            glm::vec3 ls = selected_bone->transform->getLocalVectorScale();
            this->temp_transformation->setLocalVectorTranslation(lt[0], lt[1], lt[2]);
            this->temp_transformation->setLocalVectorRotation(lr[0], lr[1], lr[2]);
            this->temp_transformation->setLocalVectorScale(ls[0], ls[1], ls[2]);*/

            ////glm::mat4 mm = this->temp_transformation->getLocalTransformation()*glm::inverse(selected_bone->parent->transform->getGlobalTransformation());
            ///gizmos->hp_t.t0 = mm*glm::vec4(0,0,0,1);

            //gizmos->hp_t.t0 = selected_bone->transform->getLocalTransformation()*glm::vec4(0,0,0,1);

            //gizmos->hp_t.t0 = v;
            //gizmos->hp_t.r0 = selected_bone->parent->transform->getLocalVectorRotation();
            gizmos->tempTransformationType(1);
            if(gizmos->pressMouse(this->f, curs_pos, this->temp_transformation, context(), this->render_tarjet_selection)){
                doneCurrent();
                this->trigger->updateDock(dock_parent);
                gizmos->restorTransformationType();
                return true;
            }
            gizmos->restorTransformationType();
        }
    }
    return false;
}


bool FGEOpenGLWidget::selectArmaturePressMouse(glm::vec2 &curs_pos){
    if(this->selection_armature->pressSelect(
        (void*)this,
        this->f,
        this->camera->getCurrentEye(),
        this->light_tool,
        curs_pos,
        this->current_data_camera->view,
        this->current_data_camera->projection,
        this->shader_program_selection,
        context(),
        this->render_tarjet_selection,
        this->WIDTH,
        this->HEIGHT,
        this->opperations_state
    )){
        /*this->trigger->updateDock(dock_parent);//trigger((void *)this);
        emit this->trigger->updatePropertiesObject(1);*/
        //doneCurrent();

        doneCurrent();
        this->trigger->updateDock(dock_parent);
        return true;
    }else{
        update();
        return false;
    }
}
bool FGEOpenGLWidget::selectionArmatureEditPressMouse(glm::vec2 &curs_pos){
    if(!this->data_project->keyboard_state->key_shift){
        this->data_project->selected_armatures->clair();
    }
    if(this->selection_armature_editable->pressSelect(
        (void*)this,
        this->f,
        this->camera->getCurrentEye(),
        this->light_tool,
        curs_pos,
        this->current_data_camera->view,
        this->current_data_camera->projection,
        this->shader_program_selection,
        context(),
        this->render_tarjet_selection,
        this->WIDTH,
        this->HEIGHT,
        this->opperations_state,
                true
    )){

        doneCurrent();
        this->trigger->updateDock(dock_parent);
        return true;
    }else{
        update();
        return false;
    }
}
bool FGEOpenGLWidget::selectionArmaturePosePressMouse(glm::vec2 &curs_pos){
    /*if(this->selection_armature->pressSelect(
        (void*)this,
        this->f,
        this->camera->current_eye,
        this->light_tool,
        curs_pos,
        this->view,
        this->projection,
        this->shader_program_selection,
        context(),
        this->render_tarjet_selection,
        this->WIDTH,
        this->HEIGHT,
        this->opperations_state
    )){

        doneCurrent();
        this->trigger->updateDock(dock_parent);
        return true;
    }else{
        update();

    }*/return false;
}

bool FGEOpenGLWidget::selectionEditPressMouse(glm::vec2 &curs_pos){
    if(this->selection_mesh_editable->pressSelect((void*)this,
                                           this->f,
                                           this->camera->getCurrentEye(),
                                           this->light_tool,
                                           curs_pos,
                                           this->current_data_camera->view,
                                           this->current_data_camera->projection,
                                           this->shader_program_selection,
                                           context(),
                                           this->render_tarjet_selection,
                                           this->WIDTH,
                                           this->HEIGHT,
                                           this->opperations_state)){
        /*this->trigger->updateDock(dock_parent);//trigger((void *)this);
        emit this->trigger->updatePropertiesObject(1);*/
        //doneCurrent();
        ////////qDebug()<<"\033[38m select_edit_mode->pressSelect \033[0m";
        doneCurrent();
        this->trigger->updateDock(dock_parent);
        return true;
    }else{
        update();
        return false;
    }
}

bool FGEOpenGLWidget::sculptPressMouse(glm::vec2 &curs_pos){
    this->sculpt->drag = true;
    this->sculpt->old_cursor = curs_pos;
    if(selection_mesh_editable->radar(f, SELECT_DEFAULT_STRATEGY, curs_pos,  this->camera->getCurrentEye(), this->current_data_camera->view, this->current_data_camera->projection, context(), this->render_tarjet_selection, this->opperations_state)){
        this->sculpt->rayIntersect(this->f, this->data_project->first_scene->first_node, data_project, curs_pos, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, WIDTH, HEIGHT);
        this->sculpt->appelySculptDraw(this->f, this->data_project->first_scene->first_node, data_project);
        this->trigger->updateDock(dock_parent);
        doneCurrent();
        return true;
    }
    return false;
}

bool FGEOpenGLWidget::paintWeightsMouse(glm::vec2 &curs_pos){

        //glm::vec2 curs_s =  curs_pos-this->painting_skin_weights->old_cursor;
        //float length = glm::length(curs_s);
        //if(length>2) {
            //this->painting_skin_weights->old_cursor = curs_pos;
            if(selection_armature_paint_weight->radar(f, this->skin_conf->radius, SELECT_DEFAULT_STRATEGY, curs_pos,  this->camera->getCurrentEye(), this->current_data_camera->view, this->current_data_camera->projection, context(), this->render_tarjet_selection, this->opperations_state)){
                FGEDataNode *node = this->data_project->first_scene->first_node;

                FGEDataBone* bn = data_project->selected_armatures->getFirstSelectedBone();

                for(int i=0; i<node->selection_edit_mode->points.size(); i++){
                    FGEDataPointItem* point = node->selection_edit_mode->points.at(i);
                    for(int j=0; j<node->controller_skins.size();j++){
                        FGEDataSkin *skin = node->controller_skins.at(j);
                        skin->addData(bn, point->index_position, this->skin_conf);
                    }
                }

                for(int j=0; j<node->controller_skins.size();j++){
                    FGEDataSkin *skin = node->controller_skins.at(j);
                    skin->updateBuffer(this->f, bn);
                }
                return true;
            }
            return false;

}
/*glm::mat4 FGEGLWidgetWorld::getRotationToParents(FGENodeOS *node){
    if(node!=NULL){
        return getRotationToParents(node->parent)*node->transform.matrix_r;
    }else{
        return glm::mat4(1.0);
    }
}
*/

bool FGEOpenGLWidget::gizmoMeshPressMouse(glm::vec2 &curs_pos){
    //FGEDataNode *current_node = NULL;

    glm::vec3 center;
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->calculateCenterOfSelectedVerticesOfNodes(center))
    {

        gizmos->setProjection(this->current_data_camera->projection->matrix);
        gizmos->setView(this->current_data_camera->view->matrix);
        gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
        gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);

        this->temp_transformation->init(NULL, NULL);
        this->temp_transformation->setLocalVectorTranslation(center[0], center[1], center[2]);
        glm::quat rt;
        if(sn->getGlobalQuaternionFirstSelectedNode(rt)){
            this->temp_transformation->setLocalQuaternion(rt);
        }
        this->temp_transformation->updateLocalCalculation();

        this->rr_old_trans = this->temp_transformation->getLocalTransformation();

        if(gizmos->pressMouse(this->f, curs_pos, this->temp_transformation, context(), this->render_tarjet_selection)){
            doneCurrent();
            this->trigger->updateDock(dock_parent);
            return true;
        }
    }

    return false;

    /*for(int _i=0; _i<this->data_project->selected_nodes->selected_nodes.size(); _i++){
        FGEDataNode *node = this->data_project->selected_nodes->selected_nodes.at(_i);
        //FGEDataNode *node = sns->getCurrentNode();

    }

    if(!sns->isEmpty()){
        glm::vec3 pos;
        if(sns->getSelectionCenterForce(pos)){
        }
    }
    return false;*/
}

bool FGEOpenGLWidget::gizmoMeshMoveMouse(glm::vec2 &curs_pos){

    glm::vec3 center;
    if(this->data_project->selected_nodes->calculateCenterOfSelectedVerticesOfNodes(center)){
        gizmos->setProjection(this->current_data_camera->projection->matrix);
        gizmos->setView(this->current_data_camera->view->matrix);
        gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
        gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);

        glm::mat4 mx0 = this->temp_transformation->getLocalTransformation();

        if(gizmos->moveMouse(this->f, curs_pos, this->temp_transformation)){

            glm::mat4 mx1 = this->temp_transformation->getLocalTransformation();

            this->data_project->selected_nodes->updateVerticesFacePosition(this->f, mx0, mx1);

            emit this->trigger->updatePropertiesObject(0);
            emit this->trigger->updateAllWIdgetsOpenGl();
            doneCurrent();
            return true;
        }

    }

    return false;/**/
}

bool FGEOpenGLWidget::selectionEditMoveMouse(glm::vec2 &curs_pos){

}

bool FGEOpenGLWidget::gizmoArmatureMoveMouse(glm::vec2 &curs_pos){
    FGEDataBone* selected_bone = this->data_project->getSelectedBone();
    if(selected_bone!=NULL){
        gizmos->setProjection(this->current_data_camera->projection->matrix);
        gizmos->setView(this->current_data_camera->view->matrix);
        gizmos->setScaleFactor(this->current_data_camera->projection->scaleFactor);
        gizmos->perspectiveIs(this->current_data_camera->projection->is_perspective);

        if(gizmos->isMouseOpperation(FGE_MOUSE_POSE_BONE_IK_TRANLATION)){

            gizmos->tempTransformationType(1);
            if(gizmos->moveMouse(this->f, curs_pos, this->temp_transformation/*selected_bone->transform*/)){

                if(this->data_project->current_inverse_kinematics!=NULL){
                    FGEDataBone *base = this->data_project->current_inverse_kinematics->source;
                    FGEDataBone *endEffector = this->data_project->current_inverse_kinematics->target;
                    glm::vec4 point_g_target = this->temp_transformation->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);

                    /*findNewAngles(endEffector, base, point_g_target, 10);*/
                    for(int i=0; i<500; i++){
                        if(!CCDMode(endEffector, base, point_g_target)){
                            i=500;
                        }
                    }
                }

                emit this->trigger->updatePropertiesObject(0);
                emit this->trigger->updateAllWIdgetsOpenGl();
                doneCurrent();
                gizmos->restorTransformationType();
                return true;
            }
            gizmos->restorTransformationType();
        }
        return false;
    }
}

bool FGEOpenGLWidget::sculptMoveMouse(glm::vec2 &curs_pos){
    if(this->sculpt->drag){
        glm::vec2 curs_s =  curs_pos-this->sculpt->old_cursor;
        float length = glm::length(curs_s);
        if(length>20) {
            this->sculpt->old_cursor = curs_pos;

            if(selection_mesh_editable->radar(f, SELECT_DEFAULT_STRATEGY, curs_pos,  this->camera->getCurrentEye(), this->current_data_camera->view, this->current_data_camera->projection, context(), this->render_tarjet_selection, this->opperations_state)){
                this->sculpt->rayIntersect(this->f, this->data_project->first_scene->first_node, data_project, curs_pos, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, WIDTH, HEIGHT);
                this->sculpt->appelySculptDraw(this->f, this->data_project->first_scene->first_node, data_project);
                this->trigger->updateDock(dock_parent);
                return true;
            }
        }
    }else{
        if(selection_mesh_editable->radar(f, SELECT_DEFAULT_STRATEGY, curs_pos,  this->camera->getCurrentEye(), this->current_data_camera->view, this->current_data_camera->projection, context(), this->render_tarjet_selection, this->opperations_state)){
            this->sculpt->rayIntersect(this->f, this->data_project->first_scene->first_node, data_project, curs_pos, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, WIDTH, HEIGHT);
            this->trigger->updateDock(dock_parent);
            return true;
        }
    }
    return false;
}


bool FGEOpenGLWidget::gizmoMeshReleaseMouse(glm::vec2 &curs_pos){
    if(gizmos->releazeMouse()){
        //if(!sns->isEmpty()){
            this->trigger->updateDock(dock_parent);
            update();
            doneCurrent();
            return true;
        //}
    }/**/
    return false;
}
bool FGEOpenGLWidget::selectionEditReleaseMouse(glm::vec2 &curs_pos){
    if(this->selection_mesh_editable->releazeSelect(
                (void*)this,
                this->f,
                curs_pos,
                light_tool,
                this->current_data_camera->view,
                this->current_data_camera->projection,
                this->shader_program_selection,
                context(),
                this->render_tarjet_selection,
                this->WIDTH,
                this->HEIGHT,
                this->opperations_state
    )){
        this->trigger->trigger((void *)this);
        update();
        return true;
    }
    return false;
}

void FGEOpenGLWidget::initObjectModule(){
    this->object_module->veiw_pos = this->camera->getCurrentEye();
    this->object_module->light_tool = this->light_tool;
    this->object_module->view = this->current_data_camera->view;
    this->object_module->projection = this->current_data_camera->projection;
    this->object_module->shader_program_selection = this->shader_program_selection;
    this->object_module->oglc = context();
    this->object_module->render_tarjet_selection = this->render_tarjet_selection;
    this->object_module->WIDTH = this->WIDTH;
    this->object_module->HEIGHT = this->HEIGHT;
    this->object_module->opperations_state = this->opperations_state;
    this->object_module->slf = (void*)this;

}

void FGEOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();
    //FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();
    glm::vec2 curs_pos = glm::vec2(event->x(), HEIGHT - event->y());

    if(event->button() == Qt::MiddleButton){
        camera->m_lastPos = glm::vec2(event->pos().x(), event->pos().y());
        camera->mousePress(curs_pos[0], curs_pos[1],this->data_project->keyboard_state->key_shift);
        update();
    }else if (event->button() == Qt::RightButton){
        area_menu->show(mapToGlobal(event->pos()));
    }else{


        if(create_new_object->isCreation()){
            create_new_object->setProjectionMatrix(this->current_data_camera->projection->matrix);
            //create_new_object->setView(struct_project->scene_current->view->matrix);
            create_new_object->setViewMatrix(this->current_data_camera->view->matrix);
            create_new_object->setScaleFactor(this->current_data_camera->projection->scaleFactor);
            create_new_object->setIsPerspective(this->current_data_camera->projection->is_perspective);

            create_new_object->pressSelect(curs_pos);
            this->trigger->updateDock(dock_parent);
            return;

        }else{
            if(view_opp->hover_axe!=0){
                view_opp->animation_camera = false;
                view_opp->key_camera = 0;
                QTimer::singleShot(30, this, SLOT(view_oppUpdateCameraToSelectedAxe()));
                doneCurrent();
                return;
            }


            if(this->opperations_state->object_model==FGE_OBJECT_MESH){
                if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                    this->gizmos->init(this->current_data_camera->projection,this->current_data_camera->view);
                    this->object_module->veiw_pos = this->camera->getCurrentEye();
                    this->object_module->light_tool = this->light_tool;
                    this->object_module->view = this->current_data_camera->view;
                    this->object_module->projection = this->current_data_camera->projection;
                    this->object_module->shader_program_selection = this->shader_program_selection;
                    this->object_module->oglc = context();
                    this->object_module->render_tarjet_selection = this->render_tarjet_selection;
                    this->object_module->WIDTH = this->WIDTH;
                    this->object_module->HEIGHT = this->HEIGHT;
                    this->object_module->opperations_state = this->opperations_state;
                    this->object_module->slf = (void*)this;


                    if(this->object_module->gizmoPressMouse(this->f, curs_pos)){
                        this->trigger->updateDock(dock_parent);
                    }else if(this->object_module->objectPressMouse(this->f, curs_pos)){

                    }
                    update();
                    doneCurrent();
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                    if(!this->gizmoMeshPressMouse(curs_pos)){
                        this->selectionEditPressMouse(curs_pos);
                    }
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_SCULPT){
                    this->sculptPressMouse(curs_pos);
                }
            }else if(this->opperations_state->object_model==FGE_OBJECT_CURVE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_SURFACE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_TEXT){

            }else if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){
                if(data_project->keyboard_state->key_a){
                    data_project->keyboard_state->key_a = false;
                }else{
                    if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                        if(!this->gizmoArmaturePressMouse(curs_pos)){
                            ////////qDebug() << "@@@ selectArmaturePressMouse @@@";
                            this->selectArmaturePressMouse(curs_pos);
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                        //qDebug() << "--@@@ FGE_OBJECT_ARMATURE @@@";
                        if(this->armature_edit->gizmoArmatureEditPressMouse(this->f, this->current_data_camera->projection->matrix,this->current_data_camera->view->matrix, this->current_data_camera->projection->scaleFactor, this->current_data_camera->projection->is_perspective, gizmos, curs_pos, context(), this->render_tarjet_selection)){
                            update();
                            //qDebug() << "--@@@ bbbb @@@";
                        }else{
                            //qDebug() << "--@@@ nnnn @@@";
                            if(!this->data_project->keyboard_state->key_shift){
                                this->data_project->selected_armatures->clair();
                            }
                            if(this->selection_armature_editable->pressSelect(
                                (void*)this,
                                this->f,
                                this->camera->getCurrentEye(),
                                this->light_tool,
                                curs_pos,
                                this->current_data_camera->view,
                                this->current_data_camera->projection,
                                this->shader_program_selection,
                                context(),
                                this->render_tarjet_selection,
                                this->WIDTH,
                                this->HEIGHT,
                                this->opperations_state,
                                true
                            )){

                                doneCurrent();
                                this->trigger->updateDock(dock_parent);
                            }else{
                                update();
                            }

                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                        if(this->armature_pose->gizmoPressMouse(this->f, this->current_data_camera->projection->matrix,this->current_data_camera->view->matrix, this->current_data_camera->projection->scaleFactor, this->current_data_camera->projection->is_perspective, gizmos, curs_pos, context(), this->render_tarjet_selection)){
                            update();
                        }else{
                            if(!this->data_project->keyboard_state->key_shift){
                                this->data_project->selected_armatures->clair();
                            }
                            if(this->selection_armature_editable->pressSelect(
                                (void*)this,
                                this->f,
                                this->camera->getCurrentEye(),
                                this->light_tool,
                                curs_pos,
                                this->current_data_camera->view,
                                this->current_data_camera->projection,
                                this->shader_program_selection,
                                context(),
                                this->render_tarjet_selection,
                                this->WIDTH,
                                this->HEIGHT,
                                this->opperations_state,
                                false
                            )){

                                update();
                                doneCurrent();
                                this->trigger->updateDock(dock_parent);
                            }else{
                                update();
                            }
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                        ////qDebug() <<"b : 0";
                        if(this->skin_conf->isBoneControl()){
                            if(!this->data_project->keyboard_state->key_shift){
                                this->data_project->selected_armatures->clair();
                            }
                            if(this->selection_armature_editable->pressSelect(
                                (void*)this,
                                this->f,
                                this->camera->getCurrentEye(),
                                this->light_tool,
                                curs_pos,
                                this->current_data_camera->view,
                                this->current_data_camera->projection,
                                this->shader_program_selection,
                                context(),
                                this->render_tarjet_selection,
                                this->WIDTH,
                                this->HEIGHT,
                                this->opperations_state,
                                false
                            )){

                                update();
                                doneCurrent();
                                this->trigger->updateDock(dock_parent);
                            }else{
                                update();
                            }
                        }else if(this->skin_conf->isWeightControl()){
                            this->painting_skin_weights->drag = true;
                            this->painting_skin_weights->old_cursor = curs_pos;
                            this->paintWeightsMouse(curs_pos);
                        }

                    }
                }

            }
        }
    }

}

void FGEOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();
    //this->setFocus();
    glm::vec2 curs_pos = glm::vec2(event->x(), HEIGHT - event->y());
    //FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();
    //this->setFocus();

    //cursor_x_t->text = QString::number(event->x()).toStdString();
    //cursor_y_t->text = QString::number(event->y()).toStdString();

    view_opp->hover_axe = 0;
    if (event->buttons() == Qt::MiddleButton) {
        QRect bounds = rect();
        float x, y;
        camera->mouseBoundaryCorrection(event->pos().x(),event->pos().y(), bounds.right(), bounds.bottom(), x, y);
        QPoint targetPos = mapToGlobal(QPoint(x, y));
        QCursor::setPos(targetPos);

        camera->mouseMove(x, y, event->pos().x(), event->pos().y());
        update();
    }else{

        if(create_new_object->isCreation()){
            create_new_object->setProjectionMatrix(this->current_data_camera->projection->matrix);
            create_new_object->setViewMatrix(this->current_data_camera->view->matrix);
            create_new_object->setScaleFactor(this->current_data_camera->projection->scaleFactor);
            create_new_object->setIsPerspective(this->current_data_camera->projection->is_perspective);
            create_new_object->moveSelect(this->f, curs_pos, WIDTH, HEIGHT);
            this->trigger->updateDock(dock_parent);
            return;
        }else{
            if(view_opp->mouseHover(this->f, context(), this->render_tarjet_selection, event->x(), event->y(), this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, this->data_project, this->WIDTH, this->HEIGHT)){
                update();
            }


            if(this->opperations_state->object_model==FGE_OBJECT_MESH){
                if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){

                    if(!this->object_module->gizmoMoveMouse(this->f, curs_pos)){
                        ////////qDebug() << "@@@ selectionMoveMouse @@@";
                        this->object_module->objectMoveMouse(this->f, curs_pos);
                    }

                    update();
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                    if(!this->gizmoMeshMoveMouse(curs_pos)){
                        this->selection_mesh_editable->moveSelect(this->f, curs_pos, WIDTH, HEIGHT);
                        update();
                    }
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_SCULPT){
                    this->sculptMoveMouse(curs_pos);
                }
            }else if(this->opperations_state->object_model==FGE_OBJECT_CURVE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_SURFACE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_TEXT){

            }else if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){
                if(data_project->keyboard_state->key_a){
                    if(this->armature_edit->gizmoArmatureEditDragMouse(this->f, this->gizmos, curs_pos)){
                        update();
                    }
                }else{
                    if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                        ////////qDebug() << "--@@@ FGE_OBJECT_ARMATURE @@@";

                        if(this->armature_edit->gizmoArmatureEditMoveMouse(this->f, this->current_data_camera->projection->matrix,this->current_data_camera->view->matrix, this->current_data_camera->projection->scaleFactor, this->current_data_camera->projection->is_perspective, gizmos, curs_pos)){
                            update();
                        }else{
                            //this->selectionArmatureEditPressMouse(curs_pos);
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                        if(this->armature_pose->gizmoMoveMouse(this->f, this->current_data_camera->projection->matrix,this->current_data_camera->view->matrix, this->current_data_camera->projection->scaleFactor, this->current_data_camera->projection->is_perspective, gizmos, curs_pos)){
                            update();
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                        if(this->skin_conf->isBoneControl()){
                            if(this->armature_pose->gizmoMoveMouse(this->f, this->current_data_camera->projection->matrix,this->current_data_camera->view->matrix, this->current_data_camera->projection->scaleFactor, this->current_data_camera->projection->is_perspective, gizmos, curs_pos)){
                                update();
                            }
                        }else if(this->skin_conf->isWeightControl()){

                            if(this->painting_skin_weights->drag){
                                this->painting_skin_weights->old_cursor = curs_pos;
                                this->paintWeightsMouse(curs_pos);
                            }

                            this->painting_skin_weights->calculatePositionCircle(curs_pos, this->current_data_camera->view->matrix, this->current_data_camera->projection->matrix, WIDTH, HEIGHT);
                            this->trigger->updateDock(dock_parent);
                        }

                    }

                }


            }



        }
    }

    doneCurrent();
}

void FGEOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();

    this->setFocus();
    //FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();
    glm::vec2 curs_pos = glm::vec2(event->x(), HEIGHT - event->y());

    if (event->buttons() == Qt::MiddleButton) {
        camera->mouseRelease();
        update();
    }else{
        if(create_new_object->isCreation()){
            create_new_object->releaseSelect(curs_pos, WIDTH, HEIGHT);
            this->trigger->updateDock(dock_parent);
            return;
        }else{

            if(this->opperations_state->object_model==FGE_OBJECT_MESH){
                if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){

                    if(this->object_module->gizmoReleaseMouse()){
                        ////////qDebug() << "@@@ selectionReleaseMouse 2 @@@";
                    }else{
                        //if(this->select->isDrug()){
                            ////////qDebug() << "@@@ selectionReleaseMouse h @@@";
                            this->object_module->objectReleaseMouse(this->f, curs_pos);
                        //}
                    }/**/

                    update();

                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                    if(!this->gizmoMeshReleaseMouse(curs_pos)){
                        this->selectionEditReleaseMouse(curs_pos);
                        update();
                    }
                }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_SCULPT){
                    this->sculpt->drag = false;
                }

            }else if(this->opperations_state->object_model==FGE_OBJECT_CURVE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_SURFACE){

            }else if(this->opperations_state->object_model==FGE_OBJECT_TEXT){

            }else if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){


                if(this->armature_edit->gizmoArmatureEditReleaseMouse(gizmos)){
                    update();
                }else{
                    //this->selectArmaturePressMouse(curs_pos);
                }

                if(data_project->keyboard_state->key_a){
                    if(this->armature_edit->gizmoArmatureEditDragMouse(this->f, this->gizmos, curs_pos)){
                        update();
                    }
                }else{
                    if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_OBJECT){
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                        if(this->armature_edit->gizmoArmatureEditReleaseMouse(gizmos)){
                            update();
                        }else{
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_POSE){
                        if(this->armature_pose->gizmoReleaseMouse(gizmos)){
                            update();
                        }
                    }else if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_WEIGHT_PAINT){
                        ////qDebug() <<"e : 0";
                        if(this->skin_conf->isWeightControl()){
                            this->painting_skin_weights->drag = false;
                        }
                    }
                }
            }
        }
    }
    doneCurrent();
}

void FGEOpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();

    //FGEDataSelectedNodesStage* sns = this->data_project->selected_nodes->getCurrentStageNode();
    if(event->key() == Qt::Key_Shift)
    {
        this->data_project->keyboard_state->key_shift = true;
        //camera->setKeyShift(true);
        update();
    }else if(event->key() == Qt::Key_E){
        ////////qDebug() << "@@@ Key_E 2 @@@";
        if(this->opperations_state->object_model==FGE_OBJECT_ARMATURE){
            if(this->opperations_state->interaction_mode==FGE_INTERACTION_MODE_EDIT){
                if(this->armature_edit->createNewBones()){
                    update();
                }
            }

        }
        /*FGEDataNode *item = sns->getFirstItem();
        if(item!=NULL){
            if(edit_mode==1){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    /*FGEExtrudeLines extrude;
                    extrude.extrude(f, mesh);*//*
                }
            }else if(edit_mode==2){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    FGEExtrudeLines extrude;
                    extrude.extrude(f, mesh);
                    this->trigger->updateDock(dock_parent);
                }
            }else if(edit_mode==3){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    /*FGEDataMesh *mesh = simple->mesh.at(i);
                    FGEExtrudeLines extrude;
                    extrude.extrude(f, mesh);*//*
                }
            }else
            }
        }*/

    }else if(event->key() == Qt::Key_F){
        /*FGEDataNode *item = sns->getFirstItem();
        if(item!=NULL){
            if(edit_mode==1){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                }
            }else if(edit_mode==2){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    FGEFill fill;
                    fill.fillSelectedEdges(f, mesh);
                    this->trigger->updateDock(dock_parent);
                }
            }else if(edit_mode==3){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    //FGEFill fill;
                    //fill.fillSelectedEdges(f, mesh);
                    this->trigger->updateDock(dock_parent);
                }
            }
        }*/
    }else if(event->key() == Qt::Key_D){
        int _om = this->opperations_state->object_model;
        int _im = this->opperations_state->interaction_mode;

        if(_om==FGE_OBJECT_ARMATURE){
            if(_im==FGE_INTERACTION_MODE_EDIT){
                if(this->armature_edit->deleteBones()){
                    update();
                }
            }

        }else if(_om==FGE_OBJECT_MESH){
            if(_im==FGE_INTERACTION_MODE_EDIT){
                int _ms = this->opperations_state->mesh_select;

                if(_ms==FGE_MESH_SELECT_VERTEX){

                }else if(_ms==FGE_MESH_SELECT_EDGE){

                }else if(_ms==FGE_MESH_SELECT_FACE ){
                    /*FGEDeleteFaces _delete;
                    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
                    for (int i = 0; i < sn->selected_nodes.size(); i++){
                        FGEDataNode* node = sn->selected_nodes.at(i);
                        _delete.deleteSelectedFaces(f, node);
                    }
                    this->trigger->updateDock(dock_parent);*/
                }
            }
        }

        /*FGEDataNode *item =sns->getFirstItem();
        if(item!=NULL){
            if(edit_mode==1){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                }
            }else if(edit_mode==2){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    this->trigger->updateDock(dock_parent);
                }
            }else if(edit_mode==3){
                FGEDataSimple* simple = item->simple;
                for(int i=0; i<simple->mesh.size(); i++){
                    FGEDataMesh *mesh = simple->mesh.at(i);
                    FGEDeleteFaces _delete;
                    _delete.deleteSelectedFaces(f, mesh);
                    this->trigger->updateDock(dock_parent);
                }
            }
        }*/
    }
    doneCurrent();

    /**else if(event->key() == Qt::Key_Up){
        ////////qDebug() << "--Key_Up";
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

void FGEOpenGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    makeCurrent();
    this->f = openGLFunctions();

    if(event->key() == Qt::Key_Shift)
    {
        this->data_project->keyboard_state->key_shift = false;
        //camera->setKeyShift(false);
    }
    doneCurrent();
}

void FGEOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    camera->zoom(event->angleDelta().y());
    update();
    event->accept();
}

// CCD Mode IK for right arm
bool FGEOpenGLWidget::CCDMode(FGEDataBone* endEffector, FGEDataBone* base, glm::vec4 &point_g_target)
{

    int i=0;
    if(endEffector!=NULL && base!=NULL ){
        FGEDataBone* cur = endEffector;
        while (cur!= base){
            // get 3 points

            glm::vec4 point_g_effector = endEffector->transform->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);

            glm::vec3 psm0, psm1, psm2;
            psm0 = cur->parent->transform->getGlobalTransformation()/point_g_effector;
            psm1 = cur->parent->transform->getGlobalTransformation()/point_g_target;
            //psm2 = cur->parent->transform->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);

            //psm0 = psm0-psm2;
            //psm1 = psm1-psm2;
            ////////qDebug()<<"------------------  psm0 : ("<<psm0[0]<<", "<<psm0[1]<<", "<<psm0[2]<<")";
            ////////qDebug()<<"------------------  psm1 : ("<<psm1[0]<<", "<<psm1[1]<<", "<<psm1[2]<<")";


            ////////qDebug()<<"------------------  psm0 : ("<<psm0[0]<<", "<<psm0[1]<<", "<<psm0[2]<<")";
            ////////qDebug()<<"----angle--------------  psm1 : ("<<psm1[0]<<", "<<psm1[1]<<", "<<psm1[2]<<")";

            /*glm::mat4 _m = cur->parent->transform->getGlobalTransformation();
            _m = _m*glm::inverse(q);
            glm::vec3 ct = _m*glm::vec4(0, 0, 0, 1);*/


            // compute cos theta and rotation axis r
            glm::vec3 _v = glm::normalize(glm::cross(glm::normalize(psm0), glm::normalize(psm1)));

            //glm::vec3 r = glm::normalize(glm::cross(e_c, t_c));

            if(qIsNaN(_v[0]) || qIsNaN(_v[1]) || qIsNaN(_v[2])){
            }else{
                float cos2a  = glm::dot(glm::normalize(psm0), glm::normalize(psm1));
                float angle = glm::acos(cos2a);
                float deg = (angle*180.0)/3.14159265358979323846;

                if(deg>0.0001){
                    ////////qDebug()<<"------------------  angle : ("<<angle<<")";
                    glm::quat quat = glm::angleAxis(angle, glm::vec3(_v[0], _v[1], _v[2]));
                    cur->parent->transform->appendLocalQuaternion(quat);
                    cur->parent->transform->updateLocalCalculation();
                    ////////qDebug()<<"------------------  r : ("<<_v[0]<<", "<<_v[1]<<", "<<_v[2]<<")";
                    i++;
                }
            }
            cur = cur->parent;
        }
    }
    if(i==0) return false;
    else return true;
}

void FGEOpenGLWidget::findNewAngles(FGEDataBone *endEffector, FGEDataBone *base, glm::vec3 target, int iterations) {
    bool found = false;
    glm::vec3 rotAxis;
    glm::quat rot;
    while(!found && iterations--) {
        FGEDataBone * currentBone = endEffector;
        while(currentBone->parent != NULL && currentBone != base) {
            glm::vec4 endPosition = endEffector->transform->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);;
            glm::vec4 startPosition = currentBone->parent->transform->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);
            glm::vec3 toTarget = glm::normalize(glm::vec3(target[0]-startPosition[0], target[1]-startPosition[1], target[2]-startPosition[2]));
            glm::vec3 toEnd = glm::normalize(glm::vec3(endPosition[0]-startPosition[0], endPosition[1]-startPosition[1], endPosition[2]-startPosition[2]));

            float clip_angle = 0.05;

            float angle;
            angle = std::acos(std::max(std::min(glm::dot(toEnd, toTarget), 1.0f), -1.0f));

            if (angle >= 0.005){
                if (angle > clip_angle) angle = clip_angle;

                rotAxis = glm::normalize(glm::cross(toEnd, toTarget));
                rotAxis = currentBone->parent->transform->getGlobalMatrixTranslation()/glm::vec4(rotAxis[0],rotAxis[1],rotAxis[2], 1);

                rot = glm::angleAxis(angle, rotAxis);
                currentBone->parent->transform->appendLocalQuaternion(rot);
                currentBone->parent->transform->updateLocalCalculation();
            }else {
                found = true;
            }

            /*if(qIsNaN(crossResult[0]) || qIsNaN(crossResult[1]) || qIsNaN(crossResult[2])){
                found = true;
            }else{
                float angle = glm::acos(cosine);
                float deg = (angle*180.0)/3.14159265358979323846;

            if(deg>0.0001){
              glm::quat quat = glm::angleAxis(angle, crossResult);
              currentBone->parent->transform->appendLocalQuaternion(quat);
          }else{
              found = true;
          }*/

          /*toTarget[0] = -toTarget[0];
          toTarget[1] = -toTarget[1];
          toTarget[2] = -toTarget[2];

          glm::vec3 temp = endEffector->transform->getGlobalTransformation()*glm::vec4(0, 0, 0, 1);
          temp[0] = temp[0]-target[0];
          temp[1] = temp[1]-target[1];
          temp[2] = temp[2]-target[2];
          if(glm::dot(temp, toTarget) < 0.001) {
            found = true;
            printf("target reached\n");
          }*/

            currentBone = currentBone->parent;
        }
    }
}
