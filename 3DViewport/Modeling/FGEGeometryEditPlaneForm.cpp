#include "FGEGeometryEditPlaneForm.h"
#include "ui_FGEGeometryEditPlaneForm.h"

FGEGeometryEditPlaneForm::FGEGeometryEditPlaneForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEGeometryEditPlaneForm)
{
    ui->setupUi(this);
    //this->item = item;
    this->swap = false;
    this->swap_solver = false;
    this->st_solver = false;
    this->enable_change = false;
    this->pass_arrow = false;
    this->data_project = data_project;
    this->glwidget_world = glwidget_world;

    /*animation_solver = new QPropertyAnimation(ui->widget_5, "geometry");
    animation_solver->setDuration(100); // مدة الرسوم المتحركة بالمللي ثانية
    animation_solver->setStartValue(30); // ارتفاع البداية
    animation_solver->setEndValue(200); //
*/

    animation = new QPropertyAnimation(ui->widget, "geometry");
    animation->setDuration(100); // مدة الرسوم المتحركة بالمللي ثانية
    animation->setStartValue(30); // ارتفاع البداية
    animation->setEndValue(200); // ارتفاع النهاية

    anim_arrow = new QPropertyAnimation(ui->pushButton, "rotation");
    anim_arrow->setDuration(200); // Animation duration in milliseconds

    QIcon ic(":/Icons/svg/right_arrow.svg");
    pixmap_arrow = ic.pixmap(32, 32);

    size = this->sizeHint();
    QObject::connect(animation, &QPropertyAnimation::valueChanged, this, &FGEGeometryEditPlaneForm::slotValueChanged);
    //QObject::connect(animation_solver, &QPropertyAnimation::valueChanged, this, &TrestForm::slotSolverChanged);


    // Define the animation behavior
    QObject::connect(anim_arrow, &QPropertyAnimation::valueChanged, [&](const QVariant &value) {
        if(!this->pass_arrow) {
            this->pass_arrow = true;

        }else{
            int angle = value.toInt();
            //qDebug() << "angle : "<<angle;
            QTransform transform;
            transform = QTransform().translate(15,15).rotate(angle, Qt::ZAxis).translate(-15,-15);

            //QPixmap pixmap = ui->pushButton->icon().pixmap(16, 16); // Adjust the size of the pixmap as needed
            QPixmap pixmap = pixmap_arrow;
            //pixmap.transformed(QTransform().rotate(angle));
            pixmap = pixmap.transformed(transform, Qt::FastTransformation);
            ui->pushButton->setIcon(QIcon(pixmap));
        }
    });


    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->mesh!=NULL){
                if(node->mesh->shape_type.type==FGE_SHAPE_TYPE_PLANE){
                    this->shape_type = node->mesh->shape_type.type;
                    FGE3DGeometryItemPlane *item_plane = (FGE3DGeometryItemPlane *)node->mesh->shape_type.item;
                    ui->spinBox_x->setValue(item_plane->sub_width);
                    ui->spinBox_y->setValue(item_plane->sub_height);
                    ui->doubleSpinBox_x->setValue(item_plane->width);
                    ui->doubleSpinBox_y->setValue(item_plane->height);
                    this->enable_change = true;
                }
            }
        }
    }
}

FGEGeometryEditPlaneForm::~FGEGeometryEditPlaneForm()
{
    delete ui;
}

void FGEGeometryEditPlaneForm::on_pushButton_clicked()
{
    this->pass_arrow = false;
    if(swap){
        ui->widget_3->setHidden(false);

        //QSize s = QSize(size.width(), 58);
        //this->item->setSizeHint(s);

        animation->setStartValue(QRect(9,9, size.width(), 48));
        animation->setEndValue(QRect(9,9, size.width(), size.height()));

        anim_arrow->setStartValue(0);
        anim_arrow->setEndValue(90); // Rotate 90 degrees on each click
        anim_arrow->start();

        //ui->widget->resize(size.width(), size.height());
        //ui->pushButton->setIcon(QIcon(":/Icons/svg/down_arrow.svg")); // استعادة الأيقونة الابتدائية عند النقر مرة أخرى

    }else{

        //ui->pushButton->setIcon(QIcon(":/Icons/svg/right_arrow.svg")); // تغيير الأيقونة عند النقر

        ui->widget_3->setHidden(true);
        //this->item->setSizeHint(size);
        size = ui->widget->geometry().size();


        animation->setStartValue(QRect(9,9, size.width(), size.height()));
        animation->setEndValue(QRect(9,9, size.width(), 48));
        //animation->setEndValue(48)

        anim_arrow->setStartValue(90);
        anim_arrow->setEndValue(0); // Rotate 90 degrees on each click
        anim_arrow->start();

        //ui->widget->resize(size.width(), 48);
    }


    if (animation->state() == QPropertyAnimation::Running)
        animation->stop();

    // انعكاس الاتجاه في كل مرة يتم فيها النقر على الزر
    //animation->setDirection(swap ? QAbstractAnimation::Forward : QAbstractAnimation::Backward);

    animation->start();
    //animation->setDirection(QAbstractAnimation::Forward);

    swap = !swap;
}

void FGEGeometryEditPlaneForm::slotValueChanged(const QVariant &value)
{
    // قم بأي عمل ترغب فيه عند تغيير قيمة الرسم المتحركة هنا

    // يمكنك استخدام القيمة المستلمة (value) إذا كانت مفيدة
    if (value.canConvert<QRect>()) {
        QRect rectValue = value.value<QRect>();
        // يمكنك استخدام rectValue كـ QRect الآن
        ///this->item->setSizeHint(QSize(rectValue.width(), rectValue.height()+18));
        //ui->widget->setMinimumHeight(rectValue.height());
        //ui->widget->setMaximumHeight(rectValue.height());
    } else {
        // إذا لم يكن يمكن التحويل إلى QRect
        // قم باتخاذ الإجراء المناسب هنا
    }
}


void FGEGeometryEditPlaneForm::updatePlane()
{
    if(!this->enable_change) return;

    uint sub_x = ui->spinBox_x->value();
    uint sub_y = ui->spinBox_y->value();
    float w = ui->doubleSpinBox_x->value();
    float h = ui->doubleSpinBox_y->value();

    if(sub_x<=0 || sub_y<=0 || w<=0 || h<=0) {
        return;
    }
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->mesh!=NULL){
                if(node->mesh->shape_type.type==FGE_SHAPE_TYPE_PLANE){
                    this->glwidget_world->makeCurrent();
                    FGE3DGeometryPlane palne;
                    palne.updateNodePlaneSubdevide(this->glwidget_world->openGLFunctions(), this->data_project, node, node->mesh, w, h, sub_x, sub_y);
                    this->glwidget_world->doneCurrent();
                    emit this->data_project->trigger->updateScene();

                }
            }
        }
    }
}
void FGEGeometryEditPlaneForm::on_doubleSpinBox_x_valueChanged(double arg1)
{
    this->updatePlane();
}

void FGEGeometryEditPlaneForm::on_doubleSpinBox_y_valueChanged(double arg1)
{
    this->updatePlane();
}

void FGEGeometryEditPlaneForm::on_spinBox_x_valueChanged(int arg1)
{
    this->updatePlane();
}

void FGEGeometryEditPlaneForm::on_spinBox_y_valueChanged(int arg1)
{
    this->updatePlane();
}




