#include "FGETreeWidget.h"

FGETreeWidget::FGETreeWidget()
{
    this->parent = NULL;
    this->child_left = NULL;
    this->child_right = NULL;
    this->type = 0;
}
FGETreeWidget::~FGETreeWidget(){

}

/*void FGETreeWidget::init(FGETreeWidget *p, FGEStructProject *sp)
{
    qDebug() << "M";
    if(p!=NULL){
        if(p->type==2){
            qDebug() << "M 1";
            FGEGL3DViewportForm * w = (FGEGL3DViewportForm *)p->widget;
            qDebug() << "M 1F" ;
            w->initStructPorject(sp, NULL);
            qDebug() << "M 1E";

        }

        if(p->child_left!=NULL){
            init(p->child_left, sp);
        }

        if(p->child_right!=NULL){
            init(p->child_right, sp);
        }
    }
}*/

void FGETreeWidget::appendItem(void *widget, int dir, QGridLayout *layout, QSplitter *spliter, int type, FGETreeWidget *parent)
{
    this->widget = widget;
    this->type = type;
    this->spliter = spliter;
    this->layout = layout;
    this->parent = parent;
    this->child_left = NULL;
    this->child_right = NULL;
    if(parent!=NULL){
        if(dir==0){
            this->parent->child_left = this;
        }else{
            this->parent->child_right = this;
        }
    }
}

void FGETreeWidget::spliteItem(void *widget, void *widget_child, int dir, QGridLayout *layout, QSplitter *spliter, int type, FGETreeWidget *parent)
{
    FGETreeWidget *child_tw1 = new FGETreeWidget();
    //ths->tree_widget_item = child_tw1;
    child_tw1->appendItem(this->child_left->widget, 0, NULL, NULL, 1, this);


    FGETreeWidget *child_tw2 = new FGETreeWidget();
    //widget->tree_widget_item = child_tw2;
    child_tw2->appendItem(widget_child, 0, NULL, NULL, 2, this);

    this->widget = widget;
    this->type = type;
    this->spliter = spliter;
    this->layout = layout;

}
