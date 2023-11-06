#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //07 82 15 70 93



    this->project = new FGEProject();
    project->setNamePoject("anime");
    project->setLocationPoject("/home/corolo/");
    project->createNewProject();

    FGEDataScene *data_scene = new FGEDataScene();
    data_scene->name = "scene 01";
    data_scene->color = glm::vec4(0.443, 0.443, 0.443, 1.0);
    data_scene->id   = 0;
    //scene->type = "scene";
    //scene->depth = 1.0;
    //data_scene->projection->is_set = false;
    data_scene->next = NULL;
    data_scene->prev = NULL;
    data_scene->first_node = NULL;
    data_scene->last_node = NULL;

    project->data_project->appendNewScene(data_scene);
    project->data_project->current_scene   = data_scene;
    project->data_project->screen_buffer.created_frame_buffer = false;

    this->trigger = new FGETriggerFunction();
    this->project->data_project->trigger = this->trigger;

    this->dock_wind = new FGEDockWindows(this->project, this->trigger, ui->gridLayout, this);

    //QObject::connect(this->project->data_project->trigger, SIGNAL(__triger(void *)), this,  SLOT(triggerCreateNewGLW(void *)));
    //QObject::connect(this->project->data_project->trigger, SIGNAL(__trigerA(int, void *)), this,  SLOT(triggerSpliteWidget(int, void *)));
    QObject::connect(this->trigger, SIGNAL(__updateDock(void *)), this,  SLOT(triggerUpdateOpenGLEtterator(void *)));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_open_dae_file_triggered()
{
/*
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Collada Dae file"), "",
            tr("DAE (*.dae);;All Files (*)"));

    if (fileName.isEmpty())
            return;
    else {
        //QString fileName = "/home/corolo/Qt/FireGameEngine/Models/DAEFiles/ht/Catwalk Walk Forward HighKnees1.dae";
        QFileInfo fileInfo(fileName);
        if(fileInfo.isFile()){
            if(fileInfo.completeSuffix()=="dae"){
                /********project2 = new FGEProject();
                project2->setNamePoject("New Scene");
                project2->setLocationPoject("/home/corolo/");
                project2->createNewProject();
                project2->data_project->trigger = this->trigger;********/
/*
                FGEDataNode *node = NULL;
                FGECreateCubeModel *newCube = new FGECreateCubeModel();
                node = newCube->create(project2->data_project, 3.0, "000");

                FGEDataScene *data_scene = new FGEDataScene();
                data_scene->name = "scene 01";
                data_scene->color = glm::vec4(0.443, 0.443, 0.443, 1.0);
                data_scene->id   = 0;
                //scene->type = "scene";
                //scene->depth = 1.0;
                data_scene->projection->is_set = false;
                project2->data_project->current_scene   = data_scene;
                project2->data_project->first_scene     = data_scene;
                project2->data_project->last_scene      = data_scene;
                project2->data_project->screen_buffer.created_frame_buffer = false;



                if(data_scene->first_node==NULL){
                    qDebug()<<"nullll : " <<node->name;
                    data_scene->first_node = node;
                    data_scene->last_node = node;
                }else{
                    qDebug()<<"lassst : " <<node->name;
                    node->prev = data_scene->last_node;
                    data_scene->last_node->next = node;
                    data_scene->last_node = node;
                }
*/
/*

                {
                    FGECreateCubeModel *newCube = new FGECreateCubeModel();
                    node = newCube->create(project2->data_project, 0.0, "1111");


                    qDebug()<<"project2->data_project->current_scene : "<<project2->data_project->current_scene->name;

                    if(project2->data_project->current_scene->first_node==NULL){
                        qDebug()<<"addd ro null";
                        project2->data_project->current_scene->first_node = node;
                        project2->data_project->current_scene->last_node = node;
                    }else{
                        qDebug()<<"at last adddddd";
                        node->prev = project2->data_project->current_scene->last_node;
                        project2->data_project->current_scene->last_node->next = node;
                        project2->data_project->current_scene->last_node = node;
                    }

                }*/
/*
                FGEParseCollada *collada = new FGEParseCollada();
                //////qDebug() << "fffff"/home/corolo/Models/DAEFiles/ht/Catwalk Walk Forward HighKnees1.dae";
                collada->openCollada(fileName, project->data_project);

                calcNode(project->data_project->first_scene->first_node);
                if(project->data_project->first_animation!=NULL){
                    FGEDataAnimation * animation = project->data_project->first_animation;
                    while(animation!=NULL){
                        animation->prepare(0.0416666);
                        animation=animation->next;
                    }
                }

                this->dock_wind->update();
                //this->dock_wind->updateOpenGL();

                qDebug( "open Collada" );

                /***QMainWindow *main_window =  new QMainWindow(this);
                main_window->setObjectName(QString::fromUtf8("New Scene"));
                main_window->resize(600, 600);

                QWidget *central_widget = new QWidget(main_window);
                central_widget->setObjectName(QString::fromUtf8("centralwidget"));
                QGridLayout *grid_layout = new QGridLayout(central_widget);
                grid_layout->setObjectName(QString::fromUtf8("grid_layout"));

                main_window->setCentralWidget(central_widget);

                qDebug( "new_dock_wind" );

                new_dock_wind = new FGEDockWindows(project2->data_project, project2->data_project->trigger, grid_layout, this);

                qDebug( "main_window->show" );

                main_window->show();***/

                //new_dock_wind->initializeScene(collada->data_struct);


                /*           this->readObjects();





                    /*this->keyframe = new FGEDataAnimModdel();
                    if(this->collada->data_struct!=NULL){
                        this->keyframe->prepare(this->collada->data_struct->first_animation, 0.0416666);
                        ////
                    }*/

                //this->keyframe->printKeys();
    /*
                    timer = new QTimer();

                    this->animation_form = new FGEAnimationTimeLineForm(timer, this->collada->data_struct, this);
                    ui->ASplitter->addWidget(this->animation_form);

                    //ui->widget->setKeykrame();

                    this->animation_form->setPipeGLWidget(ui->widget);




                    timer->start(100/3);
                    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));


                    ui->ASplitter->setSizes({2000, 1000});
                    ui->AASplitter->setSizes({1000, 2000, 1000});

                }else{

                }*//*
            }
        }

    }*/

}

void MainWindow::calcNode(FGEDataNode *node){
    /*while(node!=NULL){
        if(node->parent!=NULL){
            if(node->parent->simple!=NULL){
                if(node->simple!=NULL){
                    node->simple->matrix = node->simple->matrix*node->parent->simple->matrix;
                }
            }
        }

        this->calcNode(node->first_child);
        node = node->next;
    }*/
}

void MainWindow::triggerUpdateOpenGLEtterator(void *dock)
{
    //qDebug() << "triggerUpdateOpenGLEtterator";
    FGEDockWindows *mdock = (FGEDockWindows*)dock;
    mdock->updateOpenGLEtterator(mdock->parent_tw);
}

void MainWindow::on_action_append_dae_file_triggered()
{
    /*QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Collada Dae file"), "",
                tr("DAE (*.dae);;All Files (*)"));

        if (fileName.isEmpty())
                return;
        else {
            QFileInfo fileInfo(fileName);
            if(fileInfo.isFile()){
                if(fileInfo.completeSuffix()=="dae"){
                    /*FGEDataNode *node = NULL;
                    FGECreateCubeModel *newCube = new FGECreateCubeModel();
                    node = newCube->create(project2->data_project, 0.0, "1111");


                    qDebug()<<"project2->data_project->current_scene : "<<project2->data_project->current_scene->name;

                    if(project2->data_project->current_scene->first_node==NULL){
                        qDebug()<<"addd ro null";
                        project2->data_project->current_scene->first_node = node;
                        project2->data_project->current_scene->last_node = node;
                    }else{
                        qDebug()<<"at last adddddd";
                        node->prev = project2->data_project->current_scene->last_node;
                        project2->data_project->current_scene->last_node->next = node;
                        project2->data_project->current_scene->last_node = node;
                    }*/

                    //new_dock_wind->reUpdateOpenGL();
/*
                    FGEParseCollada *collada = new FGEParseCollada();
                    //////qDebug() << "fffff"/home/corolo/Models/DAEFiles/ht/Catwalk Walk Forward HighKnees1.dae";
                    collada->appendCollada(fileName, project->data_project);

                    calcNode(project->data_project->first_scene->first_node);
                    if(project->data_project->first_animation!=NULL){
                        FGEDataAnimation * animation = project->data_project->first_animation;
                        while(animation!=NULL){
                            animation->prepare(0.0416666);
                            animation=animation->next;
                        }
                    }
                    this->dock_wind->update();
                }
            }
        }*/

}

void MainWindow::on_actionAdd_Terrain_triggered()
{

}
