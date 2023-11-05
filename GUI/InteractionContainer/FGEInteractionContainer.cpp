#include "FGEInteractionContainer.h"
#include "ui_FGEInteractionContainer.h"

FGEInteractionContainer::FGEInteractionContainer(void *data_project, void *trigger, QString name_parent, void *glwidget_world, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectInteractionContainer)
{
    ui->setupUi(this);
    this->data_project = data_project;
    this->trigger = trigger;
    this->glwidget_world = glwidget_world;
}

FGEInteractionContainer::~FGEInteractionContainer()
{
    delete ui;
}

void FGEInteractionContainer::setWidget(QWidget *wid, int column)
{
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(wid);
    layout->setSpacing(0);
    if(column==0){
        ui->widget_w1b->setLayout(layout);
    }else if(column==1){
        ui->widget_w2b->setLayout(layout);
    }else if(column==2){
        ui->widget_w3b->setLayout(layout);
    }else if(column==3){
        ui->widget_w4b->setLayout(layout);
    }
}

QWidget * FGEInteractionContainer::getWidget(int column)
{
    if(column==0){
        return ui->widget_w1b;
    }else if(column==1){
        return ui->widget_w2b;
    }else if(column==2){
        return ui->widget_w3b;
    }else if(column==3){
        return ui->widget_w4b;
    }
}
