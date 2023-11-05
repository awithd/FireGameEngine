#ifndef FGEANIMATIONTIMELINE_H
#define FGEANIMATIONTIMELINE_H


#include <QWidget>
#include <QScrollBar>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>
#include <TimeLine/FGEItemTimeLine.h>


class FGEActionTimeLine{
public:
    FGEActionTimeLine(){

    }
    int id;
    QString name;
    void *channel;
    QLabel *label;
    QTreeWidgetItem *item;
    QListWidgetItem *litem;
    FGEItemTimeLine *kesyframes;
};

class FGEAnimationTimeLine{
public:
    FGEAnimationTimeLine();
    int id;
    QString name;
    QLabel *label;
    FGEItemTimeLine *kesyframes;
    QTreeWidgetItem *item;
    QListWidgetItem *litem;

    QVector <FGEActionTimeLine *> actions;

    FGEAnimationTimeLine *next;
    FGEAnimationTimeLine *prev;
};


#endif // FGEANIMATIONTIMELINE_H
