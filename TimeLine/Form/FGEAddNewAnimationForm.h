#ifndef FGEADDNEWANIMATIONFORM_H
#define FGEADDNEWANIMATIONFORM_H

#include <QWidget>
#include <StructData/FGEDataProject.h>

namespace Ui {
class FGEAddNewAnimationForm;
}

class FGEAddNewAnimationForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEAddNewAnimationForm(FGETriggerFunction *trigger, FGEDataProject *sp, QWidget *parent = nullptr);
    ~FGEAddNewAnimationForm();
    FGETriggerFunction *trigger;
    FGEDataProject *sp;
private slots:
    void on_create_animation_pushButton_clicked();

private:
    Ui::FGEAddNewAnimationForm *ui;
};

#endif // FGEADDNEWANIMATIONFORM_H
