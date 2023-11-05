#ifndef FGEWIDGETCLASSFORM_H
#define FGEWIDGETCLASSFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <Main/WidgetClass/FGEWidgetClass.h>

namespace Ui {
class FGEWidgetClassForm;
}

class FGEWidgetClassForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEWidgetClassForm(FGEWidgetClass *type_transform, QWidget *parent = nullptr);
    ~FGEWidgetClassForm();

    void updateModels();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;
    FGEWidgetClass *type_transform;

private slots:
    void on_pushButton_close_clicked();


private:
    Ui::FGEWidgetClassForm *ui;
};

#endif // FGEWIDGETCLASSFORM_H
