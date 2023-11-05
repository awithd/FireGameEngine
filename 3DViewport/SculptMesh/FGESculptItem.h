#ifndef FGESCULPTITEM_H
#define FGESCULPTITEM_H

#include <QWidget>
class FGESculptItem{
public:
    FGESculptItem(QString name, QString icon){
        this->name = name;
        this->icon = icon;
        this->next = NULL;
        this->prev = NULL;

        position[3] = 0;
    }
    uint id;
    QString name;
    QString icon;
    float position[3];
    float normal[3];

    FGESculptItem *next, *prev;
};
#endif // FGESCULPTITEM_H
