#include "FGEObjectModeling.h"

FGEObjectModeling::FGEObjectModeling(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent)
{
qDebug()<<"hhhhhh : ";
    this->data_project = data_project;
    this->trigger = trigger;
    this->glwidget_world = glwidget_world;

    this->name_parent = name_parent;
    this->old_sel = 0;

    QGridLayout *_gridLayout = new QGridLayout(parent);
    _gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    vvvvvvvvv = new QWidget(parent);
    vvvvvvvvv->setObjectName(QString::fromUtf8("vvvvvvvvv"));
    vvvvvvvvv->setGeometry(QRect(10, 20, 441, 381));
    gridLayout_2 = new QGridLayout(vvvvvvvvv);
    gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
    /*pushButton_make_skin = new QPushButton(vvvvvvvvv);
    pushButton_make_skin->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_make_skin->setMinimumSize(QSize(60, 30));
    pushButton_make_skin->setMaximumSize(QSize(60, 30));*/

    //gridLayout_2->addWidget(pushButton_make_skin, 0, 0, 1, 1);
    {
        groupBox_ = new QGroupBox(vvvvvvvvv);
        groupBox_->setObjectName(QString::fromUtf8("groupBox"));
        groupBox_->setGeometry(QRect(10, 40, 471, 111));
        gridLayout_ = new QGridLayout(groupBox_);
        gridLayout_->setObjectName(QString::fromUtf8("gridLayout"));
        label__ = new QLabel(groupBox_);
        label__->setObjectName(QString::fromUtf8("label"));
        label__->setMinimumSize(QSize(170, 0));
        label__->setMaximumSize(QSize(170, 16777215));

        gridLayout_->addWidget(label__, 0, 0, 1, 1);

        comboBox_method_skinning = new QComboBox(groupBox_);
        comboBox_method_skinning->addItem(QString());
        comboBox_method_skinning->addItem(QString());
        comboBox_method_skinning->setObjectName(QString::fromUtf8("comboBox_method_skinning"));

        gridLayout_->addWidget(comboBox_method_skinning, 0, 1, 1, 2);

        label_ = new QLabel(groupBox_);
        label_->setObjectName(QString::fromUtf8("label_2"));
        label_->setMinimumSize(QSize(170, 0));
        label_->setMaximumSize(QSize(170, 16777215));

        gridLayout_->addWidget(label_, 1, 0, 1, 1);

        pushButton_make_skin = new QPushButton(groupBox_);
        pushButton_make_skin->setObjectName(QString::fromUtf8("pushButton_apply_skinning"));
        pushButton_make_skin->setMinimumSize(QSize(71, 0));
        pushButton_make_skin->setMaximumSize(QSize(71, 16777215));

        gridLayout_->addWidget(pushButton_make_skin, 1, 1, 1, 1);

        horizontalSpacer_ = new QSpacerItem(189, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_->addItem(horizontalSpacer_, 1, 2, 1, 1);
    }

    gridLayout_2->addWidget(groupBox_, 0, 0, 1, 1);
qDebug()<<"jjjjjj : ";
    splitter = new QSplitter(vvvvvvvvv);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    listWidget_meshes_armatures = new QListWidget(splitter);
    listWidget_meshes_armatures->setObjectName(QString::fromUtf8("listWidget"));
    splitter->addWidget(listWidget_meshes_armatures);
    groupBox = new QGroupBox(splitter);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid ;\n"
"	border-color: rgb(156, 156, 156);\n"
"    margin-top: 10px;\n"
"    font-size: 14px;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	top:0px;\n"
"	left : 15px;\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 0px 2px;\n"
"}"));


    gridLayout = new QGridLayout(groupBox);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    pushButton = new QPushButton(groupBox);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));


    gridLayout->addWidget(pushButton, 3, 1, 1, 1);

    verticalSpacer = new QSpacerItem(20, 177, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    horizontalLayout_2->addWidget(label_2);

    checkBox = new QCheckBox(groupBox);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setMinimumSize(QSize(30, 30));
    checkBox->setMaximumSize(QSize(30, 30));

    horizontalLayout_2->addWidget(checkBox);
qDebug()<<"llllll : ";

    gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));

    horizontalLayout->addWidget(label);

    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setMinimumSize(QSize(30, 30));
    label_3->setMaximumSize(QSize(30, 30));

    horizontalLayout->addWidget(label_3);


    gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

    splitter->addWidget(groupBox);

    gridLayout_2->addWidget(splitter, 1, 0, 1, 1);

qDebug()<<"vvvvvvv : ";
    /*groupBox->setEnabled(false);
    _gridLayout->addWidget(vvvvvvvvv, 0, 0, 1, 1);
    this->retranslateUi();
    QObject::connect(this->pushButton_make_skin, SIGNAL(clicked(bool)), this,  SLOT(linkArmaturesMeshs(bool)));
    QObject::connect(this->checkBox, SIGNAL(clicked(bool)), this,  SLOT(copyNode(bool)));

    QObject::connect(this->listWidget_meshes_armatures, SIGNAL(itemClicked(QListWidgetItem*)), this,  SLOT(selectItem(QListWidgetItem*)));
*/
}
void FGEObjectModeling::link(QString name_parent, FGEDataProject *data_project, FGETriggerFunction *trigger, QWidget *menu, QWidget *body){
    if(menu==NULL || body==NULL) return;

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;


    //QLayout *layout = header->layout();
    //layout->deleteLater();

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);
    gridLayout->setSpacing(4);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    body->setLayout(gridLayout);


    //qDebug() << "+++++++object layout+++++++;";
    /**/

    //layout = menu->layout();
    //layout->deleteLater();

    QGridLayout *hbox_layout_menu     = new QGridLayout();
    menu_bar->show();
    hbox_layout_menu->addWidget(menu_bar, 0, 0, 1, 1);
    hbox_layout_menu->setSpacing(4);
    hbox_layout_menu->setObjectName(QStringLiteral("gridLayout"));
    hbox_layout_menu->setContentsMargins(0, 0, 0, 0);
    menu->setLayout(hbox_layout_menu);
}

void FGEObjectModeling::prepare()
{

    if(this->data_project->selected_nodes->selected_nodes.size()==0){
        copy_nodes.clear();
        this->listWidget_meshes_armatures->clear();
        checkBox->setChecked(false);
        label->setText("");
        groupBox->setEnabled(false);
        return;
    }

    if(this->old_sel!=this->data_project->selected_nodes->selection_counter){
        this->old_sel = this->data_project->selected_nodes->selection_counter;
        copy_nodes.clear();
        this->listWidget_meshes_armatures->clear();
        checkBox->setChecked(false);
        label->setText("");
        groupBox->setEnabled(false);

        for(int i=0; i<this->data_project->selected_nodes->selected_nodes.size(); i++){
            FGEDataNode * node = this->data_project->selected_nodes->selected_nodes.at(i);

            if(node!=NULL){
                qDebug() << "+++++++add 0+++++++;";
                QListWidgetItem *item = new QListWidgetItem(node->name);
                QIcon node_icon;
                if(node->node_type==FGE_NODE_TYPE_CAMERA){
                    node_icon.addFile(QStringLiteral(":/Icons/svg/camera_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                }else if(node->node_type==FGE_NODE_TYPE_ARMATURE){
                    node_icon.addFile(QStringLiteral(":/Icons/svg/armature_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                }else if(node->node_type==FGE_NODE_TYPE_MESH){
                    node_icon.addFile(QStringLiteral(":/Icons/svg/mesh_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                }else if(node->node_type==FGE_NODE_TYPE_SKIN){
                    node_icon.addFile(QStringLiteral(":/Icons/svg/armature_skined.svg"), QSize(), QIcon::Normal, QIcon::Off);
                }
                item->setIcon(node_icon);
                this->listWidget_meshes_armatures->addItem(item);

                //this->listWidget_meshes_armatures->addItem(this);
                /*QWidget *widget = new QWidget(this->listWidget_meshes_armatures);
                {
                    widget->setObjectName(QString::fromUtf8("widget_item_selected"));
                    widget->setMinimumSize(QSize(300, 30));
                    widget->setMaximumSize(QSize(16777215, 30));


                    QGridLayout *gridLayout = new QGridLayout(widget);
                    gridLayout->setSpacing(0);
                    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
                    gridLayout->setContentsMargins(0, 0, 0, 0);
                    QHBoxLayout *_horizontalLayout = new QHBoxLayout();
                    _horizontalLayout->setSpacing(12);
                    _horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
                    _horizontalLayout->setContentsMargins(-1, 0, -1, -1);

                    QIcon node_icon;
                    if(node->node_type==FGE_NODE_TYPE_CAMERA){
                        node_icon.addFile(QStringLiteral(":/Icons/svg/camera_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                    }else if(node->node_type==FGE_NODE_TYPE_ARMATURE){
                        node_icon.addFile(QStringLiteral(":/Icons/svg/armature_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                    }else if(node->node_type==FGE_NODE_TYPE_MESH){
                        node_icon.addFile(QStringLiteral(":/Icons/svg/mesh_object.svg"), QSize(), QIcon::Normal, QIcon::Off);
                    }else if(node->node_type==FGE_NODE_TYPE_SKIN){
                        node_icon.addFile(QStringLiteral(":/Icons/svg/armature_skined.svg"), QSize(), QIcon::Normal, QIcon::Off);
                    }

                    QLabel *lni = new QLabel(widget);
                    lni->setPixmap(node_icon.pixmap(28,28));
                    lni->setMinimumSize(QSize(28, 28));
                    lni->setMaximumSize(QSize(28, 28));
                    lni->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

                    _horizontalLayout->addWidget(lni);


                    QLabel *label_name = new QLabel(widget);
                    label_name->setObjectName(QString::fromUtf8("label_name"));
                    label_name->setMinimumSize(QSize(0, 28));
                    label_name->setMaximumSize(QSize(16777215, 28));

                    _horizontalLayout->addWidget(label_name);


                    gridLayout->addLayout(_horizontalLayout, 0, 0, 1, 1);
                    label_name->setText(node->name);

                }*/
                //item->setSizeHint(QSize(widget->width()-10, 40));
                QVariant pp = QVariant::fromValue<void*>(node);
                item->setData(Qt::UserRole, pp);

                //this->listWidget_meshes_armatures->addItem(item);
                //this->listWidget_meshes_armatures->setItemWidget(item, widget);
            //if(node->node_type == FGE_NODE_TYPE_MESH){
                 /*for(int j=0; j<node->simples.size();j++){

                    FGEInstanceSimple *ins_smp = node->simples.at(j);
                    FGEDataSimple* simple = ins_smp->simple;

                    if(simple->controller_skin==NULL){
                        if(simple->mesh!=NULL){
                            this->listWidget_meshes_armatures->addItem(node->name);
                        }
                    }
                }*/
            }
            /*if(node->node_type==FGE_NODE_TYPE_MESH){
            }else if(node->node_type==FGE_NODE_TYPE_ARMATURE){
                this->listWidget_2->addItem(node->name);
            }*/
        }
    }

}
void FGEObjectModeling::copyNode(bool click)
{
    QListWidgetItem * item = this->listWidget_meshes_armatures->currentItem();
    groupBox->setEnabled(true);
    QVariant v = item->data(Qt::UserRole);
    FGEDataNode *node = (FGEDataNode*) v.value<void *>();
    label->setText(node->name);
    if(!click){
        for(int i=0;i<copy_nodes.size(); i++){
            if(copy_nodes.at(i)==node){
                copy_nodes.remove(i);
                return;
            }
        }
    }else{
        for(int i=0;i<copy_nodes.size(); i++){
            if(copy_nodes.at(i)==node){
                return;
            }
        }
        copy_nodes.push_back(node);
    }
}
void FGEObjectModeling::selectItem(QListWidgetItem* click)
{
    groupBox->setEnabled(true);
    QVariant v = click->data(Qt::UserRole);
    FGEDataNode *node = (FGEDataNode*) v.value<void *>();
    label->setText(node->name);
    for(int i=0;i<copy_nodes.size(); i++){
        if(copy_nodes.at(i)==node){
            copy_nodes.at(i);
            checkBox->setChecked(true);
            return;
        }
    }
    checkBox->setChecked(false);
}
void FGEObjectModeling::linkArmaturesMeshs(bool st)
{

    QVector<FGEDataArmature*> armatures;
    for(int k=0; k<this->data_project->selected_nodes->selected_nodes.size(); k++){
        FGEDataNode * _node = this->data_project->selected_nodes->selected_nodes.at(k);
        if(_node!=NULL){
            if(_node->node_type==FGE_NODE_TYPE_ARMATURE){
                if(_node->armature!=NULL){

                    _node->private_visible = false;
                    armatures.push_back(_node->armature);
                }
            }
        }
    }

    for(int i=0; i<this->data_project->selected_nodes->selected_nodes.size(); i++){
        FGEDataNode * node = this->data_project->selected_nodes->selected_nodes.at(i);
        if(node!=NULL){
            if(node->node_type==FGE_NODE_TYPE_MESH){
                for(int j=0; j<armatures.size();j++){

                    FGEDataArmature *armature = armatures.at(j);
                    node->mesh->shader_item->clear();
                    node->mesh->shader_item->joints_size = armature->size_bones;

                    FGEDataSkin* cs = new FGEDataSkin("new skin", node->mesh, armature);
                    node->controller_skins.push_back(cs);
                    node->node_type=FGE_NODE_TYPE_SKIN;

                    this->data_project->appendNewSkin(cs);
                    int idx = comboBox_method_skinning->currentIndex();
                    if(idx==0){

                    }else if(idx==1){

                        FGEDataVectorf3 *position_data = (FGEDataVectorf3*)node->mesh->resources->position->data;

                        QVector<void*> lb;
                        cs->armature->getListBones(lb);
                        for(int _i=0; _i<lb.size(); _i++){
                            FGEDataBone* bn = (FGEDataBone*)lb.at(_i);
                            bn->trans_pose->inv_bind_matrix = glm::inverse(bn->trans_pose->getGlobalTransformation());
                            cs->influance->addNewItem(bn);
                        }
qDebug() <<" cs->influance->size : "<<cs->influance->size;
                        for(int _i=0; _i<position_data->vector.size(); _i++){
                            //fge_f3 pos = position_data->vector.at(_i);
                            //glm::mat4 _m = node->transform->getGlobalTransformation();
                            //glm::vec4 _pos = _m*glm::vec4(pos.x, pos.y, pos.z, 1);

                            for(int _j=0; _j<cs->influance->size; _j++){

                                FGEDataBoneInfluanceItem* item = cs->influance->items.at(_j);
                                FGEDataVectorf1 *weight = (FGEDataVectorf1*)item->weight->data;
                                weight->vector.push_back(0.0);
                            }
                        }

                        for(int _j=0; _j<cs->influance->size; _j++){

                            FGEDataBoneInfluanceItem* item = cs->influance->items.at(_j);
                            FGEDataVectorf1 *weight = (FGEDataVectorf1*)item->weight->data;
                            qDebug()<<"weight : ";
                            qDebug()<<weight->vector;

                        }

                    }

                    //FGEDataVectorAddress *vec_adr = (FGEDataVectorAddress*)cs->joint->data;




                    //FGEDataVectormat4 *vec_invm = (FGEDataVectormat4*)controller_skin->inv_bind_mtrix->data;

                    /*QStringList m =  name_array.text().split(" ");
                    ////qDebug() <<" JOINTS : " << source << " ; s ;"<<m.size();
                    if(stride==1){
                        for(unsigned int i =0;i<m.size(); i++){

                            qDebug() <<" m.at(i) : "<<m.at(i);
                            FGEDataBone* dbs= cs->armature->getBoneOf(m.at(i));
                            qDebug() <<" dbs : "<<dbs->name;
                            vec_adr->vector.push_back((void*)dbs);
                        }
                    }*/

                }
            }
        }
    }

}
