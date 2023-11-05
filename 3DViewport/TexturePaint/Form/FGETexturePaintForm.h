#ifndef FGETEXTUREPAINTFORM_H
#define FGETEXTUREPAINTFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>

namespace Ui {
class FGETexturePaintForm;
}

class FGETexturePaintForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGETexturePaintForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent = 0);
    ~FGETexturePaintForm();

    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;

private:
    Ui::FGETexturePaintForm *ui;
};

#endif // FGETEXTUREPAINTFORM_H
