#ifndef FGESPLITEWIDGETFORM_H
#define FGESPLITEWIDGETFORM_H

#include <QWidget>
#include <Main/FGEPopupMenu.h>
#include <Widgets/FGESpliteWidget.h>


namespace Ui {
class FGESpliteWidgetForm;
}

class FGESpliteWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGESpliteWidgetForm(FGESpliteWidget *splite_widget,QWidget *parent = 0);
    ~FGESpliteWidgetForm();

    void updateModels();
    void _setParent(FGEPopupMenu *w);
    FGEPopupMenu *_parent;
    FGESpliteWidget *splite_widget;

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_horizontal_splite_clicked();

    void on_pushButton_vertical_splite_widget_clicked();

private:
    Ui::FGESpliteWidgetForm *ui;
};

#endif // FGESPLITEWIDGETFORM_H
