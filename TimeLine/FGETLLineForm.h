#ifndef FGETLLINEFORM_H
#define FGETLLINEFORM_H

#include <QWidget>

#include <QMainWindow>
#include <QScrollBar>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>

#include <TimeLine/CursorLine.h>
#include <TimeLine/FGETimeLineWidget.h>
#include <TimeLine/FGEItemTimeLine.h>
#include <TimeLine/FGEAnimationTimeLine.h>


namespace Ui {
class FGETLLineForm;
}

class FGETLLineForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGETLLineForm(QWidget *parent = 0);
    ~FGETLLineForm();
    void init(FGEAnimationTimeLine &animation);
    void updateListWidgetEditorGeometries();
    QListWidget * getListWidet();
    QWidget * getoooo();

signals:
    void __updateListWidgetEditorGeometries();

private:
    Ui::FGETLLineForm *ui;
};

#endif // FGETLLINEFORM_H
