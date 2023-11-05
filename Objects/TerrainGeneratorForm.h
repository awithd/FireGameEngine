#ifndef TERRAINGENERATORFORM_H
#define TERRAINGENERATORFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>

namespace Ui {
class TerrainGeneratorForm;
}

class TerrainGeneratorForm : public QWidget
{
    Q_OBJECT

public:
    explicit TerrainGeneratorForm(FGETriggerFunction *trigger, FGEDataProject *data_project, QWidget *parent = 0);
    ~TerrainGeneratorForm();

    FGETriggerFunction *trigger;
    FGEDataProject *data_project;

private slots:
    void on_pushButton_create_clicked();

private:
    Ui::TerrainGeneratorForm *ui;
};

#endif // TERRAINGENERATORFORM_H
