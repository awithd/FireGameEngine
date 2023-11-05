#ifndef FGERESIZINGVIEW_H
#define FGERESIZINGVIEW_H


#include <QWidget>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QDebug>
#include <QObject>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <TimeLine/FGETimeLineExtra.h>
#include <TimeLine/FGETLLineForm.h>
#include <Animation/FGEAnimationFrames.h>





class FGEResizingView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit FGEResizingView(QWidget *parent = 0);
    void setTimeLineForm(FGETLLineForm *tlwidget);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void drawHeaderTimeLine();
    void resizeEvent(QResizeEvent *event);
    void updateCursorLine(int cursor_line);
    void initCursorLine(int cursor_line);
    int getCursorLine();
    void drawCursorLine(int frame);
    int getCursorLinePixelPostion(float time);
    int pixeltoFramePostion(int x);
    int keyframeToPosition(int i);
    void drawBodyTimeLine(QTreeWidget *tree_widget, FGEDataAnimation *anim_frm);
    void drawPointIntoRow(QTreeWidget *tree_widget, FGEDataAnimation *animation, FGEDataChannel *channel, int kp);
    void doStuffWithEveryItemInMyTree(QTreeWidgetItem *item , int &ss);
    int getWidth();

    QGraphicsLineItem * itemToDraw ;
    QGraphicsItemGroup * itemHeaderTime ;
    FGETLLineForm *tlwidget;
    float cursor_line;
    bool mouse_pressed;


    FGEBorder border;
    FGEInner inner;
    int jump;
    int jump_width;


signals:
    void resizing();
    void frameChanged(int frame);

};

#endif // FGERESIZINGVIEW_H
