#ifndef FGEPOPUPMENU_H
#define FGEPOPUPMENU_H


#include <StructData/FGEDataProject.h>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QFocusEvent>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QEvent>
#include <QPushButton>
#include <QHideEvent>
#include <QShowEvent>
#include <QPalette>
#include <QGridLayout>
#include <Geometry/FGE3DGeometryPlane.h>
#include <Geometry/FGE3DGeometryBox.h>
#include <Geometry/FGE3DGeometryCylinder.h>

namespace Ui {
class FGEPopupMenu;
}

class FGEPopupMenu : public QWidget
{
    Q_OBJECT

public:
    explicit FGEPopupMenu(FGEDataProject *sp, QWidget *parent = nullptr);
    ~FGEPopupMenu();
    void addWidget(QWidget *add_mf);
    //void _setParent(FGEGL3DViewportForm *_w_parent);
    void appendDirectCudeMesh();
    void appendDirectPlan();
    void appendDirectSun();
    void initPopup(QWidget *add_mesh, QPoint _p, int w, int h);
    void startAnimation();

    QPushButton *_parent;
    QWidget *cont_widget;
    QGridLayout *_layout;
    FGEDataProject *struct_project;
    QPropertyAnimation *animation;
    int __f, __g;

signals:
    void emitUpdateGLViews();
    void createNewObject();

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;
    void showEvent(QShowEvent *e) override;
private:
    Ui::FGEPopupMenu *ui;
};



#endif // FGEPOPUPMENU_H
