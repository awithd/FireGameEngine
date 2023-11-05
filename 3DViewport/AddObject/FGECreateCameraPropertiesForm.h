#ifndef FGECREATECAMERAPROPERTIESFORM_H
#define FGECREATECAMERAPROPERTIESFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>

namespace Ui {
class FGECreateCameraPropertiesForm;
}

class FGECreateCameraPropertiesForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGECreateCameraPropertiesForm(FGEDataProject *data_project, QWidget *parent = nullptr);
    ~FGECreateCameraPropertiesForm();

    FGEDataProject *data_project;

private slots:
    void on_create_pushButton_clicked();

private:
    Ui::FGECreateCameraPropertiesForm *ui;
};

#endif // FGECREATECAMERAPROPERTIESFORM_H
