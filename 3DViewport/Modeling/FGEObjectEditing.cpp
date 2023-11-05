#include "FGEObjectEditing.h"

FGEObjectEditing::FGEObjectEditing(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent) :
    QWidget(parent)
{


    /*if (FGEObjectInteractionForm->objectName().isEmpty())
        FGEObjectInteractionForm->setObjectName(QStringLiteral("FGEObjectInteractionForm"));
    FGEObjectInteractionForm->resize(526, 282);*/

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;
    qDebug()<<"nbbbb: ";

    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setSpacing(4);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);

    widget_header = new QWidget();
    widget_header->setObjectName(QStringLiteral("widget_header"));
    widget_header->setGeometry(QRect(0, 0, 91, 31));
    widget_header->setStyleSheet(QLatin1String(".QPushButton{\n"
"	border : 0px solid;\n"
"	background-color: rgb(40, 120, 240);\n"
"}\n"
".QPushButton::hover{\n"
"	background-color: rgb(133, 28, 147);\n"
"}"));

    gridLayout_2 = new QGridLayout(widget_header);
    gridLayout_2->setSpacing(0);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout_2->setContentsMargins(0, 0, 0, 0);



    {
        pushButton_vertex_edmd = new QPushButton(widget_header);
        pushButton_vertex_edmd->setObjectName(QStringLiteral("pushButton_edit_mode_points"));
        pushButton_vertex_edmd->setMinimumSize(QSize(30, 30));
        pushButton_vertex_edmd->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/svg/edit_mode_points.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_vertex_edmd->setIcon(icon1);
        pushButton_vertex_edmd->setIconSize(QSize(26, 26));
        gridLayout_2->addWidget(pushButton_vertex_edmd, 0, 0, 1, 1);
    }
    {
        pushButton_edge_edmd = new QPushButton(widget_header);
        pushButton_edge_edmd->setObjectName(QStringLiteral("pushButton_edit_mode_lines"));
        pushButton_edge_edmd->setMinimumSize(QSize(30, 30));
        pushButton_edge_edmd->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/svg/edit_mode_lines.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_edge_edmd->setIcon(icon);
        pushButton_edge_edmd->setIconSize(QSize(26, 26));
        gridLayout_2->addWidget(pushButton_edge_edmd, 0, 1, 1, 1);
    }
    {
        pushButton_face_edmd = new QPushButton(widget_header);
        pushButton_face_edmd->setObjectName(QStringLiteral("pushButton_edit_mode_faces"));
        pushButton_face_edmd->setMinimumSize(QSize(30, 30));
        pushButton_face_edmd->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/svg/edit_mode_faces.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_face_edmd->setIcon(icon2);
        pushButton_face_edmd->setIconSize(QSize(26, 26));
        gridLayout_2->addWidget(pushButton_face_edmd, 0, 2, 1, 1);
    }

    gridLayout->addWidget(widget_header, 0, 0, 1, 1);
    horizontalSpacer = new QSpacerItem(268, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);



    /*QGridLayout *hbox_layout_menu  = new QGridLayout(__menu);
    hbox_layout_menu->setSpacing(4);
    hbox_layout_menu->setObjectName(QStringLiteral("gridLayout"));
    hbox_layout_menu->setContentsMargins(0, 0, 0, 0);

    {
        menu_bar = new QMenuBar(this);
        QFont font = menu_bar->font();
        font.setPointSize(10);
        menu_bar->setFont(font);

        QMenu *file_menu = menu_bar->addMenu("View");
        font = file_menu->font();
        font.setPointSize(10);
        file_menu->setFont(font);

        QMenu *edit_menu = menu_bar->addMenu("Select");
        font = edit_menu->font();
        font.setPointSize(10);
        edit_menu->setFont(font);

        QMenu *add_menu = menu_bar->addMenu("Add");
        font = add_menu->font();
        font.setPointSize(10);
        add_menu->setFont(font);

        QMenu *mesh_menu = menu_bar->addMenu("Mesh");
        font = mesh_menu->font();
        font.setPointSize(10);
        mesh_menu->setFont(font);
    }

    hbox_layout_menu->addWidget(menu_bar, 0, 0, 1, 1);*/


    /*auto *_slcft = new QAction("&Select from:to", this);
    auto *_slco = new QAction("&Select One", this);
    auto *_delete_selected = new QAction("&Delete selected", this);
    auto *_copy_selected = new QAction("&Copy selected", this);
    edit_menu->addAction(_slcft);
    edit_menu->addAction(_slco);
    edit_menu->addAction(_delete_selected);
    edit_menu->addAction(_copy_selected);*/

    connect(this->pushButton_vertex_edmd, SIGNAL(clicked()), this,  SLOT(selectVertexEditMode()));
    connect(this->pushButton_edge_edmd, SIGNAL(clicked()), this,  SLOT(selectLineEditMode()));
    connect(this->pushButton_face_edmd, SIGNAL(clicked()), this,  SLOT(selectFaceEditMode()));

}
void FGEObjectEditing::link(QString name_parent, FGEDataProject *data_project, FGETriggerFunction *trigger, QWidget *menu, QWidget *body){
    if(menu==NULL || body==NULL) return;

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;

    /*QLayoutItem *child;
    if(header->layout()!=NULL){
        while ((child = header->layout()->takeAt(0)) != 0) {
            header->layout()->removeItem(child);
        }
    }*/

    //QLayout *layout = header->layout();
    //layout->deleteLater();
    /*QLayoutItem *child;
    if(header->layout()!=NULL){
        while ((child = header->layout()->takeAt(0)) != 0) {
            delete child;
        }
    }*/
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(widget_header, 0, 0, 1, 1);
    gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);
    gridLayout->setSpacing(4);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    body->setLayout(gridLayout);

    /*if(menu->layout()!=NULL){
        while ((child = menu->layout()->takeAt(0)) != 0) {
            menu->layout()->removeItem(child);
        }
    }*/
    //layout = menu->layout();
    //layout->deleteLater();
    /*if(menu->layout()!=NULL){
        while ((child = menu->layout()->takeAt(0)) != 0) {
            delete child;
        }
    }*/
    QGridLayout *hbox_layout_menu  = new QGridLayout();
    hbox_layout_menu->addWidget(menu_bar, 0, 0, 1, 1);
    hbox_layout_menu->setSpacing(4);
    hbox_layout_menu->setObjectName(QStringLiteral("gridLayout"));
    hbox_layout_menu->setContentsMargins(0, 0, 0, 0);
    menu->setLayout(hbox_layout_menu);
}

void FGEObjectEditing::selectVertexEditMode(){
    //qDebug() << "vertex ddddddddddddddd";
    emit this->trigger->switch3DViewToEditMode(this->name_parent, 1);
}
void FGEObjectEditing::selectLineEditMode(){
    emit this->trigger->switch3DViewToEditMode(this->name_parent, 2);
}
void FGEObjectEditing::selectFaceEditMode(){
    emit this->trigger->switch3DViewToEditMode(this->name_parent, 3);
}
