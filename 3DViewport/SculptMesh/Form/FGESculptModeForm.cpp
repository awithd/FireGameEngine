#include "FGESculptModeForm.h"
#include "ui_FGESculptModeForm.h"

FGESculptModeForm::FGESculptModeForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGESculptModeForm)
{
    ui->setupUi(this);

    this->first_sculpt_item=NULL;
    this->last_sculpt_item=NULL;

    this->data_project = data_project;
    this->trigger = trigger;
    this->name_parent = name_parent;


    addSculptItem(0, "Draw", "/home/corolo/Qt/FireGameEngine22/Icons/Sculpts/1.png");
    addSculptItem(1, "Clay", "/home/corolo/Qt/FireGameEngine22/Icons/Sculpts/2.png");
    addSculptItem(2, "Flatten", "/home/corolo/Qt/FireGameEngine22/Icons/Sculpts/3.png");
    addSculptItem(3, "Crease", "/home/corolo/Qt/FireGameEngine22/Icons/Sculpts/4.png");

    FGESculptItem *p = this->first_sculpt_item;
    //QSize size(290, 260);

    while(p!=NULL){

        QListWidgetItem* dog = new QListWidgetItem();
        //dog->setSizeHint(size);
        dog->setIcon(QIcon(p->icon));
        dog->setText(p->name);

        QVariant pp = QVariant::fromValue<void*>(p);
        dog->setData(Qt::UserRole, pp);

        ui->listWidget->addItem(dog);
        //ui->listWidget->setItemWidget(dog, item);

        p=p->next;
    }
}

FGESculptModeForm::~FGESculptModeForm()
{
    delete ui;
}

void FGESculptModeForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    QVariant v = item->data(Qt::UserRole);
    FGESculptItem *_item = (FGESculptItem*) v.value<void *>();
    emit this->trigger->switch3DViewToSculptMode(this->name_parent, _item);

}

FGESculptItem *FGESculptModeForm::addSculptItem(uint id, QString name, QString icon){
    FGESculptItem *item = new FGESculptItem(name, icon);
    if(this->first_sculpt_item==NULL){
        this->first_sculpt_item = item;
        this->last_sculpt_item = item;
        item->id = id;
    }else{
        this->last_sculpt_item->next = item;
        item->prev = this->last_sculpt_item;
        this->last_sculpt_item = item;
        item->id = id;
    }
    return item;
}
