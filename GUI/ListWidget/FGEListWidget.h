#ifndef FGELISTWIDGET_H
#define FGELISTWIDGET_H


#include <QWidget>
#include <QListWidget>
#include <QDebug>
#include <QWheelEvent>
#include <QEvent>

class FGEListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit FGEListWidget(QWidget *parent = 0);
    bool eventFilter(QObject *o, QEvent *event);

    bool mouse_left_state;
    bool mouse_drag_state;
    bool mouse_right_state;

public slots:
    void _updateEditorGeometries();

signals:
    void fgeMouseWheelEvent(int value);
    void fgeMouseWheelEvent(QPoint point);

    void fgeMousePressRightButtonEvent(QPoint point);
    void fgeMousePressLeftButtonEvent(QPoint point);

    void fgeMouseDragRightButtonEvent(QPoint point);
    void fgeMouseDragLeftButtonEvent(QPoint point);
    void fgeMouseDragEvent(QPoint point);

    void fgeMouseReleaseRightButtonEvent(QPoint point);
    void fgeMouseReleaseLeftButtonEvent(QPoint point);

    void fgeMousePressRightButtonItemEvent(QPoint point, QListWidgetItem *item);
    void fgeMouseReleaseLeftButtonItemEvent(QPoint point, QListWidgetItem *item);
    void fgeMouseReleaseLeftButtonVideEvent(QPoint point);

};

#endif // FGELISTWIDGET_H
