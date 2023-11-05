#include "FGEGeometryEditCircleForm.h"
#include "ui_FGEGeometryEditCircleForm.h"

FGEGeometryEditCircleForm::FGEGeometryEditCircleForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEGeometryEditCircleForm)
{
    ui->setupUi(this);
    this->swap = false;
    this->swap_solver = false;
    this->st_solver = false;
    this->enable_change = false;
    this->pass_arrow = false;
    this->data_project = data_project;
    this->glwidget_world = glwidget_world;


    animation = new QPropertyAnimation(ui->widget, "geometry");
    animation->setDuration(100); // مدة الرسوم المتحركة بالمللي ثانية
    animation->setStartValue(30); // ارتفاع البداية
    animation->setEndValue(200); // ارتفاع النهاية

    anim_arrow = new QPropertyAnimation(ui->pushButton, "rotation");
    anim_arrow->setDuration(200); // Animation duration in milliseconds

    QIcon ic(":/Icons/svg/right_arrow.svg");
    pixmap_arrow = ic.pixmap(32, 32);

    size = this->sizeHint();
    QObject::connect(animation, &QPropertyAnimation::valueChanged, this, &FGEGeometryEditCircleForm::slotValueChanged);
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
                if(node->mesh->shape_type.type==FGE_SHAPE_TYPE_CIRCLE){
                    this->shape_type = node->mesh->shape_type.type;
                    FGE3DGeometryItemCircle *item_circle = (FGE3DGeometryItemCircle *)node->mesh->shape_type.item;
                    ui->doubleSpinBox_r->setValue(item_circle->diameter);
                    ui->spinBox_s->setValue(item_circle->sectors);
                    ui->spinBox_t->setValue(item_circle->stacks);
                    ui->checkBox->setChecked(item_circle->polygonal);
                    this->enable_change = true;
                }
            }
        }
    }
}

FGEGeometryEditCircleForm::~FGEGeometryEditCircleForm()
{
    delete ui;
}

void FGEGeometryEditCircleForm::on_pushButton_clicked()
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

void FGEGeometryEditCircleForm::slotValueChanged(const QVariant &value)
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


void FGEGeometryEditCircleForm::updateCircle()
{
    if(!this->enable_change) return;

    float _r = ui->doubleSpinBox_r->value();
    uint _t = ui->spinBox_t->value();
    uint _s = ui->spinBox_s->value();
    uint _ch = ui->checkBox->isChecked();

    if(_r<=0 || _t<=0 || _s<=0) {
        return;
    }
    FGEDataSelectedNodes * sn = this->data_project->getSelectedNodes();
    if(sn->selected_nodes.size()==1){
        FGEDataNode * node = sn->selected_nodes.at(0);
        if(node!=NULL){
            if(node->mesh!=NULL){
                if(node->mesh->shape_type.type==FGE_SHAPE_TYPE_CIRCLE){
                    this->glwidget_world->makeCurrent();
                    FGE3DGeometryCircle circle;
                    circle.createMeshCircle(this->glwidget_world->openGLFunctions(), this->data_project, node, node->mesh, _t, _s, _r, _ch);
                    this->glwidget_world->doneCurrent();
                    emit this->data_project->trigger->updateScene();

                }
            }
        }
    }
}

void FGEGeometryEditCircleForm::on_doubleSpinBox_r_valueChanged(double arg1)
{
    this->updateCircle();
}

void FGEGeometryEditCircleForm::on_spinBox_t_valueChanged(int arg1)
{
    this->updateCircle();
}

void FGEGeometryEditCircleForm::on_spinBox_s_valueChanged(int arg1)
{
    this->updateCircle();
}

void FGEGeometryEditCircleForm::on_checkBox_toggled(bool checked)
{
    this->updateCircle();
}

