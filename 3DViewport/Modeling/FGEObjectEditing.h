#ifndef FGEOBJECTEDITING_H
#define FGEOBJECTEDITING_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QSpacerItem>
#include <StructData/FGEDataProject.h>

class FGEObjectEditing : public QWidget
{
    Q_OBJECT
public:
    explicit FGEObjectEditing(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent = 0);
    void link(QString name_parent, FGEDataProject *data_project, FGETriggerFunction *trigger, QWidget *menu, QWidget *body);


    QWidget *widget_header;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_edge_edmd;
    QPushButton *pushButton_vertex_edmd;
    QPushButton *pushButton_face_edmd;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menu_bar;

    QString name_parent;

    FGEDataProject *data_project;
    FGETriggerFunction *trigger;

public slots:
    void selectVertexEditMode();
    void selectLineEditMode();
    void selectFaceEditMode();

};

#endif // FGEOBJECTEDITING_H
