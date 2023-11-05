#ifndef FGEITEMTIMELINE_H
#define FGEITEMTIMELINE_H

#include <QWidget>
#include <QPainter>
#include <QObject>
#include <QPaintEvent>
#include <QPoint>
#include <QApplication>
#include <TimeLine/FGETimeLineExtra.h>
#include <StructData/FGEDataStructAnimation.h>
#include <Animation/FGEAnimationFrames.h>
#include <CSS/FGEInner.h>
#include <CSS/FGEBorder.h>
#include <TimeLine/FGEEditKeyframe.h>
#include <TimeLine/DataAnim/FGEDataAnimAnimation.h>
#include <QPushButton>
#define FGE_TIMELINE_SELECTION_NORMAL   0
#define FGE_TIMELINE_SELECTION_FROMTO   1

class FGEItemTimeLine : public QWidget
{

    Q_OBJECT

public:
    explicit FGEItemTimeLine(
            FGEEditKeyframe         *edit_keyframe,
            FGEDataChannel          *channel,
            FGEDataAnimation    *_keyframe,
            QWidget                 *parent = nullptr);


    int getCursorLinePixelPostion(float time);
    ~FGEItemTimeLine();

    //FGEItemTimeLine(QPoint from, QPoint to);
    void moveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);
    bool selectFromT(int to);


    FGEDataAnimation *_keyframe;
    FGEDataChannel* channel;
    FGEDataAnimation *animation;
    QPoint fromPoint;
    QPoint toPoint;
    FGEEditKeyframe *edit_keyframe;

    FGEBorder border;
    FGEInner inner;
    int jump;
    int jump_width;

    int draw_mode;
    QVector<int> selected;
    int mode_selection;

public slots:
    void deleteSelected();

};

#endif // FGEITEMTIMELINE_H
