#include "FGEOutlinerForm.h"
#include "ui_FGEOutlinerForm.h"
#include <QApplication>

FGEOutlinerForm::FGEOutlinerForm(FGEDataProject *struct_project, FGETriggerFunction *triger, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEOutlinerForm)
{
    ui->setupUi(this);
    this->struct_project = struct_project;
    this->triger = triger;
    //ui->treeobject->installEventFilter(this);
    ui->treeobject->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeobject, SIGNAL(customContextMenuRequested(QPoint)),
        this, SLOT(treeObjectCustomMenu(QPoint)));

    contextMenu = new QMenu(ui->treeobject);
    //ui->treeobject->setContextMenuPolicy(Qt::ActionsContextMenu);

    properties_action   = new QAction("Properties");
    select_action       = new QAction("Select");
    remove_action       = new QAction("Remove");
    duplicate_action    = new QAction("Duplicate");

    contextMenu->addAction(properties_action);
    contextMenu->addAction(select_action);
    contextMenu->addAction(remove_action);
    contextMenu->addAction(duplicate_action);

    //connect(uninstallAction, SIGNAL(triggered()), this, SLOT(uninstallAppletClickedSlot()));
    connect(select_action, SIGNAL(triggered()), this, SLOT(selectAppletClickedSlot()));
    connect(this->triger, SIGNAL(triggered()), this, SLOT(selectAppletClickedSlot()));


}

void FGEOutlinerForm::treeObjectCustomMenu(const QPoint & pos)
{
    //if(ui->treeobject->is)
    QModelIndex index = ui->treeobject->indexAt(pos);
    int itemRow = index.row();
    ///int itemCol = index.column();
    qDebug() << "itemRow " << itemRow;
    if(itemRow!=-1) {
        //ui->treeobject->sele
        ///QAction *selected = contextMenu->exec(mapToGlobal(pos));

    }

    /*QStandardItemModel * model = new QStandardItemModel;

    model->itemFromIndex(index);

    QStandardItem* itemAtPos = model->item(itemRow, itemCol);
    itemAtPos->setText("meh");

    if (selected) {
    }*/




    //Implement your menu here using myTreeView->itemAt(pos);
}

void FGEOutlinerForm::updateTree()
{
    this->init(this->triger, this->struct_project);
}

void FGEOutlinerForm::init(FGETriggerFunction *triger, FGEDataProject *struct_project /*, FGECreateNewObject *__create_new_object*/)
{

    //this->struct_project = struct_project;
    //this->triger = triger;
    //this->glwidget_world = _glww;

    //this->create_new_object = __create_new_object;

    //struct_project = sp;
    //QRect r = ui->treeobject->geometry();
    //ui->treeobject->setGeometry(r.x(), r.y(), 300, r.height());

    //QStandardItemModel* model = new QStandardItemModel();
    QStandardItemModel * model = new QStandardItemModel;
    //model->setColumnCount(1);
    //QTableView tableView;
    ui->treeobject->setModel(model);

    //model->setHorizontalHeaderItem( 0, new QStandardItem() );
    //model->setHorizontalHeaderItem( 1, new QStandardItem( "name" ) );
    //model->setHorizontalHeaderItem( 2, new QStandardItem( "type" ) );
    FGEStandardItem* mi;
    FGEDataScene *p =  this->struct_project->first_scene;

    while(p!=NULL){

        bool st = false;
        int j = 0;
        for(int i=0; i<model->rowCount(); i++){
            mi = (FGEStandardItem*) model->item(i, 0);
            if(mi->l_data == (void *)p) {
                st = true;
                i=model->rowCount();
            }
            j++;
        }

        if(j>0) j--;
qDebug() << "+++++++++++++++++++++++++++++kkkkkkk : "<<triger<<struct_project;
        FGEStandardItem* item;
        if(!st) {
            item = new FGEStandardItem();
            item->setText(p->name);
            item->setIcon(QIcon("/home/corolo/Qt/FireGameEngine/Icons/green-star.png"));
            item->l_data = (void *)p;
            item->type = 0;
            qDebug() << "0 item->l_data : "<<j<<"  -  "<<item->l_data;
            model->insertRow(j, item);

            FGEDataNode *_n=p->first_node;
            while(_n!=NULL){
                QString icon;
                if(_n->type=="Light"){
                    icon = "/home/corolo/Qt/FireGameEngine/Icons/sun.png";
                }else{
                    icon = "/home/corolo/Qt/FireGameEngine/Icons/green-star.png";
                }
                FGEStandardItem *child = new FGEStandardItem();
                child->setText(_n->name);
                child->setIcon(QIcon(icon));
                child->l_data = (void *)_n;
                child->type = 1;
                qDebug() << "1 item->l_data : "<<item<<"  -  "<<child->l_data;
                item->appendRow(child);

                _n=_n->next;
            }

        }else{

            item = mi;

            int k=0;
            FGEDataNode *_n=p->first_node;
            while(_n!=NULL){

                st = false;

                for(int i=0; i<item->rowCount(); i++){
                    mi = (FGEStandardItem*) item->child(i, 0);
                    if(mi->l_data == (void *)_n) st = true;
                    i=item->rowCount();
                    k++;
                }

                if(k>0) k--;

                if(!st) {
                    QString icon;
                    if(_n->type=="Light"){
                        icon = "/home/corolo/Qt/FireGameEngine/Icons/sun.png";
                    }else{
                        icon = "/home/corolo/Qt/FireGameEngine/Icons/green-star.png";
                    }
                    FGEStandardItem *child = new FGEStandardItem();
                    child->setText(_n->name);
                    child->setIcon(QIcon(icon));
                    child->l_data = (void *)_n;
                    child->type = 1;
                    qDebug() << "3 item->l_data : "<<child->l_data;
                    item->insertRow(k, child);
                }

                _n=_n->next;
            }
        }

        p=p->next;
    }

}

void FGEOutlinerForm::uninstallAppletClickedSlot()
{

}

void FGEOutlinerForm::contextMenuEvent(QContextMenuEvent *event)
  {
      QMenu menu(this);
      menu.addAction(new QAction("Properties",this));
      menu.exec(event->globalPos());
  }
void FGEOutlinerForm::selectAppletClickedSlot()
{
    qDebug() << "++++++ddddddddddddddddddddddddddddd ------" << ui->treeobject->currentIndex().row();

}
FGEOutlinerForm::~FGEOutlinerForm()
{
    delete ui;
}
/*void FGEOutlinerForm::on_buttonaddnewobject_clicked()
{
    FGEDialogListObjects *dialog_list_object = new FGEDialogListObjects();

    dialog_list_object->init(this->triger, this->struct_project/*, this->create_new_object*///);

    /*const QRect screen = QApplication::desktop()->screenGeometry();
    dialog_list_object->move( screen.center() - dialog_list_object->rect().center() );

    dialog_list_object->show();
}*/
/*
void FGEOutlinerForm::on_splitterHA_splitterMoved(int pos, int index)
{
    qDebug() << "pos " << pos;
    qDebug() << "width " << ui->splitterHA->width();

}

bool FGEOutlinerForm::etterator_uiedr(FGENodeOS *_node, QTreeWidgetItem *item)
{
    FGENodeOS *n = _node;
    while(n!=NULL){
        if(n->tree_widget_item==item){
            struct_project->node_current = n;

            FGEEditObject *eo = new FGEEditObject();
            eo->init(n, ui->glwidget_world_area_01);
            eo->show();
            item->setSelected(true);
            return true;
        }else{
            if(n->child!=NULL){
                if(etterator_uiedr(n->child, item)) return true;
            }
        }
        n = n->next;
    }
    return false;
}*/
/*
void FGEOutlinerForm::on_treeobject_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(2)=="Geometry" || item->text(2)=="Light"){
        FGENodeOS *n = struct_project->scene_current->node;
        qDebug() << "DoubleClicked";
        while(n!=NULL){
            qDebug() <<"bj name "  << n->name;
            n = n->next;
        }
        n = struct_project->scene_current->node;
        while(n!=NULL){qDebug() << "DoubleClicked name "  << n->name;
            if(n->tree_widget_item==item){qDebug() << "yes name "  << n->name;
                struct_project->node_current = n;
                FGEEditObject *eo = new FGEEditObject();
                eo->init(n, ui->glwidget_world_area_01);
                eo->show();
                item->setSelected(true);
                return;
            }else{qDebug() << "no name "  << n->name;
                if(n->child!=NULL){
                    if(etterator_uiedr(n->child, item)) return;
                }
            }
            n = n->next;
        }
    }
}*/
// SELECT THE OBJECT OF SCENE IN TREEWIDGET
/*void FGEOutlinerForm::on_treeobject_itemClicked(QTreeWidgetItem *item, int column)
{

    if(item->text(2)=="scene"){
        /*FGESceneOS *p = struct_project->scene_first;

        while(p!=NULL){
            if(p->tree_widget_item==item){
                struct_project->scene_current = p;
                struct_project->node_current = NULL;
                item->setSelected(true);
                this->glwidget_world->slotUpdateGL();
                p = NULL;
            }else{
                p = p->next;
            }

        }*//*
    }else if(item->text(2)=="Geometry" || item->text(2)=="Light" ){
        FGESceneOS *p = struct_project->scene_first;
        //item->da
        QVariant v = item->data(column, Qt::UserRole);
        FGENodeOS *node = (FGENodeOS *) v.to;
        struct_project->node_current = node;
        struct_project->selected_nodes->clair();
        struct_project->selected_nodes->append(node);
        /*while(p!=NULL){
            FGENodeOS *n = p->node;
            while(n!=NULL){
                if(n->tree_widget_item==item){
                    struct_project->node_current = n;
                    item->setSelected(true);
                    this->glwidget_world->slotUpdateGL();
                    return;
                }else{
                    if(n->child!=NULL){
                        if(etterator_uhfyyd(n->child, item)) return;
                    }
                }
                n = n->next;
            }
            p = p->next;
        }*//*
    }
}*/
/*bool FGEOutlinerForm::etterator_uhfyyd(FGENodeOS *_node, QTreeWidgetItem *item)
{
    FGENodeOS *n = _node;
    while(n!=NULL){
        if(n->tree_widget_item==item){
            struct_project->node_current = n;
            item->setSelected(true);
            this->glwidget_world->slotUpdateGL();
            return true;
        }else{
            if(n->child!=NULL){
                if(etterator_uhfyyd(n->child, item)) return true;
            }
        }
        n = n->next;
    }
    return false;
}*/
/*
void FGEOutlinerForm::on_buttonaddnewscene_clicked()
{

    FGESceneOS * p = struct_project->scene_first;
    unsigned int c=0;
    while(p!=NULL){
        c++;
        p = p->next;
    }

    FGESceneOS *newscense =  new FGESceneOS;

    newscense->name = "scene "+QString::number(c);

    newscense->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
    newscense->id   = c;
    newscense->type = "scene";
    newscense->depth = 1.0;
    newscense->node = NULL;
    newscense->next = NULL;
    newscense->prev = NULL;
    newscense->projection->is_set = false;

    if(struct_project->scene_last==NULL){
        struct_project->scene_last = newscense;
        struct_project->scene_first = newscense;
    }else{
        struct_project->scene_last->next = newscense;
        newscense->prev = struct_project->scene_last;
        struct_project->scene_last = newscense;
    }
    struct_project->scene_current = newscense;
    struct_project->node_current = NULL;

    ui->glwidget_world_area_01->slotUpdateGL();

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeobject);
    treeItem->setText(0, QString::number(newscense->id));
    treeItem->setText(1, newscense->name);
    treeItem->setText(2, newscense->type);
    newscense->tree_widget_item = treeItem;

}
*/


/*
void FGEOutlinerForm::on_buttonaddnewnode_clicked()
{
    QTreeWidgetItem *sel_item = ui->treeobject->selectedItems()[0];

    FGENodeOS *newnode =  new FGENodeOS;
    newnode->child = NULL;
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->name = "empty";
    newnode->type = "Geometry";
    newnode->id = 2;
    newnode->object = NULL;
    newnode->scene = struct_project->scene_current;
    newnode->is_set = false;

    FGESceneOS *s = struct_project->scene_current;
    if(s->tree_widget_item==sel_item){
        newnode->parent = NULL;
        FGENodeOS *p = s->node, *op=NULL;
        while(p!=NULL){
            op = p;
            p = p->next;
        }
        if(op==NULL){
            s->node = newnode;
        }else{
            op->next = newnode;
            newnode->prev = op;
        }

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, QString::number(2));
        child->setText(1, newnode->name);
        child->setText(2, newnode->type);
        sel_item->addChild(child);
        child->setSelected(true);
        newnode->tree_widget_item = child;

        newnode->transform = new FGETransform(NULL, NULL);


    }else{

        FGENodeOS *p = struct_project->scene_current->node;
        while(p!=NULL){
            if(p->tree_widget_item==sel_item){
                newnode->parent = p;
                newnode->transform = new FGETransform(p->transform, NULL);

                FGENodeOS *y = p->child, *op=NULL;
                while(y!=NULL){
                    op = y;
                    y = y->next;
                }
                if(op==NULL){
                    p->child = newnode;
                }else{
                    op->next = newnode;
                    newnode->prev = op;
                }

                QTreeWidgetItem *child = new QTreeWidgetItem();
                child->setText(0, QString::number(2));
                child->setText(1, newnode->name);
                child->setText(2, newnode->type);
                sel_item->addChild(child);
                child->setSelected(true);
                newnode->tree_widget_item = child;

            }else{
                if(p->child!=NULL){
                    if(etterator_gttrds(sel_item, newnode, p->child)) return;
                }
            }
            p = p->next;
        }
    }
}
*//*
bool FGEOutlinerForm::etterator_gttrds(QTreeWidgetItem *_sel_item, FGENodeOS *_newnode, FGENodeOS *node)
{
    while(node!=NULL){
        if(node->tree_widget_item==_sel_item ){
            _newnode->parent = node;
            _newnode->transform = new FGETransform(node->transform, NULL);

            FGENodeOS *y = node->child, *op=NULL;
            while(y!=NULL){
                op = y;
                y = y->next;
            }
            if(op==NULL){
                node->child = _newnode;
            }else{
                op->next = _newnode;
                _newnode->prev = op;
            }

            QTreeWidgetItem *child = new QTreeWidgetItem();
            child->setText(0, QString::number(2));
            child->setText(1, _newnode->name);
            child->setText(2, _newnode->type);
            _sel_item->addChild(child);
            child->setSelected(true);
            _newnode->tree_widget_item = child;

            return true;
        }else{
            if(node->child!=NULL){
                if(etterator_gttrds(_sel_item, _newnode, node->child )) return true;
            }
        }
        node = node->next;
    }
    return false;
}*/

/*



void FGEOutlinerForm::on_import_obj_pushButton_clicked()
{

    QList<QUrl> urls;
    urls << QUrl::fromLocalFile("/home")
         << QUrl::fromLocalFile(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).first());

    QFileDialog dialog;
    dialog.setSidebarUrls(urls);
    dialog.setFileMode(QFileDialog::AnyFile);
    QDir directory;
    if(dialog.exec()) {
        QString fileName = dialog.selectedFiles().first();

        FGEImportObjectForm *import_object_form = new FGEImportObjectForm();
        //import_object_form->init(filesList);

        qDebug() << "QFileDialog " << fileName;
        import_object_form->show();
        import_object_form->beginImporting(fileName);




    }
}

void FGEOutlinerForm::on_pushButton_light_clicked()
{
    new_light_tool_form->init();
    new_light_tool_form->show();
}

void FGEOutlinerForm::addNewLight()
{
    QTreeWidgetItem *sel_item = ui->treeobject->selectedItems()[0];

    FGENodeOS *newnode =  new FGENodeOS;
    newnode->child = NULL;
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->name = new_light_tool_form->getName();
    newnode->type = "Light";
    newnode->id = 3;
    newnode->object = NULL;
    newnode->scene = struct_project->scene_current;
    newnode->is_set = false;



    newnode->color_selection[0] = 1.0;
    newnode->color_selection[1] = 0.1;
    newnode->color_selection[2] = 0.0;

    FGESceneOS *s = struct_project->scene_current;
    if(s->tree_widget_item==sel_item){
        newnode->parent = NULL;
        newnode->transform = new FGETransform(NULL, NULL);

        FGENodeOS *p = s->node, *op=NULL;
        while(p!=NULL){
            op = p;
            p = p->next;
        }
        if(op==NULL){
            s->node = newnode;
        }else{
            op->next = newnode;
            newnode->prev = op;
        }

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, QString::number(2));
        child->setText(1, newnode->name);
        child->setText(2, newnode->type);
        sel_item->addChild(child);
        child->setSelected(true);
        newnode->tree_widget_item = child;

    }else{

        FGENodeOS *p = struct_project->scene_current->node;
        while(p!=NULL){
            if(p->tree_widget_item==sel_item){
                newnode->parent = p;
                newnode->transform = new FGETransform(p->transform, NULL);

                FGENodeOS *y = p->child, *op=NULL;
                while(y!=NULL){
                    op = y;
                    y = y->next;
                }
                if(op==NULL){
                    p->child = newnode;
                }else{
                    op->next = newnode;
                    newnode->prev = op;
                }

                QTreeWidgetItem *child = new QTreeWidgetItem();
                child->setText(0, QString::number(2));
                child->setText(1, newnode->name);
                child->setText(2, newnode->type);
                sel_item->addChild(child);
                child->setSelected(true);
                newnode->tree_widget_item = child;

            }else{
                if(p->child!=NULL){
                    if(etterator_gttrds(sel_item, newnode, p->child)) return;
                }
            }
            p = p->next;
        }
    }
}

*/
/*
void FGEOutlinerForm::on_buttonaddnewobject_clicked()
{
    QTreeWidgetItem *sel_item = ui->treeobject->selectedItems()[0];

    FGENodeOS *newnode =  new FGENodeOS;
    newnode->child = NULL;
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->name = "empty";
    newnode->type = "Geometry";
    newnode->id = 2;
    newnode->object = NULL;
    newnode->scene = struct_project->scene_current;
    newnode->is_set = false;

    FGESceneOS *s = struct_project->scene_current;
    if(s->tree_widget_item==sel_item){
        newnode->parent = NULL;
        FGENodeOS *p = s->node, *op=NULL;
        while(p!=NULL){
            op = p;
            p = p->next;
        }
        if(op==NULL){
            s->node = newnode;
        }else{
            op->next = newnode;
            newnode->prev = op;
        }

        QTreeWidgetItem *child = new QTreeWidgetItem();
        child->setText(0, QString::number(2));
        child->setText(1, newnode->name);
        child->setText(2, newnode->type);
        sel_item->addChild(child);
        child->setSelected(true);
        newnode->tree_widget_item = child;

        newnode->transform = new FGETransform(NULL, NULL);

    }else{

        FGENodeOS *p = struct_project->scene_current->node;
        while(p!=NULL){
            if(p->tree_widget_item==sel_item){
                newnode->parent = p;
                newnode->transform = new FGETransform(p->transform, NULL);

                FGENodeOS *y = p->child, *op=NULL;
                while(y!=NULL){
                    op = y;
                    y = y->next;
                }
                if(op==NULL){
                    p->child = newnode;
                }else{
                    op->next = newnode;
                    newnode->prev = op;
                }

                QTreeWidgetItem *child = new QTreeWidgetItem();
                child->setText(0, QString::number(2));
                child->setText(1, newnode->name);
                child->setText(2, newnode->type);
                sel_item->addChild(child);
                child->setSelected(true);
                newnode->tree_widget_item = child;

            }else{
                if(p->child!=NULL){
                    if(etterator_gttrds(sel_item, newnode, p->child)) return;
                }
            }
            p = p->next;
        }
    }
}
*/

void FGEOutlinerForm::on_treeobject_clicked(const QModelIndex &index)
{
    QStandardItemModel *sModel = (QStandardItemModel *)(index.model());
    FGEStandardItem *item = (FGEStandardItem*)sModel->itemFromIndex(index);
    if(item->type==0){
        qDebug() << "treeobject_ type==0";
        FGEDataScene *scene = (FGEDataScene *)item->l_data;
        qDebug() << "treeobject_clicked : "<<scene->name;
    }else if(item->type==1){
        qDebug() << "treeobject_ type==1";
        FGEDataNode *node = (FGEDataNode *)item->l_data;
        qDebug() << "treeobject_clicked : "<<node->name;
        /*FGEDataSelectedNodesStage* sns = this->struct_project->selected_nodes->getCurrentStageNode();
        sns->clair();
        sns->append(node);
        sns->updateTransform();*/
        this->triger->updateScene();
    }

}








void FGEOutlinerForm::on_pushButton_light_2_clicked()
{

}

