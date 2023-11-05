#ifndef FGEANIMATIONTIMELINEFORM_H
#define FGEANIMATIONTIMELINEFORM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QMenu>
#include <QListWidgetItem>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QHeaderView>
#include <QTimer>
#include <ParseDAE/FGEParseCollada.h>

#include <TimeLine/FGETLLineForm.h>
#include <TimeLine/FGEResizingView.h>
#include <GUI/ListWidget/FGEListWidget.h>
#include <Animation/FGEAnimationFrames.h>
#include <TimeLine/FGEAnimationTimeLine.h>
//#include <Scene/FGEOpenGLWidget.h>
#include <TimeLine/FGEEditKeyframe.h>
#include <TimeLine/FGEAnimationSelectionForm.h>
#include <TimeLine/FGEAnimationTimeLineApplied.h>
#include <StructData/FGEDataProject.h>
#include <TimeLine/Form/FGEAddNewAnimationForm.h>

namespace Ui {
class FGEAnimationTimeLineForm;
}

class FGEAnimationTimeLineForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEAnimationTimeLineForm(QTimer * timer, FGETriggerFunction *trigger, FGEDataProject *sp, QString name, void *dock, QWidget *parent = 0);
    ~FGEAnimationTimeLineForm();
    //void setPipeGLWidget(FGEOpenGLWidget *widget);
    void initListView();
    void setData();
    void setDataChannel(FGEDataChannel* _channel);
    void resetAnimationListVerticalScrollBar();
    int timerPulse();
    void updatePulse();


    FGEDataProject *data_project;
    FGETriggerFunction *trigger;

    QGraphicsProxyWidget * proxy_list_widget;
    FGEAnimationTimeLine *animation_time_line;
    FGEListWidget *list_widget;
    QGraphicsScene *scene;
    FGEParseCollada *collada;
    FGEAnimationTimeLine* first_anim_time_line;
    FGEAnimationTimeLine* last_anim_time_line;
    //FGEOpenGLWidget *glwidget;
    FGEEditKeyframe *edit_keyframe;
    QTimer * timer;
    bool next_prev;
    int current_frame;
    int max_frame;

    //FGEDataAnimation *selected_animation;
    FGEAnimationTimeLineApplied *applied_animation;



private:
    Ui::FGEAnimationTimeLineForm *ui;



signals:

private slots:
    void setFrame(int frame);
    //void deleteSelected(bool st);
    void mekeSelectFromTo(bool st);
    void mekeSelectOne(bool st);
    void updateAppliedAnimation();

    void on_AnimationsTreeWidget_itemCollapsed(QTreeWidgetItem *item);
    void on_AnimationsTreeWidget_itemExpanded(QTreeWidgetItem *item);

    void resizeListWidget();

    void on_PlayPausePushButton_clicked();

    void on_ResetPushButton_clicked();

    void on_PrevPushButton_clicked();

    void on_AnimationsTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_horizontalSlider_valueChanged(int value);
    void timerSlot();

    void wheelChanged(int val);
    void addNewAnimation(bool st);
    void updateTimeLine(void *_animation);
    //void on_AnimationListVerticalScrollBar_valueChanged(int value);
    void on_AnimationsTreeWidget_collapsed(const QModelIndex &index);
    void on_AnimationsTreeWidget_expanded(const QModelIndex &index);

    void updateScrollbarFromTreeWidgetAnimation();
    void on_SelectAnimPushButton_clicked();
    void on_add_keyframe_PushButton_clicked();
};

#endif // FGEANIMATIONTIMELINEFORM_H
