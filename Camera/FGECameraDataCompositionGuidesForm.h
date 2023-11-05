#ifndef FGECAMERADATACOMPOSITIONGUIDESFORM_H
#define FGECAMERADATACOMPOSITIONGUIDESFORM_H

#include <QWidget>
#include <QListWidgetItem>
#include <StructData/FGEDataProject.h>
#include <GUI/ListWidget/FGEListWidgetStyleBItem.h>

namespace Ui {
class FGECameraDataCompositionGuidesForm;
}

class FGECameraDataCompositionGuidesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECameraDataCompositionGuidesForm(FGEDataProject *data_project, FGEDataCamera *camera, QWidget *parent = nullptr);
    ~FGECameraDataCompositionGuidesForm();

    FGEListWidgetStyleBItem *getWidgetB();
    FGEDataCamera *camera;
    FGEDataProject *data_project;
    QListWidgetItem *item;

signals:
    void heightChanged(int height);
private:
    Ui::FGECameraDataCompositionGuidesForm *ui;
};

#endif // FGECAMERADATACOMPOSITIONGUIDESFORM_H
