#ifndef FGEDOUBLESLIDER_H
#define FGEDOUBLESLIDER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QEvent>

#define FGE_SLIDERVALUE_NO_CLICK        0
#define FGE_SLIDERVALUE_ONE_CLICK       1
#define FGE_SLIDERVALUE_DOUBLE_CLICK    2
#define FGE_SLIDERVALUE_EDITMODE        3




class FGEDSDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    FGEDSDoubleSpinBox(QWidget *parent = nullptr);


protected:
    void focusOutEvent(QFocusEvent*pEvent);
    void leaveEvent(QEvent * event);

signals:
    void out();
};


class FGEDoubleSlider : public QSlider
{
    Q_OBJECT
public:
    FGEDoubleSlider(QWidget *parent = nullptr);
    void initValue(float);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    int behavior;
    FGEDSDoubleSpinBox *spinbox;
    bool hover;
    QPoint cursor_posistion_press;
    double current_value;
    double current_value_press;


public slots:
    void changeValue(double val);
    void finishEditing();
};
#endif // FGEDOUBLESLIDER_H
