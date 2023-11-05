#ifndef FGEANIMATIONSELECTIONFORM_H
#define FGEANIMATIONSELECTIONFORM_H

#include <QWidget>
#include <QDebug>
#include <StructData/FGEDataProject.h>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>
#include <TimeLine/FGEAnimationDelegateLIA.h>
#include <TimeLine/FGEAnimationTimeLineApplied.h>

class __FGESelected{
public:
    __FGESelected(){
        this->animation = NULL;
        this->item = NULL;
    }
    void set(FGEDataAnimation *animation, QListWidgetItem *item){
        this->animation = animation;
        this->item = item;
    }
    FGEDataAnimation * getAnimation(){
        return this->animation;
    }
    QListWidgetItem * getItem(){
        return this->item;
    }

    FGEDataAnimation *animation;
    QListWidgetItem *item;
};

namespace Ui {
class FGEAnimationSelectionForm;
}

class FGEAnimationSelectionForm : public QWidget
{
    Q_OBJECT

public:
    explicit FGEAnimationSelectionForm(QWidget *parent = 0);
    ~FGEAnimationSelectionForm();


    void init(FGEDataProject *data_struct, FGEAnimationTimeLineApplied *applied_animation);
    void updateChannelsListWidget(FGEDataAnimation *animation);
    QListWidgetItem* getItemFromAnimation(FGEDataAnimation *animation);


    FGEDataProject *data_struct;
    FGEDataChannel *cut_channel;
    FGEDataAnimation *cut_anim;
    __FGESelected selected;
    FGEAnimationTimeLineApplied *applied_animation;

    QMenu *aminItemContextMenu;
    QAction* delete_this_action;
    QAction* select_this_action;
    QAction* clear_channels_action;
    QAction* add_empty_channel_action;

    QMenu *animAddContextMenu;
    QAction* saldm_add_action;
    QAction* saldm_clear_all_action;


    QMenu *channelCopyContextMenu;
    QAction* cccm_copy_action;
    QAction* cccm_cut_action;
    QAction* cccm_paste_action;
    QAction* cccm_delete_action;

private slots:
    void on_ClosePushButton_clicked();

    void on_SelectPushButton_clicked();

    void on_AnimListWidget_itemChanged(QListWidgetItem *item);

    void on_AnimListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_AddNewAnimPushButton_clicked();

    void on_AnimListWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_AnimListWidget_itemClicked(QListWidgetItem *item);

    void on_AnimListWidget_customContextMenuRequested(const QPoint &pos);

    void showAnimListItemMenu(QPoint pos, QListWidgetItem *item);

    void showAnimListVideMenu(QPoint pos);

    void showChannelsListItemMenu(QPoint pos, QListWidgetItem *item);

    void selectCurrentItemInAnimListWidget(QPoint pos, QListWidgetItem *item);

    void fgeSelectCurrentAnimation();

    void fgeDeleteAnimation();

    void fgeCutChannel();

    void fgePasteChannel();

signals:
    void updateAppliedAnimation();
private:
    Ui::FGEAnimationSelectionForm *ui;
};

#endif // FGEANIMATIONSELECTIONFORM_H
