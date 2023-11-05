#ifndef FGEDOUBLESPINBOX_H
#define FGEDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QStyle>
#include <QObject>
#include <QPainterPath>
#include <QDebug>
#include <QApplication>
#include <QCursor>
#include <GUI/PushButton/FGELineEdit.h>

class FGEDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    FGEDoubleSpinBox(QWidget *parent = nullptr);
    FGELineEdit *line_edit;
public slots:
    void focusOut();
protected:
     void paintEvent(QPaintEvent *event);
     virtual void mouseMoveEvent(QMouseEvent *ev) override;
     virtual void mousePressEvent(QMouseEvent *ev) override;
     virtual void mouseReleaseEvent(QMouseEvent *ev) override;
};

#endif // FGEDOUBLESPINBOX_H
