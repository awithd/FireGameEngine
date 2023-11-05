#ifndef FGEINTERACTIONCONTAINER_H
#define FGEINTERACTIONCONTAINER_H

#include <QWidget>

namespace Ui {
class ObjectInteractionContainer;
}

class FGEInteractionContainer : public QWidget
{
    Q_OBJECT

public:
    explicit FGEInteractionContainer(void *data_project, void *trigger, QString name_parent, void *glwidget_world, QWidget *parent = 0);
    ~FGEInteractionContainer();

    void setWidget(QWidget *wid, int column);
    QWidget * getWidget(int column);

    void *data_project;
    void *trigger;
    void *glwidget_world;
    //FGEEditModeObjectInteraction *edit_m;

    Ui::ObjectInteractionContainer *ui;
};

#endif // FGEINTERACTIONCONTAINER_H
