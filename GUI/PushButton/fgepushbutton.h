#ifndef FGEPUSHBUTTON_H
#define FGEPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QKeyEvent>
#include <QIntValidator>
#include <GUI/PushButton/FGEDoubleSpinBox.h>

class FGEPushButton : public QWidget
{
    Q_OBJECT
public:
    explicit
    FGEPushButton(QString name, QWidget *parent = nullptr);

    FGEDoubleSpinBox *line_edit;

    bool pressed;
    bool hover_left, hover_midle, hover_right, slide, hover;
    double value;
    bool dsb_mode;
    int x_dir;
    int grow_value;
    bool grow_sign;
    QString name;

public slots:
    void editingFinished();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);
    virtual bool eventFilter(QObject *obj, QEvent *ev);
};

#endif // FGEPUSHBUTTON_H
