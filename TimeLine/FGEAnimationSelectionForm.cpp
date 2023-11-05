#include "FGEAnimationSelectionForm.h"
#include "ui_FGEAnimationSelectionForm.h"

FGEAnimationSelectionForm::FGEAnimationSelectionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEAnimationSelectionForm)
{
    ui->setupUi(this);


    ui->AnimListWidget->setItemDelegate(new FGEAnimationDelegateLIA());
    ui->AnimListWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                    | QAbstractItemView::SelectedClicked);
    ui->AnimListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->AnimListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->AnimListWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    ui->ChannelsListWidget->setItemDelegate(new FGEAnimationDelegateLIA());
    ui->ChannelsListWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                    | QAbstractItemView::SelectedClicked);
    ui->ChannelsListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ChannelsListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->ChannelsListWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    aminItemContextMenu = new QMenu(ui->AnimListWidget);
    delete_this_action   = new QAction("Delete");
    select_this_action       = new QAction("Select");
    clear_channels_action       = new QAction("Clear");
    add_empty_channel_action    = new QAction("New empty channel");
    aminItemContextMenu->addAction(delete_this_action);
    aminItemContextMenu->addAction(select_this_action);
    aminItemContextMenu->addAction(clear_channels_action);


    animAddContextMenu = new QMenu(ui->AnimListWidget);
    saldm_add_action        = new QAction("Add");
    saldm_clear_all_action  = new QAction("Clear All");
    animAddContextMenu->addAction(saldm_add_action);
    animAddContextMenu->addAction(saldm_clear_all_action);


    channelCopyContextMenu = new QMenu(ui->ChannelsListWidget);
    cccm_copy_action        = new QAction("Copy");
    cccm_cut_action  = new QAction("Cut");
    cccm_paste_action  = new QAction("Paste");
    cccm_delete_action  = new QAction("Delete");
    channelCopyContextMenu->addAction(cccm_cut_action);
    channelCopyContextMenu->addAction(cccm_copy_action);
    channelCopyContextMenu->addAction(cccm_paste_action);
    channelCopyContextMenu->addAction(cccm_delete_action);

    //ui->AnimListWidget->viewport()->installEventFilter(ui->AnimListWidget);


    connect(ui->AnimListWidget,
            SIGNAL(fgeMousePressRightButtonItemEvent(QPoint, QListWidgetItem*)),
            this,
            SLOT(showAnimListItemMenu(QPoint, QListWidgetItem*)));

    connect(ui->AnimListWidget,
            SIGNAL(fgeMouseReleaseLeftButtonItemEvent(QPoint,QListWidgetItem*)),
            this,
            SLOT(selectCurrentItemInAnimListWidget(QPoint, QListWidgetItem*)));

    connect(ui->AnimListWidget,
            SIGNAL(fgeMousePressRightButtonEvent(QPoint)),
            this,
            SLOT(showAnimListVideMenu(QPoint)));


    //////////
    ///
    connect(ui->ChannelsListWidget,
            SIGNAL(fgeMousePressRightButtonItemEvent(QPoint, QListWidgetItem*)),
            this,
            SLOT(showChannelsListItemMenu(QPoint, QListWidgetItem*)));

    // WHEN SELECTED ANIMATION
    connect(this->select_this_action,
            SIGNAL(triggered()),
            this,
            SLOT(fgeSelectCurrentAnimation()));
    connect(this->delete_this_action,
            SIGNAL(triggered()),
            this,
            SLOT(fgeDeleteAnimation()));

    // WHEN SELECTED CHANNEL
    connect(this->cccm_cut_action,
            SIGNAL(triggered()),
            this,
            SLOT(fgeCutChannel()));
    connect(this->cccm_paste_action,
            SIGNAL(triggered()),
            this,
            SLOT(fgePasteChannel()));
    //ui->AnimListWidget->addActions({ delete_this_action, select_this_action });
}

FGEAnimationSelectionForm::~FGEAnimationSelectionForm()
{
    delete ui;
}

/*void FGEAnimationSelectionForm::seteApllied(FGEDataAnimation *animation)
{
    this->applied.set(animation, );
}*/

void FGEAnimationSelectionForm::init(FGEDataProject *data_struct, FGEAnimationTimeLineApplied *applied_animation)
{
    this->data_struct = data_struct;
    this->applied_animation = applied_animation;

    qDebug() << "s 1 : ";

    FGEDataAnimation *anim = this->data_struct->first_animation;
    int i=0;
    while(anim!=NULL){
        qDebug() << "s 2 : ";
        QListWidgetItem * _anim = new QListWidgetItem(anim->name);
        //_anim->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
        _anim->setFlags(_anim->flags() | Qt::ItemIsUserCheckable);
        _anim->setCheckState(Qt::Checked);
        _anim->setSizeHint(QSize(100, 30));
        QVariant data(anim->id);
        _anim->setData(Qt::UserRole, data);
qDebug() << "s 3 : ";
        if(this->applied_animation->getAnimation()==anim){
            this->selected.set(this->applied_animation->getAnimation(), _anim);
        }
qDebug() << "s 4 : ";
        /*QWidget *wid = new QWidget();
        wid->setAttribute(Qt::WA_TranslucentBackground);
        QLabel *lab = new QLabel(wid);
        lab->setAttribute(Qt::WA_TranslucentBackground);
        lab->setText(anim->name);
        lab->setGeometry(37,5,100,20);
        QPushButton *button_remove = new QPushButton(wid);
        QPixmap pixmap(":/Icons/window_close.svg");
        QIcon ButtonIcon(pixmap);
        button_remove->setIcon(ButtonIcon);
        button_remove->setIconSize(QSize(12, 12));
        button_remove->setMaximumSize(20, 20);
        button_remove->setMinimumSize(20, 20);
        button_remove->setGeometry(5,5,20,20);
        button_remove->setStyleSheet(
                    "background-color: white;"
                    "border: 1px solid white;"  //outline
                    "border-radius: 9px;"     //corners
                    );
*/
        ui->AnimListWidget->insertItem(i, _anim);
        qDebug() << "s 5 : ";
        //ui->AnimListWidget->setItemWidget(_anim, wid);

        //ui->AnimComboBox->insertItem(i, anim->name, QVariant(anim->id));
        i++;

        anim=anim->next;
    }
}

void FGEAnimationSelectionForm::on_ClosePushButton_clicked()
{
    this->deleteLater();
}

void FGEAnimationSelectionForm::on_SelectPushButton_clicked()
{
    /*if(this->selected_animation!=NULL){
        qDebug() << "on_SelectPushButton_clicked : ";

        emit this->changeAnimation(this->selected_animation);
        this->deleteLater();
    }*/
}

void FGEAnimationSelectionForm::on_AnimListWidget_itemChanged(QListWidgetItem *item)
{
    qDebug() << "on_AnimListWidget_itemChanged : "<<item->text();

    /*ui->AnimListWidget->clear();
    int i=0;

    FGEDataAnimation *anim = this->data_struct->first_animation;
    while(anim!=NULL){
        qDebug() << "anim->id : "<<anim->id;
        QVariant v = item->data(Qt::UserRole);
        if(v.toInt()==anim->id){
            this->selected_animation = anim;
            FGEDataChannel *channel = anim->first_channel;
            int i=0;
            while(channel!=NULL){
                QListWidgetItem * _channel = new QListWidgetItem();
                //_anim->setFlags(anim->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
                _channel->setText(channel->name);
                _channel->setSizeHint(QSize(100, 30));
                ui->ChannelsListWidget->insertItem(channel->id, _channel);
                channel = channel->next;
                i++;
            }
            ui->ChannelCountLabel->setText(QString::number(i));
            ui->ErrorLabel->setText(QString("NO ERRORS.."));

            anim=NULL;
        }else{
            anim=anim->next;
        }

    }*/
}

void FGEAnimationSelectionForm::on_AnimListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
/*    ui->ChannelsListWidget->clear();
    int i=0;

    FGEDataAnimation *anim = this->data_struct->first_animation;
    while(anim!=NULL){
        qDebug() << "anim->id : "<<anim->id;
        QVariant v = current->data(Qt::UserRole);
        qDebug() << "v.toInt() : "<<v.toInt();
        if(v.toInt()==anim->id){
            this->selected_animation = anim;
            FGEDataChannel *channel = anim->first_channel;
            int i=0;
            while(channel!=NULL){
                QListWidgetItem * _channel = new QListWidgetItem();
                //_anim->setFlags(anim->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
                _channel->setSizeHint(QSize(100, 30));

                QWidget *wid = new QWidget();
                wid->setAttribute(Qt::WA_TranslucentBackground);
                QLabel *lab = new QLabel(wid);
                lab->setAttribute(Qt::WA_TranslucentBackground);
                lab->setText(channel->name);
                lab->setGeometry(37,5,100,20);

                QPushButton *button_remove = new QPushButton(wid);
                QPixmap pixmap(":/Icons/window_close.svg");
                QIcon ButtonIcon(pixmap);
                button_remove->setIcon(ButtonIcon);
                button_remove->setIconSize(QSize(12, 12));
                button_remove->setMaximumSize(20, 20);
                button_remove->setMinimumSize(20, 20);
                button_remove->setGeometry(5,5,20,20);
                button_remove->setStyleSheet(
                            "background-color: white;"
                            "border: 1px solid white;"  //outline
                            "border-radius: 9px;"     //corners
                            );

                ui->ChannelsListWidget->insertItem(i, _channel);
                ui->ChannelsListWidget->setItemWidget(_channel, wid);

                channel = channel->next;
                i++;
            }
            ui->ChannelCountLabel->setText(QString::number(i));
            ui->ErrorLabel->setText(QString("NO ERRORS.."));

            anim=NULL;
        }else{
            anim=anim->next;
        }

    }*/
}

void FGEAnimationSelectionForm::on_AddNewAnimPushButton_clicked()
{

}

void FGEAnimationSelectionForm::on_AnimListWidget_itemDoubleClicked(QListWidgetItem *item)
{
   item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void FGEAnimationSelectionForm::on_AnimListWidget_itemClicked(QListWidgetItem *item)
{


}

void FGEAnimationSelectionForm::showAnimListItemMenu(QPoint pos, QListWidgetItem *item)
{
    if(item==ui->AnimListWidget->currentItem()){
        QAction *selected = aminItemContextMenu->exec(QCursor::pos());
    }
}

void FGEAnimationSelectionForm::showChannelsListItemMenu(QPoint pos, QListWidgetItem *item)
{
    if(item==ui->ChannelsListWidget->currentItem()){
        if(this->cut_channel==NULL){
            cccm_paste_action->setDisabled(true);
        }else{
            cccm_paste_action->setDisabled(false);
        }
        QAction *selected = channelCopyContextMenu->exec(QCursor::pos());
    }
}

void FGEAnimationSelectionForm::showAnimListVideMenu(QPoint pos)
{
    QAction *selected = animAddContextMenu->exec(QCursor::pos());

}

void FGEAnimationSelectionForm::selectCurrentItemInAnimListWidget(QPoint pos, QListWidgetItem *item)
{
    FGEDataAnimation *anim = this->data_struct->first_animation;
    while(anim!=NULL){
        QVariant v = item->data(Qt::UserRole);
        if(v.toInt()==anim->id){
            this->selected.set(anim, item);
            ui->AnimListWidget->setCurrentItem(item);
            this->updateChannelsListWidget(anim);
            anim=NULL;
        }else{
            anim=anim->next;
        }
    }
}

void FGEAnimationSelectionForm::on_AnimListWidget_customContextMenuRequested(const QPoint &pos)
{        qDebug() << "on_AnimListWidget_customContextMenuRequested : "<<pos;

    QAction *selected = aminItemContextMenu->exec(mapToGlobal(pos));
}

void FGEAnimationSelectionForm::fgeSelectCurrentAnimation()
{
    if(this->selected.getAnimation()!=NULL){
        this->applied_animation->getAnimation()->clearPrepare();
        this->applied_animation->setAnimation(this->selected.getAnimation());

        this->applied_animation->getAnimation()->clearPrepare();
        this->applied_animation->getAnimation()->prepare(0.0416666);

        emit this->updateAppliedAnimation();
    }
}

void FGEAnimationSelectionForm::fgeDeleteAnimation()
{
    if(this->selected.getAnimation()!=NULL){
        if(this->selected.getAnimation()==this->applied_animation->getAnimation()){
            this->applied_animation->setAnimation(NULL);
            emit this->updateAppliedAnimation();

        }

        this->data_struct->deleteAnimation(this->selected.getAnimation());

        ui->AnimListWidget->removeItemWidget(this->selected.getItem());
        delete this->selected.getItem();

        ui->ChannelsListWidget->clear();

        this->selected.set(NULL, NULL);
    }
}

void FGEAnimationSelectionForm::updateChannelsListWidget(FGEDataAnimation *animation)
{
    ui->ChannelsListWidget->clear();

    FGEDataChannel *channel = animation->first_channel;
    int i=0;
    while(channel!=NULL){
        QListWidgetItem * _channel = new QListWidgetItem();
        //_anim->setFlags(anim->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        _channel->setSizeHint(QSize(100, 30));
        QVariant data(channel->id);
        _channel->setData(Qt::UserRole, data);

        QWidget *wid = new QWidget();
        wid->setAttribute(Qt::WA_TranslucentBackground);
        QLabel *lab = new QLabel(wid);
        lab->setAttribute(Qt::WA_TranslucentBackground);
        lab->setText(channel->name);
        lab->setGeometry(37,5,100,20);

        QPushButton *button_remove = new QPushButton(wid);
        QPixmap pixmap(":/Icons/window_close.svg");
        QIcon ButtonIcon(pixmap);
        button_remove->setIcon(ButtonIcon);
        button_remove->setIconSize(QSize(12, 12));
        button_remove->setMaximumSize(20, 20);
        button_remove->setMinimumSize(20, 20);
        button_remove->setGeometry(5,5,20,20);
        button_remove->setStyleSheet(
                    "background-color: white;"
                    "border: 1px solid white;"  //outline
                    "border-radius: 9px;"     //corners
                    );

        ui->ChannelsListWidget->insertItem(i, _channel);
        ui->ChannelsListWidget->setItemWidget(_channel, wid);

        channel = channel->next;
        i++;
    }
    ui->ChannelCountLabel->setText(QString::number(i));
    ui->ErrorLabel->setText(QString("NO ERRORS.."));
}

QListWidgetItem* FGEAnimationSelectionForm::getItemFromAnimation(FGEDataAnimation *animation)
{
    for(int i = 0; i < ui->AnimListWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->AnimListWidget->item(i);
        QVariant v = item->data(Qt::UserRole);
        if(v.toInt()==animation->id){
            return item;
        }
    }







}

void FGEAnimationSelectionForm::fgeCutChannel()
{
    QListWidgetItem *cha_itm = ui->ChannelsListWidget->currentItem();
    if(cha_itm!=NULL){
        QVariant v = cha_itm->data(Qt::UserRole);
        qDebug() << "fgeCutChannel : v.toInt() "<<v.toInt();

        FGEDataAnimation * anim = this->selected.getAnimation();
        if(anim!=NULL){
            FGEDataChannel *channel = anim->first_channel;
            while(channel!=NULL){
                qDebug() << "channel->id : "<<channel->id;
                if(v.toInt()==channel->id){
                    this->cut_channel = channel;
                    this->cut_anim = anim;
                    qDebug() << "Cut Channel : "<<channel->name;
                    return;
                }
                channel=channel->next;
            }
        }

    }
    this->cut_channel = NULL;
}

void FGEAnimationSelectionForm::fgePasteChannel()
{
    /*FGEDataAnimation * anim = this->selected.getAnimation();
    if(anim!=NULL){
        qDebug() << "Paste Channel : "<<this->cut_channel->name;
        //FGEDataSimple * s = (FGEDataSimple *)this->cut_channel->source;
        s->animation = this->cut_anim;
        this->cut_anim->unlinkChannel(this->cut_channel);
        anim->appendChannel(this->cut_channel);
        anim->clearPrepare();
        anim->prepare(0.0416666);
    }
    this->cut_channel = NULL;*/
}
