#ifndef FGETREEWIDGET_H
#define FGETREEWIDGET_H

#include <QObject>
#include <QGridLayout>
#include <QSplitter>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QSplitter>

#define FGE_TYPE_WIDGET_NULL                0
#define FGE_TYPE_WIDGET_WIDGET              1
#define FGE_TYPE_WIDGET_3DVIEW              2
#define FGE_TYPE_WIDGET_MATERIAL            3
#define FGE_TYPE_WIDGET_BROWSER_MATERIALS   4
#define FGE_TYPE_WIDGET_PROJECT             5
#define FGE_TYPE_WIDGET_OUTLINER            6
#define FGE_TYPE_WIDGET_UVEDITOR            7
#define FGE_TYPE_WIDGET_TIMELINE            8
#define FGE_TYPE_WIDGET_CONSOLE             9


class FGETreeWidget
{
public:
    FGETreeWidget();
    ~FGETreeWidget();

    /*void clear(){
        FGEItemGL3DViewportForm *p = this->first_item, *k=NULL;
        while(p!=NULL){
            k = p;
            p=p->next;
            delete k;
        }

        this->first_item = NULL;
        this->last_item = NULL;
    }*/

    void appendItem(void *widget, int dir, QGridLayout *layout, QSplitter *spliter, int type, FGETreeWidget *parent);
    void spliteItem(void *widget, void *widget_child, int dir, QGridLayout *layout, QSplitter *spliter, int type, FGETreeWidget *parent);

    //void init(FGETreeWidget *p, FGEStructProject *sp);

    void *widget;
    int type;
    QSplitter *spliter;
    QGridLayout *layout;

    FGETreeWidget *parent;
    FGETreeWidget *child_left;
    FGETreeWidget *child_right;
};

#endif // FGETREEWIDGET_H
