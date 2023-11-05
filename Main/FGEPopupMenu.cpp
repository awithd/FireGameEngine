#include "FGEPopupMenu.h"
#include "ui_FGEPopupMenu.h"

#include <QScreen>

FGEPopupMenu::FGEPopupMenu(FGEDataProject *sp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEPopupMenu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //setAttribute( Qt::WA_NoSystemBackground, true );
    //setAttribute( Qt::WA_OpaquePaintEvent, false );
    //setAttribute(Qt::WA_NoBackground);

    _layout = new QGridLayout();
    this->struct_project = sp;
    //QPalette
    //this->setBackgroundRole(QPalette::);

    /*QPalette editorPalette = palette();
    editorPalette.setColor(QPalette::Active, QPalette::Base, Qt::transparent);
    editorPalette.setColor(QPalette::Inactive, QPalette::Base, Qt::transparent);*/
    //setPalette(editorPalette);
    setStyleSheet("QWidget#Menu { background: rgba( 255, 255, 255, 0); border-radius: 20px; border: 10px solid green; }");
    this->cont_widget = NULL;

    animation = new QPropertyAnimation(this, "geometry");
    this->__f = 0;
    this->__g = 0;
    //this->_w_parent = NULL;
}

FGEPopupMenu::~FGEPopupMenu()
{
    delete ui;
}

void FGEPopupMenu::addWidget(QWidget *add_mf)
{

    //this->cont_widget;
    //qDebug() << "addWidget 888 : ";

    if(this->cont_widget!=NULL){
        //qDebug() << "addWidget 12 : ";
        _layout->removeWidget(this->cont_widget);

    }

    add_mf->show();
    //qDebug() << "addWidget 2 ";
    this->cont_widget = add_mf;
    _layout->addWidget(this->cont_widget);
    ui->widget->setLayout(_layout);
    //qDebug() << "addWidget 3 ";
}

/*void FGEPopupMenu::_setParent(FGEGL3DViewportForm *_w_parent)
{
    this->_w_parent = _w_parent;
}*/

void FGEPopupMenu::initPopup(QWidget *add_mesh, QPoint _p, int w, int h){

    //qDebug() << "initPopup 0";
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int _height = screenGeometry.height();
    int _width = screenGeometry.width();
    //qDebug() << "initPopup 1 o : "<< add_mesh->height();

    //FGEListAddMeshForm *add_mesh = new FGEListAddMeshForm();
    //add_mesh->_setParent(this);
    this->addWidget(add_mesh);
    //qDebug() << "initPopup 2";
    //QPoint _p = ui->pushButton_menu_add_mesh->cursor().pos();
    int _w = add_mesh->width()+28;
    int _h = add_mesh->height()+28;
    //int h = ui->pushButton_menu_add_mesh->height();

    //qDebug() << "_w : ("<<_w<<")";
    //qDebug() << "_h : ("<<_h<<")";

    QPoint p = QPoint(_p.x()-(_w/2)+(w/2),_p.y()+h);
    if(p.x()<0){
        this->__f = p.x();
        p.setX(0);
    }else if(p.x()>_width-_w){
        this->__f = p.x()-_width+_w;
        p.setX(_width-_w);
    }else{
        this->__f = 0;
    }

    if(p.y()>_height-_h){
        this->__g = _h;
        p.setY(_p.y()-_h-6);
    }else{

        this->__g = 0;
    }

    //qDebug() << "initPopup : ("<<p.x()<<", "<<p.y()<<")";
    animation->setDuration(100);
    animation->setStartValue(QRect(p.x(), p.y()-6, _w, _h));
    animation->setEndValue(QRect(p.x(), p.y(), _w, _h));

    animation->setEasingCurve(QEasingCurve::OutCirc);
    //_parent = ui->pushButton_menu_add_mesh;


}

void FGEPopupMenu::startAnimation(){
    animation->start();
}

void FGEPopupMenu::appendDirectSun()
{
    //qDebug() << "append Direct Sun";
    struct_project->count_object++;

    FGEDataNode *node_light = new FGEDataNode;

    node_light->name = "Light";
    node_light->first_child = NULL;
    node_light->last_child = NULL;
    node_light->next = NULL;
    node_light->prev = NULL;
    //node_light->tree_widget_item = NULL;
    node_light->type = "Light";
    node_light->id = 3;
    //node_light->is_set = false;
    node_light->transform = new FGETransformation(NULL, NULL);
    //node_light->color_selection = struct_project->current_color_selection;
    struct_project->current_color_selection++;

    node_light->parent = NULL;
    //node_light->scene = this->struct_project->current_scene;


    //node_light->object = NULL;

    /*if(this->struct_project->current_scene->node==NULL){
        qDebug() << "fff";
        this->struct_project->current_scene->node = node_light;
    }else{
        qDebug() << "sss";
        FGENodeOS *p = this->struct_project->current_scene->node, *op;
        while(p!=NULL){
            op = p;
            p=p->next;
        }
        op->next = node_light;
        node_light->prev = op;
    }
    this->struct_project->current_node = node_light;
*/
    this->hide();
    emit emitUpdateGLViews();
}

void FGEPopupMenu::appendDirectCudeMesh()
{
    /*qDebug() << "appendDirectCudeMesh";
    struct_project->count_object++;

    FGENodeOS *node = new FGENodeOS;

    node->type = 2;
    node->child = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->tree_widget_item = NULL;
    node->name = "Cube";
    node->type = "Geometry";
    node->id = 3;
    node->is_set = false;
    node->transform = new FGETransformation(NULL, NULL);
    node->color_selection = struct_project->current_color_selection;
    struct_project->current_color_selection++;

    node->parent = NULL;
    node->scene = this->struct_project->current_scene;

    FGEObjectOS *obj = new FGEObjectOS;

    FGETexture *tex = new FGETexture;
    tex->name = "/home/corolo/Pictures/147487.jpg";
    tex->next = NULL;
    tex->prev = NULL;
    obj->first_texture = tex;

    FGEMaterialOS *mat = new FGEMaterialOS;
    mat->next = NULL;
    mat->prev = NULL;
    mat->diffuse_texture = tex;
    obj->first_material = mat;

    FGEGeometryOS *geo = new FGEGeometryOS();
    geo->id = 1;
    geo->next = NULL;
    geo->prev = NULL;
    geo->name = "Cube";
    FGEGeometry cube;
    cube.cube(geo);
    geo->order = FGE_POSITION_NORMAL_TEXCOORD_ORDER;
    geo->material = mat;
    geo->count_triangles = 12;

    obj->first_geometry = geo;
    node->object = obj;

    if(this->struct_project->current_scene->node==NULL){
        qDebug() << "fff";
        this->struct_project->current_scene->node = node;
    }else{
        qDebug() << "sss";
        FGENodeOS *p = this->struct_project->current_scene->node, *op;
        while(p!=NULL){
            op = p;
            p=p->next;
        }
        op->next = node;
        node->prev = op;
    }
    this->struct_project->current_node = node;*/


/*

    FGEDataNode *node = new FGEDataNode();
    node->transform = new FGETransformation(NULL, NULL);
    node->transform->setLocalVectorTranslation(0.0, 0.0, 0.0);
    node->name = "new cube";

    FGEDataNode *parent_node =  this->struct_project->current_node;
    if(parent_node!=NULL){
        node->transform->setParent(parent_node->transform);

        if(parent_node->first_child==NULL){
            parent_node->first_child = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }else{
            node->prev = parent_node->last_child;
            parent_node->last_child->next = node;
            parent_node->last_child = node;
            node->parent = parent_node;
        }
    }

        node->simple = new FGEDataSimple();
        node->simple->sid = "id";
        node->simple->name = "id";
        //  search mesh in data
        //if(data_mesh==NULL){
        FGEDataMesh * data_mesh = new FGEDataMesh();
        data_mesh->name = "m";
        this->struct_project->appendNewMesh(data_mesh);
        //}

        node->simple->mesh.push_back(data_mesh);
        this->struct_project->appendNewSiple(node->simple);

        FGEDataTriangles *data_triangles = new FGEDataTriangles();
        data_triangles->material = NULL;
        data_triangles->offset_size = 3;
        data_mesh->triangles.push_back(data_triangles);

        /*FGE3DGeometryBox box;
        QVector<float> vertex;

        box.getBox(data_triangles->index, vertex, 2, 2, 2, 10, 10, 10);*/
        /*FGE3DGeometryCylinder cylinder;
        QVector<float> vertex;

        cylinder.getCylinder(data_triangles->index, vertex, 3.0, 1, 4.0, 1, 4.0, 3, 1);

        {
            data_triangles->vertex = new FGEDataResources("_ss", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_VRTEX3F);
            FGEDataVectorf3 *vec = (FGEDataVectorf3*)data_triangles->vertex->data;
            for(unsigned int i =0;i<vertex.size(); i++){
                fge_f3 d;
                d.x = vertex.at(i);
                i++;
                d.y = vertex.at(i);
                i++;
                d.z = vertex.at(i);
                vec->vector.push_back(d);
            }
        }

        {
            data_triangles->normal = new FGEDataResources("source", FGE_TYPE_VECTOR_F3, FGE_RES_SEMANTIC_NORMAL3F);
            FGEDataVectorf3 *vec = (FGEDataVectorf3*)data_triangles->normal->data;

            ////qDebug() <<" normal : " << source << " ; s ;"<<m.size();

            for(unsigned int i =0;i<vertex.size(); i++){
                fge_f3 d;
                d.x = 0.0;
                i++;
                d.y = 1.0;
                i++;
                d.z = 0.0;
                vec->vector.push_back(d);
            }
        }


        {
            FGEDataResources *__uv = new FGEDataResources("source", FGE_TYPE_VECTOR_F2, FGE_RES_SEMANTIC_UVMAP2F);
            FGEDataVectorf2 *vec = (FGEDataVectorf2*)__uv->data;

            //qDebug() <<" __uv : " << source << " ; s ;"<<m.size();

            for(unsigned int i =0;i<vertex.size(); i++){
                fge_f2 d;
                d.x = 0.0;
                i++;
                d.y = 0.0;
                vec->vector.push_back(d);
            }
            data_triangles->uv.push_back(__uv);
        }




        node->simple->matrix = glm::mat4(1.0);

        node->color_selection = this->struct_project->current_color_selection;
        this->struct_project->current_color_selection++;

        if(this->struct_project->current_scene->first_node==NULL){
            this->struct_project->current_scene->first_node = node;
            this->struct_project->current_scene->last_node = node;
        }else{
            node->prev = this->struct_project->current_scene->last_node;
            this->struct_project->current_scene->last_node->next = node;
            this->struct_project->current_scene->last_node = node;
        }

    //this->hide();
    emit createNewObject();*/

}


void FGEPopupMenu::appendDirectPlan()
{
    /*qDebug() << "appendDirectCudeMesh";
    struct_project->count_object++;

    FGENodeOS *node = new FGENodeOS;

    node->type = 2;
    node->child = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->tree_widget_item = NULL;
    node->name = "Cube";
    node->type = "Geometry";
    node->id = 3;
    node->is_set = false;
    node->transform = new FGETransformation(NULL, NULL);
    node->color_selection = struct_project->current_color_selection;
    struct_project->current_color_selection++;

    node->parent = NULL;
    node->scene = this->struct_project->current_scene;

    FGEObjectOS *obj = new FGEObjectOS;

    FGETexture *tex = new FGETexture;
    tex->name = "/home/corolo/Pictures/147487.jpg";
    tex->next = NULL;
    tex->prev = NULL;
    obj->first_texture = tex;

    FGEMaterialOS *mat = new FGEMaterialOS;
    mat->next = NULL;
    mat->prev = NULL;
    mat->diffuse_texture = tex;
    obj->first_material = mat;

    FGEGeometryOS *geo = new FGEGeometryOS();
    geo->id = 1;
    geo->next = NULL;
    geo->prev = NULL;
    geo->name = "Cube";
    FGE3DGeometryPlane plane;
    int i = 0;
    plane.getBuffer(geo->vertices, 1, 1, 1, 1, i, 0);
    unsigned int indices[6] = {
         0, 1, 2, 3, 4, 5
    };

    geo->indices_triangles.clear();
    for(int i=0; i<6; i++){
        geo->indices_triangles.push_back(indices[i]);
    }

    geo->order = FGE_POSITION_NORMAL_TEXCOORD_ORDER;
    geo->material = mat;
    geo->count_triangles = 2;

    obj->first_geometry = geo;
    node->object = obj;

    if(this->struct_project->current_scene->node==NULL){
        qDebug() << "fff";
        this->struct_project->current_scene->node = node;
    }else{
        qDebug() << "sss";
        FGENodeOS *p = this->struct_project->current_scene->node, *op;
        while(p!=NULL){
            op = p;
            p=p->next;
        }
        op->next = node;
        node->prev = op;
    }
    this->struct_project->current_node = node;

    this->hide();
    emit emitUpdateGLViews();
    //if(this->_w_parent != NULL) this->_w_parent->addDirectCudeMesh();
*/
}



void FGEPopupMenu::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    // Draw the popup here
    // You can always pick an image and use drawPixmap to
    // draw it in order to make things simpler



    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Prepare the popup dimensions
    QRect roundedRectDimensions;
    roundedRectDimensions.setX(rect().x() + 10);
    roundedRectDimensions.setY(rect().y() + 10);
    roundedRectDimensions.setWidth(rect().width() - 20);
    roundedRectDimensions.setHeight(rect().height() - 20);

    QPalette  pl = ui->widget->palette();
    QColor green70 = pl.brush(this->backgroundRole()).color();
    green70.setAlphaF( 1.0 );
    painter.setBrush(QBrush(green70));

    QPen pen;
    pen.setColor(QColor(0, 40, 40, 255));
    pen.setWidth(6);
    painter.setPen(pen);

    // Draw the popup body
    painter.drawRoundedRect(roundedRectDimensions, 3, 3);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(0, 40, 40, 255)));

    // Draw the popup pointer
    const QPointF points[3] = {
        QPoint(this->__f+rect().width()/2-8, 10+this->__g),
        QPoint(this->__f+rect().width()/2+8, 10+this->__g),
        QPoint(this->__f+rect().width()/2 , this->__g)
    };

    painter.drawPolygon(points, 3);
}
void FGEPopupMenu::hideEvent(QHideEvent *e)
{
    ///qDebug() << "hideEvent";
    if(this->cont_widget!=NULL){
        this->cont_widget->hide();
        //this->cont_widget->deleteLater();
        //this->cont_widget=NULL;
    }
}

void FGEPopupMenu::showEvent(QShowEvent *e)
{
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    animation->start();
    //qDebug() << "showEvent";
}
