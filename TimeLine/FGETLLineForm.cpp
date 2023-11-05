#include "FGETLLineForm.h"
#include "ui_FGETLLineForm.h"

FGETLLineForm::FGETLLineForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGETLLineForm)
{
    ui->setupUi(this);
    connect(this, SIGNAL(__updateListWidgetEditorGeometries()),
            ui->listWidget, SLOT(updateEditorGeometries()));
    connect(this, SIGNAL(__updateListWidgetEditorGeometries()),
            ui->listWidget, SLOT(updateEditorData()));
}

FGETLLineForm::~FGETLLineForm()
{
    delete ui;
}

QListWidget * FGETLLineForm::getListWidet()
{
    return ui->listWidget;
}
void FGETLLineForm::updateListWidgetEditorGeometries()
{
    qDebug() << "aSliderPosition : ";

    emit __updateListWidgetEditorGeometries();
}

QWidget * FGETLLineForm::getoooo()
{
    return ui->widget_2;
}

void FGETLLineForm::init(FGEAnimationTimeLine &animation)
{
    /*animation.id = 0;
    animation.name = "Run";
    animation.label = new QLabel();
    animation.label->setText("Run");
    animation.label->setMinimumSize(animation.label->width(), 40);
    animation.label->setStyleSheet("background-color:green;");
    animation.kesyframes = new FGEItemTimeLine();

    animation.kesyframes->setMinimumSize(1000, 40);
    animation.kesyframes->setMaximumSize(1000, 40);
    animation.kesyframes->setStyleSheet("background-color:#4C4C4C02;");

    animation.item = new QTreeWidgetItem();

    animation.litem = new QListWidgetItem();
    animation.litem->setSizeHint(QSize(ui->listWidget->width(), 40));
    ui->listWidget->addItem(animation.litem);
    ui->listWidget->setItemWidget(animation.litem, animation.kesyframes);


    for(int i=0; i<10; i++){

        FGEActionTimeLine *action = new FGEActionTimeLine;
        animation.actions.push_back(action);

        action->id = 0;
        action->name = "action_01";

        /*action->label = new QLabel();
        action->label->setText("action_"+QString(i));
        action->label->setMinimumSize(action->label->width(), 40);
        action->label->setStyleSheet("background-color:#4C4C4C;");*/
        /*action->kesyframes = new FGEItemTimeLine();

        action->kesyframes->setMinimumSize(1000, 40);
        action->kesyframes->setMaximumSize(1000, 40);
        action->kesyframes->setStyleSheet("background-color:#4C4C4C02;");

        action->item = new QTreeWidgetItem();
        action->item->setFlags(action->item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        action->item->setCheckState(0, Qt::Checked);
        action->item->setText(0, "action_"+QString(i));
        action->item->setSizeHint(0, QSize(100, 40));

        animation.item->addChild(action->item);



        action->litem = new QListWidgetItem();
        action->litem->setSizeHint(QSize(ui->listWidget->width(), 40));
        ui->listWidget->addItem(action->litem);
        ui->listWidget->setItemWidget(action->litem, action->kesyframes);
        ////qDebug() << "  -----hhhhhhhh() : ";

    }*/
}
