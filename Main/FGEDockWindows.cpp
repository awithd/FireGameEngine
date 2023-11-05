#include "FGEDockWindows.h"

FGEDockWindows::FGEDockWindows(FGEProject *project, FGETriggerFunction *trigger, QGridLayout *gridLayout, QWidget *parent)
{
    this->parent = parent;
    this->data_project = project->data_project;
    this->create_new_object = new FGECreateNewObject();

    this->popup_menu = new FGEPopupMenu(this->data_project);
    QObject::connect(this->popup_menu, SIGNAL(emitUpdateGLViews()), this,  SLOT(triggerUpdateOpenGLEtterator()));
    QObject::connect(this->popup_menu, SIGNAL(createNewObject()), this,  SLOT(triggerUpdateOpenGLEtterator()));

    this->trigger = trigger;
    this->parent_tw = new FGETreeWidget();
    this->simpleViewport(this->parent_tw, gridLayout);
    /*
    //this->list_gl3dviewport = new FGEListGL3DViewportForms();
    QSplitter *splitter_a = new QSplitter();

    this->parent_tw = new FGETreeWidget();
    this->parent_tw->appendItem(NULL, 0, gridLayout, splitter_a, FGE_TYPE_WIDGET_NULL, NULL);

    QWidget *a_right = new QWidget();
    QWidget * a_left =  new QWidget();

    splitter_a->setOrientation(Qt::Horizontal);
    splitter_a->addWidget(a_left);
    splitter_a->addWidget(a_right);
    gridLayout->addWidget(splitter_a);
    splitter_a->setSizes(QList<int>({400,400}));
    gridLayout->setContentsMargins(0,0,0,0);



    FGETreeWidget *child_tw1 = new FGETreeWidget();
    //a_left->tree_widget_item = child_tw1;
    child_tw1->appendItem(a_left, 0, NULL, NULL, FGE_TYPE_WIDGET_WIDGET, this->parent_tw);


    FGETreeWidget *child_tw2 = new FGETreeWidget();
    //a_right->tree_widget_item = child_tw2;
    child_tw2->appendItem(a_right, 1, NULL, NULL, FGE_TYPE_WIDGET_PROJECT, this->parent_tw);




    ////////////////////////////////////////
    /// \brief materials_browser_form
    ///


    FGEOutlinerForm *outliner_form = new FGEOutlinerForm(this->data_project, this->trigger);
    outliner_form->init(this->trigger, this->data_project);
    FGETreeWidget *child_tw4 = new FGETreeWidget();
    child_tw4->appendItem(outliner_form, 1, NULL, NULL, FGE_TYPE_WIDGET_OUTLINER, child_tw1);

    _a_left = new FGEGL3DViewportForm(this->trigger, this->data_project, "A", this->create_new_object, this->popup_menu, (void*)this, parent);
    FGETreeWidget *child_tw3 = new FGETreeWidget();
    _a_left->tree_widget_item = child_tw3;
    child_tw3->appendItem(_a_left, 0, NULL, NULL, FGE_TYPE_WIDGET_3DVIEW, child_tw1);

    QSplitter *spl = new QSplitter();
    QGridLayout *lay = new QGridLayout();
    lay->setSpacing(0);
    //lay->setMargin(0);
    spl->setOrientation(Qt::Horizontal);
    spl->addWidget(outliner_form);
    spl->addWidget(_a_left);
    lay->addWidget(spl);
    spl->setSizes(QList<int>({200,400}));
    a_left->setLayout(lay);
*/

    /*{


        this->animation_form = new FGEAnimationTimeLineForm(timer, this->trigger, this->data_project, "A", (void*)this);

    }*/

    timer = new QTimer();

    /*FGEOutlinerForm *outliner_form2 = new FGEOutlinerForm(this->data_project, this->trigger);
    outliner_form2->init(this->trigger, this->data_project);
    FGETreeWidget *child_tw5 = new FGETreeWidget();
    child_tw5->appendItem(outliner_form2, 1, NULL, NULL, FGE_TYPE_WIDGET_OUTLINER, child_tw2);
*/
    //_b_left = new FGEUVEditorForm(this->trigger, this->data_project, "B", this->popup_menu, (void*)this, parent);
/*    this->animation_form = new FGEAnimationTimeLineForm(timer, this->trigger, this->data_project, "A", (void*)this);
    FGETreeWidget *child_tw6 = new FGETreeWidget();
    //this->animation_form->tree_widget_item = child_tw6;
    child_tw6->appendItem(this->animation_form, 0, NULL, NULL, FGE_TYPE_WIDGET_TIMELINE, child_tw2);

    QSplitter *bspl = new QSplitter();
    QGridLayout *blay = new QGridLayout();
    blay->setSpacing(0);
    //blay->setMargin(0);
    bspl->setOrientation(Qt::Horizontal);
    //bspl->addWidget(outliner_form2);
    bspl->addWidget(this->animation_form);
    blay->addWidget(bspl);
    bspl->setSizes(QList<int>({200,400}));
    a_right->setLayout(blay);

*/
    QObject::connect(this->trigger, SIGNAL(__addNewObject(void *)), this,  SLOT(_updateTreeWidgets(void *)));
    QObject::connect(this->trigger, SIGNAL(__updateUVEditor()), this,  SLOT(_updateUVEditWidgets()));


}


void FGEDockWindows::simpleViewport(FGETreeWidget *tree_parent, QGridLayout *gridLayout)
{
    QSplitter *splitter = new QSplitter();

    this->parent_tw->appendItem(NULL, 0, gridLayout, splitter, FGE_TYPE_WIDGET_NULL, NULL);

    QWidget *wid = new QWidget();

    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(wid);
    gridLayout->addWidget(splitter);
    splitter->setSizes(QList<int>({400,400}));
    gridLayout->setContentsMargins(0,0,0,0);


    FGEGL3DViewportForm *viewport_form = new FGEGL3DViewportForm(this->trigger, this->data_project, "A", this->create_new_object, this->popup_menu, (void*)this, parent);
    FGETreeWidget *tree_viewport = new FGETreeWidget();

    tree_viewport->appendItem(viewport_form, 0, NULL, NULL, FGE_TYPE_WIDGET_3DVIEW, tree_parent);
    viewport_form->tree_widget_item = tree_viewport;



    FGEConsoleForm *console_form = new FGEConsoleForm(this->data_project);
    //console_form->init(this->trigger, this->data_project);
    tree_viewport->appendItem(console_form, 1, NULL, NULL, FGE_TYPE_WIDGET_CONSOLE, tree_parent);



    QSplitter *spl = new QSplitter();
    QGridLayout *lay = new QGridLayout();
    lay->setSpacing(0);
    spl->setOrientation(Qt::Horizontal);
    spl->addWidget(console_form);
    spl->addWidget(viewport_form);
    lay->addWidget(spl);
    spl->setSizes(QList<int>({200,400}));

    wid->setLayout(lay);

}

/*void FGEDockWindows::simpleViewportWithConsole(FGETreeWidget *tree_parent, QGridLayout *gridLayout)
{
    QSplitter *splitter = new QSplitter();

    this->parent_tw->appendItem(NULL, 0, gridLayout, splitter, FGE_TYPE_WIDGET_NULL, NULL);

    QWidget *wid = new QWidget();

    splitter->setOrientation(Qt::Horizontal);
    splitter->addWidget(wid);
    gridLayout->addWidget(splitter);
    splitter->setSizes(QList<int>({400,400}));
    gridLayout->setContentsMargins(0,0,0,0);


    FGEGL3DViewportForm *viewport_form = new FGEGL3DViewportForm(this->trigger, this->data_project, "A", this->create_new_object, this->popup_menu, (void*)this, parent);
    FGETreeWidget *tree_viewport = new FGETreeWidget();

    tree_viewport->appendItem(viewport_form, 0, NULL, NULL, FGE_TYPE_WIDGET_3DVIEW, tree_parent);

    viewport_form->tree_widget_item = tree_viewport;

    QSplitter *spl = new QSplitter();
    QGridLayout *lay = new QGridLayout();
    lay->setSpacing(0);
    spl->setOrientation(Qt::Horizontal);
    spl->addWidget(outliner_form);
    spl->addWidget(viewport_form);
    lay->addWidget(spl);
    spl->setSizes(QList<int>({200,400}));

    wid->setLayout(lay);

}*/

void FGEDockWindows::update()
{
    updateTreeWidgets(this->parent_tw);
}


void FGEDockWindows::triggerUpdateOpenGLEtterator()
{
    updateOpenGLEtterator(this->parent_tw);
}

void FGEDockWindows::updateOpenGL()
{
    updateOpenGLEtterator(this->parent_tw);
}
void FGEDockWindows::reUpdateOpenGL()
{
    this->_a_left->updateInitOpenGL();
    updateOpenGLEtterator(this->parent_tw);
}

void FGEDockWindows::updateOpenGLEtterator(FGETreeWidget *tw)
{
    if(tw->type==FGE_TYPE_WIDGET_3DVIEW){

        FGEGL3DViewportForm *p = (FGEGL3DViewportForm *)tw->widget;
        p->updateInitOpenGL();
    }
    if(tw->child_left!=NULL) updateOpenGLEtterator(tw->child_left);
    if(tw->child_right!=NULL) updateOpenGLEtterator(tw->child_right);
}



void FGEDockWindows::updateTreeWidgets(FGETreeWidget *tw)
{

    if(tw->type==FGE_TYPE_WIDGET_3DVIEW){

        FGEGL3DViewportForm *p = (FGEGL3DViewportForm *)tw->widget;
        p->updateInitOpenGL();
    }else if(tw->type==FGE_TYPE_WIDGET_OUTLINER){

        FGEOutlinerForm *p = (FGEOutlinerForm *)tw->widget;
        p->updateTree();
    }else if(tw->type==FGE_TYPE_WIDGET_UVEDITOR){
        //FGEUVEditorForm *p = (FGEUVEditorForm *)tw->widget;
        //p->updateOpenGL();
    }

    if(tw->child_left!=NULL) this->updateTreeWidgets(tw->child_left);
    if(tw->child_right!=NULL) this->updateTreeWidgets(tw->child_right);
}


void FGEDockWindows::updateUVEditWidgets(FGETreeWidget *tw)
{

    if(tw->type==FGE_TYPE_WIDGET_UVEDITOR){
       // FGEUVEditorForm *p = (FGEUVEditorForm *)tw->widget;
        //p->updateOpenGL();
    }

    if(tw->child_left!=NULL) this->updateTreeWidgets(tw->child_left);
    if(tw->child_right!=NULL) this->updateTreeWidgets(tw->child_right);
}
void FGEDockWindows::_updateTreeWidgets(void *obj)
{
    updateTreeWidgets(this->parent_tw);
}

void FGEDockWindows::_updateUVEditWidgets()
{
    updateUVEditWidgets(this->parent_tw);
}
