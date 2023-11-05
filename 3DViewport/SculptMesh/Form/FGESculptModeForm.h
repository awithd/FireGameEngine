#ifndef FGESCULPTMODEFORM_H
#define FGESCULPTMODEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>
#include <3DViewport/SculptMesh/FGESculptItem.h>

namespace Ui {
class FGESculptModeForm;
}

class FGESculptModeForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGESculptModeForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent = 0);
    ~FGESculptModeForm();
    FGESculptItem *addSculptItem(uint id, QString name, QString icon);



    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;

    FGESculptItem *first_sculpt_item, *last_sculpt_item;

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::FGESculptModeForm *ui;
};

#endif // FGESCULPTMODEFORM_H
