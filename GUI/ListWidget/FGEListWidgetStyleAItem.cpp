#include "FGEListWidgetStyleAItem.h"
#include "ui_FGEListWidgetStyleAItem.h"

FGEListWidgetStyleAItem::FGEListWidgetStyleAItem(FGEListWidgetStyleBItem *widget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEListWidgetStyleAItem)
{
    this->animation_is_current = false;
    ui->setupUi(this);
    this->widget = widget;
    ui->gridLayout->addWidget(this->widget, 0, 0, 1, 1);


    this->swap = false;
    this->swap_solver = false;
    this->st_solver = false;
    this->enable_change = false;
    this->pass_arrow = false;

    this->item = new QListWidgetItem();
    this->item->setSizeHint(this->sizeHint());

    animation = new QPropertyAnimation(this->ui->widget, "geometry");
    animation->setDuration(100); // مدة الرسوم المتحركة بالمللي ثانية
    animation->setStartValue(30); // ارتفاع البداية
    animation->setEndValue(200); // ارتفاع النهاية

    anim_arrow = new QPropertyAnimation(ui->pushButton, "rotation");
    anim_arrow->setDuration(200); // Animation duration in milliseconds

    QIcon ic(":/Icons/svg/right_arrow.svg");
    pixmap_arrow = ic.pixmap(32, 32);

    size = this->sizeHint();
    qDebug()<<"size : "<<size.width()<<", "<<size.height();

    QObject::connect(animation, &QPropertyAnimation::valueChanged, this, &FGEListWidgetStyleAItem::slotValueChanged);
    //QObject::connect(animation_solver, &QPropertyAnimation::valueChanged, this, &TrestForm::slotSolverChanged);
    QObject::connect(animation, &QPropertyAnimation::finished, this, &FGEListWidgetStyleAItem::endAnim);


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

    //QObject::connect(this->widget, SIGNAL(sizeChanged(QResizeEvent*)), this,SLOT(updateSize(QResizeEvent*)));

    QObject::connect(this->widget, SIGNAL(sizeChanged(QResizeEvent*)), this,SLOT(updateSize(QResizeEvent*)));
    this->animation_is_current = true;

}

FGEListWidgetStyleAItem::~FGEListWidgetStyleAItem()
{
    delete ui;
}

void FGEListWidgetStyleAItem::setTitle(QString title)
{
    this->ui->label->setText(title);
}

void FGEListWidgetStyleAItem::setIcon(QString icon)
{
    this->ui->label_icon->setPixmap(QPixmap(icon));
    this->ui->label_icon->setScaledContents(true);
}


void FGEListWidgetStyleAItem::updateSize(QResizeEvent *event)
{

    //if(!this->animation_is_current){
        QSize _size = event->size();
        //QSize s = this->item->sizeHint();
        //int h = size.height();
        //int w = size.width();
        qDebug()<<"000000nresizeEvent : "<<_size.width()<<", "<<_size.height();
        this->item->setSizeHint(QSize(_size.width(), _size.height()+54));
    //}
}

void FGEListWidgetStyleAItem::on_pushButton_clicked()
{
    this->animation_is_current = true;
    this->pass_arrow = false;

    if(swap){
        ui->widget_3->setHidden(false);

        //QSize s = QSize(size.width(), 58);
        //this->item->setSizeHint(s);
        //QSize size = this->widget->geometry().size();
        QSize _size = this->widget->sizeHint();
        animation->setStartValue(QRect(2,2, _size.width(), 48));
        animation->setEndValue(QRect(2,2, _size.width(), _size.height()));
qDebug()<<"cv : "<<this->widget->geometry().width()<<", "<<this->widget->geometry().height();
        anim_arrow->setStartValue(0);
        anim_arrow->setEndValue(90); // Rotate 90 degrees on each click
        anim_arrow->start();

        //this->widget->setAttribute(Qt::WA_TranslucentBackground, false);
        this->widget->setStyleSheet("");
        //ui->widget->resize(size.width(), size.height());
        //ui->pushButton->setIcon(QIcon(":/Icons/svg/down_arrow.svg")); // استعادة الأيقونة الابتدائية عند النقر مرة أخرى

    }else{

        //ui->pushButton->setIcon(QIcon(":/Icons/svg/right_arrow.svg")); // تغيير الأيقونة عند النقر

        ui->widget_3->setHidden(true);
        //this->item->setSizeHint(size);
        size = ui->widget->geometry().size();
        //QSize _size = this->sizeHint();
        QSize _size = this->widget->sizeHint();



        animation->setStartValue(QRect(2, 2, _size.width(), _size.height()));
        animation->setEndValue(QRect(2, 2, _size.width(), 48));
        //animation->setEndValue(48)

        anim_arrow->setStartValue(90);
        anim_arrow->setEndValue(0); // Rotate 90 degrees on each click
        anim_arrow->start();

        this->widget->setStyleSheet("background:transparent;");

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

void FGEListWidgetStyleAItem::slotValueChanged(const QVariant &value)
{
    // قم بأي عمل ترغب فيه عند تغيير قيمة الرسم المتحركة هنا

    // يمكنك استخدام القيمة المستلمة (value) إذا كانت مفيدة
    if (value.canConvert<QRect>()) {
        QRect rectValue = value.value<QRect>();
        // يمكنك استخدام rectValue كـ QRect الآن
        this->item->setSizeHint(QSize(rectValue.width(), rectValue.height()+4));
        //ui->widget->setMinimumHeight(rectValue.height());
        //ui->widget->setMaximumHeight(rectValue.height());
    } else {
        // إذا لم يكن يمكن التحويل إلى QRect
        // قم باتخاذ الإجراء المناسب هنا
    }/**/

    ///this->ui->widget_3->updateGeometry();
}

void FGEListWidgetStyleAItem::endAnim()
{

    this->animation_is_current = false;
}

