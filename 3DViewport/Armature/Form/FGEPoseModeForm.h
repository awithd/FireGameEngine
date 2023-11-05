#ifndef FGEPOSEMODEFORM_H
#define FGEPOSEMODEFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>

namespace Ui {
class FGEPoseModeForm;
}

class FGEPoseModeForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEPoseModeForm(FGEDataProject *data_project, FGETriggerFunction *trigger, QString name_parent, QWidget *parent = nullptr);
    ~FGEPoseModeForm();


    FGEDataProject *data_project;
    FGETriggerFunction *trigger;
    QString name_parent;


private slots:
    void on_insertKey_PushButton_clicked();

private:
    Ui::FGEPoseModeForm *ui;
};

#endif // FGEPOSEMODEFORM_H
