#include "FGEAnimationTimeLineForm.h"
#include "ui_FGEAnimationTimeLineForm.h"

FGEAnimationTimeLineForm::FGEAnimationTimeLineForm(QTimer * timer, FGETriggerFunction *trigger, FGEDataProject *sp, QString name, void *dock, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEAnimationTimeLineForm)
{
    ui->setupUi(this);

    this->data_project = sp;
    this->trigger = trigger;

    this->next_prev = false;
    //this->current_frame = 0;
    //this->timer = timer;
    //this->glwidget = NULL;

    this->animation_time_line = new FGEAnimationTimeLine();

    this->applied_animation = new FGEAnimationTimeLineApplied();
    this->applied_animation->setAnimation(this->data_project->first_animation);

    this->edit_keyframe = new FGEEditKeyframe(NULL);


    qDebug() <<"oh h";
    //this->max_width_time_line = 0;
    this->initListView();

    ///this->setData();

    //this->list_widget->setMinimumWidth(this->max_width_time_line);
    //tlwidget->setMaximumWidth(this->max_width_time_line);

    //tlwidget->updateGeometry();

    //ui->graphicsView->setWidget(tlwidget);

    //OverlayFactoryFilter *factory = new OverlayFactoryFilter(tlwidget->getoooo());
    //tlwidget->getoooo()->installEventFilter(factory);

    //ui->widget->setAcceptDrops(true);


    QScrollBar *list_widget_scrollbar = this->list_widget->verticalScrollBar();
    QScrollBar *tree_widget_scrollbar = ui->AnimationsTreeWidget->verticalScrollBar();
    ui->AnimationsTreeWidget->setAutoScroll(false);


    ui->AnimationListVerticalScrollBar->setValue(tree_widget_scrollbar->value());
    ui->AnimationListVerticalScrollBar->setMaximum(tree_widget_scrollbar->maximum());
    ui->AnimationListVerticalScrollBar->setMinimum(tree_widget_scrollbar->minimum());
    ui->AnimationListVerticalScrollBar->setPageStep(tree_widget_scrollbar->pageStep());


    connect(ui->AnimationListVerticalScrollBar, &QScrollBar::valueChanged,
                [=](int aSliderPosition){
        qDebug() << "  -----valueChanged : ";

                                            tree_widget_scrollbar->setValue(aSliderPosition);
                                            list_widget_scrollbar->setValue(aSliderPosition);
                                            //tlwidget->updateListWidgetEditorGeometries();
                                            this->list_widget->_updateEditorGeometries();
                                            //_currentSliderValue = aSliderPosition;
                                         //
                });

    /*connect(ui->AnimationListVerticalScrollBar, &QScrollBar::sliderMoved,
                [=](int aSliderPosition){
                                            qDebug() << "aSliderPosition : " <<aSliderPosition;
                                            lValueScrollBar1->setValue(aSliderPosition);
                                            lValueScrollBar2->setValue(aSliderPosition);
                                            //tlwidget->updateListWidgetEditorGeometries();
                                            tlwidget->updateListWidgetEditorGeometries();
                                            //_currentSliderValue = aSliderPosition;
                                         //
                });
*/

    connect(tree_widget_scrollbar, SIGNAL(valueChanged(int)), this, SLOT(updateScrollbarFromTreeWidgetAnimation()));
    //connect(list_widget_scrollbar, SIGNAL(rangeChanged()), this, SLOT(updateScrollbarFromTreeWidgetAnimation()));

    connect(ui->graphicsView, SIGNAL(resizing()), this, SLOT(resizeListWidget()));
    connect(ui->AnimationsTreeWidget, &FGEAnimationTreeView::wheelChanged, this, &FGEAnimationTimeLineForm::wheelChanged);

    connect(ui->graphicsView, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
    connect(this->trigger, SIGNAL(__updateAllTimeLine(void*)), this, SLOT(updateTimeLine(void*)));

    /*connect(ui->AnimationsTreeWidget->verticalScrollBar(), SIGNAL(valueChanged(int)),
    this, SLOT(scrollBarChanged(int)));*/

    /*connect(ui->AnimationsTreeWidget->verticalScrollBar(), SIGNAL(valueChanged(int)),
            tlwidget->getListWidet(), SLOT(updateEditorGeometries()));*/


/*
    timer = new QTimer(this);

    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

*/

    //w_htl = ui->graphicsView->sceneRect().width();

    ui->graphicsView->drawHeaderTimeLine();
    ui->graphicsView->drawBodyTimeLine(ui->AnimationsTreeWidget, this->data_project->first_animation);
    qDebug() << "vb : ";

    ui->ABSplitter->setSizes({1000, 3000});

    ///this->current_frame = ui->BeginFrameSpinBox->value();

    //ui->widget->setCurrentFrame(0);


    //QPixmap newpix("new.png");

    QMenuBar *menu_bar = new QMenuBar(this);
    //QFont font = menu_bar->font();
    //font.setPointSize(11);
    //menu_bar->setFont(font);
    menu_bar->setMinimumWidth(200);
    menu_bar->setGeometry(QRect(0, 0, 200, 28));

    QMenu *file_menu = menu_bar->addMenu("File");
    //font = file_menu->font();
    //font.setPointSize(10);
    //file_menu->setFont(font);
    file_menu->setMinimumWidth(100);

    auto *add_new_animation_action = new QAction("&Add New Animation", this);
    file_menu->addAction(add_new_animation_action);



    QMenu *edit_menu = menu_bar->addMenu("Edit");
    //font = edit_menu->font();
    //font.setPointSize(10);
    //edit_menu->setFont(font);
    edit_menu->setMinimumWidth(100);

    auto *_slcft = new QAction("&Select from:to", this);
    auto *_slco = new QAction("&Select One", this);
    auto *_delete_selected = new QAction("&Delete selected", this);
    auto *_copy_selected = new QAction("&Copy selected", this);
    edit_menu->addAction(_slcft);
    edit_menu->addAction(_slco);
    edit_menu->addAction(_delete_selected);
    edit_menu->addAction(_copy_selected);


    QHBoxLayout* vbox = new QHBoxLayout(ui->widget_3);
    vbox->setMenuBar(menu_bar);
    ui->widget_3->setLayout(vbox);


    ui->widget_3->setMinimumWidth(menu_bar->width());


    /*QGridLayout *gridLayout = new QGridLayout(ui->widget_3);
    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(menu_bar, 0, 0, menu_bar->width(), 28);
    //QHBoxLayout* vbox = new QHBoxLayout(ui->widget_3);*/

    //ui->widget_3->setLayout(vbox);
    //vbox->setMenuBar(menu_bar);


    //ui->widget_3->setMinimumWidth(menu_bar->width());
    //connect(_delete_selected, SIGNAL(triggered(bool)), this, SLOT(deleteSelected(bool)));
    connect(_slcft, SIGNAL(triggered(bool)), this, SLOT(mekeSelectFromTo(bool)));
    connect(_slco, SIGNAL(triggered(bool)), this, SLOT(mekeSelectOne(bool)));
    connect(add_new_animation_action, SIGNAL(triggered(bool)), this, SLOT(addNewAnimation(bool)));

/*
    ui->AnimationsTreeWidget->setProperty("highlightHeader", true);
    ui->AnimationsTreeWidget->setStyleSheet("QHeaderView::section { background-color:red }");

    QTreeWidgetItem *header = ui->AnimationsTreeWidget->headerItem();
    header->setBackgroundColor(0, Qt::green);
    header->setForeground(0, QBrush(Qt::green));*/

}

FGEAnimationTimeLineForm::~FGEAnimationTimeLineForm()
{
    delete ui;
}

void FGEAnimationTimeLineForm::updateTimeLine(void* _animation)
{
    FGEDataAnimation *__animation = (FGEDataAnimation *)_animation;
    this->applied_animation->setAnimation(__animation);
    QHeaderViewR * hvr = (QHeaderViewR *) ui->AnimationsTreeWidget->header();
    hvr->updateTitle(0, __animation->name);
    setData();
    qDebug() << "__animation->name : "<<__animation->name;

    connect(__animation->timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    //this->initListView();
    /*this->setData();*/
}

void FGEAnimationTimeLineForm::timerSlot()
{
    this->updatePulse();
    this->timerPulse();
    qDebug() << "timerSlot... : ^";
    this->trigger->updateAllWIdgetsOpenGl();
}

void FGEAnimationTimeLineForm::addNewAnimation(bool st)
{
    FGEAddNewAnimationForm *new_anim = new FGEAddNewAnimationForm(this->trigger, this->data_project);
    new_anim->show();
}

void FGEAnimationTimeLineForm::wheelChanged(int val)
{
    qDebug() << "--wheelChanged : ";

    ui->AnimationListVerticalScrollBar->setValue(ui->AnimationListVerticalScrollBar->value()+val);
}

void FGEAnimationTimeLineForm::initListView()
{
    //qDebug() << "....................................000000000000000 : " <<this->data_project->first_animation->last_kf;
    //cursor_line = 0;

    //this->next_prev = false;
    qDebug() <<"oh d : "<<ui->graphicsView;
    ui->graphicsView->inner.setWidth(20*ui->graphicsView->jump_width);

    this->scene = new QGraphicsScene();

    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->setScene(this->scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setRenderHint((QPainter::Antialiasing));

    this->list_widget = new FGEListWidget();
    this->list_widget->setStyleSheet("show-decoration-selected: 1;"
                            "border: 0px solid #d9d9d9;"
                            "background-color: rgb(255, 255, 255);");

    this->list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->list_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView->setSceneRect(this->frameGeometry()); // set the scene's bounding rect to rect of mainwindow
    //this->list_widget->setMinimumWidth(600);
    this->list_widget->setMinimumHeight(ui->AnimationsTreeWidget->minimumHeight());
    this->list_widget->setMaximumHeight(ui->AnimationsTreeWidget->maximumHeight());

    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );


    /*QRect rec = ui->graphicsView->rect();
    rec.setWidth(1000);
    scene->setSceneRect(rec);*/
    //QRect rec = tlwidget->getListWidet()->geometry();
    //rec.setY(50);
    //tlwidget->getListWidet()->setGeometry(rec);
    //proxy = new QGraphicsProxyWidget();
    //
    //ui->graphicsView->setTimeLineForm(tlwidget);
    //proxy->setWidget(tlwidget);
    //proxy->setOpacity(0.999999);



    this->proxy_list_widget = scene->addWidget(this->list_widget);
    this->proxy_list_widget->setPos(0, 40);
    this->proxy_list_widget->setFlag(QGraphicsItem::ItemIsMovable,false);

    this->proxy_list_widget->setMinimumWidth(ui->graphicsView->getWidth());

    /*QWidget *wd = new QWidget();
    wd->setGeometry(0, 0, scene->width(), 40);
    QGraphicsProxyWidget *w_proxy = scene->addWidget(wd);*/

    //proxy->setFlag(QGraphicsItem::ItemIsSelectable,true);

qDebug() << "--aaa : ";

}


void FGEAnimationTimeLineForm::on_AnimationsTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QVariant _v = current->data(0, Qt::UserRole);
    for(int i = 0; i < this->list_widget->count(); ++i)
    {
        QListWidgetItem* item = this->list_widget->item(i);
        QVariant v = item->data(Qt::UserRole);
        if(v.toInt()==_v.toInt()){
            //item->setSelected(true);
            this->list_widget->setCurrentItem(item);
        }
    }

/*
    while(p!=NULL){
        ////qDebug() << " p->item : "<<p->id;
        //p->item->setText(0, "hxh");
        if(p->id==current->data(0, Qt::UserRole).toInt()){
            p->litem->setSelected(true);
            return;
        }
        for(int i=0; i<p->actions.size(); i++){
            FGEActionTimeLine *_time = p->actions.at(i);
            if(_time->id==current->data(0, Qt::UserRole).toInt()){
                _time->litem->setSelected(true);
                return;
            }
        }
        p=p->next;
    }
*/
}

void FGEAnimationTimeLineForm::on_horizontalSlider_valueChanged(int value)
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    anim->timer->setInterval(value*10);
}

void FGEAnimationTimeLineForm::setFrame(int frame){
    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    if(anim!=NULL){
        anim->current_frame = frame;
        anim->play = true;
        this->trigger->updateAllWIdgetsOpenGl();
    }
    /*if(this->glwidget!=NULL) {
        this->glwidget->lanch(this->current_frame);
    }*/
}

/*
void MainWindow::on_AnimationListVerticalScrollBar_valueChanged(int value)
{
    //tlwidget->getListWidet()->verticalScrollBar()->setValue(value);
    //tlwidget->updateListWidgetEditorGeometries();

    //int _currentSliderValue = 0;

}*/


void FGEAnimationTimeLineForm::on_AnimationsTreeWidget_collapsed(const QModelIndex &index)
{
    // tested
    qDebug() << "  -----collapsed : ";
    this->resetAnimationListVerticalScrollBar();
}


void FGEAnimationTimeLineForm::on_AnimationsTreeWidget_expanded(const QModelIndex &index)
{
    // tested
    qDebug() << "  -----expanded : ";
    this->resetAnimationListVerticalScrollBar();
}

void FGEAnimationTimeLineForm::updateScrollbarFromTreeWidgetAnimation()
{
    // tested
    qDebug() << "  -----crollb : ";
    this->resetAnimationListVerticalScrollBar();
}

void FGEAnimationTimeLineForm::resizeListWidget()
{
    // tested

    this->list_widget->setMinimumHeight(ui->AnimationsTreeWidget->height());
    this->list_widget->setMaximumHeight(ui->AnimationsTreeWidget->height());

    ui->graphicsView->setSceneRect(0, 0, this->list_widget->width(), this->list_widget->height());

    this->resetAnimationListVerticalScrollBar();

    ui->graphicsView->scene()->update();
    ui->graphicsView->update();

}

void FGEAnimationTimeLineForm::resetAnimationListVerticalScrollBar()
{
    // tested
    QScrollBar *ScrollBar = ui->AnimationsTreeWidget->verticalScrollBar();
    ui->AnimationListVerticalScrollBar->setValue(ScrollBar->value());
    ui->AnimationListVerticalScrollBar->setMaximum(ScrollBar->maximum());
    ui->AnimationListVerticalScrollBar->setMinimum(ScrollBar->minimum());
    ui->AnimationListVerticalScrollBar->setPageStep(ScrollBar->pageStep());

}


void FGEAnimationTimeLineForm::setDataChannel(FGEDataChannel* channel)
{

    for(int i=0; i<this->animation_time_line->actions.size(); i++){
        FGEActionTimeLine * action = this->animation_time_line->actions.at(i);
        if(action->channel==(void*)channel){
            action->kesyframes->deleteLater();
            action->kesyframes = new FGEItemTimeLine(this->edit_keyframe,
                                                     channel,
                                                     this->applied_animation->getAnimation(),
                                                     this->list_widget);
            action->kesyframes->setStyleSheet("background-color:#4C4C4C02;");
            this->list_widget->setItemWidget(action->litem, action->kesyframes);

        }
    }
/*
    QListWidget * _list_widget = this->list_widget;
    //QTreeWidget * _list_channels_widget = ui->AnimationsTreeWidget;

    FGEActionTimeLine *action = new FGEActionTimeLine();
    action->id = channel->id;
    action->name = channel->name;
    action->channel = channel;
    action->kesyframes = new FGEItemTimeLine(this->edit_keyframe,
                                             channel,
                                             this->applied_animation->getAnimation(),
                                             _list_widget);
    /*if(action->kesyframes->width()>this->max_width_time_line){
        this->max_width_time_line = action->kesyframes->width();
    }*/
    /*action->litem = new QListWidgetItem();
    QVariant __data(channel->id);
    action->litem->setData(Qt::UserRole, __data);
    action->litem->setSizeHint(QSize(600, 30));

    _list_widget->addItem(action->litem);
    _list_widget->setItemWidget(action->litem, action->kesyframes);*/

/*
    QWidget *wid = new QWidget();
    QPushButton *button_play = new QPushButton("P", wid);
    button_play->setMaximumSize(20, 20);
    button_play->setMinimumSize(20, 20);
    button_play->setGeometry(5,5,20,20);
    QPushButton *button_fix = new QPushButton("P", wid);
    button_fix->setMaximumSize(20, 20);
    button_fix->setMinimumSize(20, 20);
    button_fix->setGeometry(27,5,20,20);


    action->item = new QTreeWidgetItem();
    action->item->setFlags(action->item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    action->item->setCheckState(0, Qt::Checked);
    action->item->setText(0, action->name);
    action->item->setSizeHint(0, QSize(100, 30));
    QVariant data(channel->id);
    action->item->setData(0, Qt::UserRole, data);
    channel->help = (void*) action->item;


    _list_channels_widget->insertTopLevelItem(channel->id, action->item);
    _list_channels_widget->setItemWidget(action->item, 1, wid);*/

}

void FGEAnimationTimeLineForm::setData()
{
    QListWidget * _list_widget = this->list_widget;
    QTreeWidget * _list_channels_widget = ui->AnimationsTreeWidget;
    int iii=0;

    _list_widget->clear();
    _list_channels_widget->clear();

    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    if(anim!=NULL){
        FGEDataChannel* channel = anim->first_channel;
        while(channel!=NULL){
            FGEActionTimeLine *action = new FGEActionTimeLine();
            action->id = channel->id;
            action->name = channel->name;
            action->channel = (void*)channel;

            action->kesyframes = new FGEItemTimeLine(this->edit_keyframe,
                                                     channel,
                                                     anim,
                                                     _list_widget);
            /*if(action->kesyframes->width()>this->max_width_time_line){
                this->max_width_time_line = action->kesyframes->width();
            }*/
            action->kesyframes->setStyleSheet("background-color:#4C4C4C02;");
            action->litem = new QListWidgetItem();

            QVariant vptr = QVariant::fromValue(action);

            //QVariant __data(channel->id);
            action->litem->setData(Qt::UserRole, vptr);
            action->litem->setSizeHint(QSize(600, 30));

            _list_widget->addItem(action->litem);
            _list_widget->setItemWidget(action->litem, action->kesyframes);

            QWidget *wid = new QWidget();
            QPushButton *button_play = new QPushButton("P", wid);
            button_play->setMaximumSize(20, 20);
            button_play->setMinimumSize(20, 20);
            button_play->setGeometry(5,5,20,20);
            QPushButton *button_fix = new QPushButton("P", wid);
            button_fix->setMaximumSize(20, 20);
            button_fix->setMinimumSize(20, 20);
            button_fix->setGeometry(27,5,20,20);


            action->item = new QTreeWidgetItem();
            action->item->setFlags(action->item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
            action->item->setCheckState(0, Qt::Checked);
            action->item->setText(0, action->name);
            action->item->setSizeHint(0, QSize(100, 30));
            QVariant data(channel->id);
            action->item->setData(0, Qt::UserRole, data);
            channel->help = (void*) action->item;


            _list_channels_widget->insertTopLevelItem(iii, action->item);
            _list_channels_widget->setItemWidget(action->item, 1, wid);
            iii++;

            this->animation_time_line->actions.push_back(action);


            channel=channel->next;
        }
    }
}


void FGEAnimationTimeLineForm::on_AnimationsTreeWidget_itemCollapsed(QTreeWidgetItem *item)
{
    ////qDebug() << " mm m m  m m m m m m m m m  m m m m m m m m m m m m  mm m  mm  m m m m m m m ";
    /*FGEAnimationTimeLine* p = this->first_anim_time_line;


    while(p!=NULL){
        if(p->id==item->data(0, Qt::UserRole).toInt()){
            for(int i=0; i<p->actions.size(); i++){
                FGEActionTimeLine *_time = p->actions.at(i);
                _time->litem->setHidden(true);
            }
        }
        p=p->next;
    }*/

}


void FGEAnimationTimeLineForm::on_AnimationsTreeWidget_itemExpanded(QTreeWidgetItem *item)
{

    ////qDebug() << " mm m m  m m m m m m m m m  m m m m m m m m m m m m  mm m  mm  m m m m m m m ";
    /*FGEAnimationTimeLine* p = this->first_anim_time_line;
    int id =item->data(0, Qt::UserRole).toInt();
    qDebug() << " p->UserRole: "<<id;
    while(p!=NULL){
        qDebug() << " vp->id: ";
        qDebug() << " p->id: "<<p->id;

        if(p->id==id){
            qDebug() << " p->actions.size(): "<<p->actions.size();
            for(int i=0; i<p->actions.size(); i++){
                FGEActionTimeLine *_time = p->actions.at(i);
                _time->litem->setHidden(false);
                qDebug() << " p->i: "<<i;
            }
        }
        qDebug() << " ->next: ";

        p=p->next;
        qDebug() << " d->next: ";
    }*/


}

void FGEAnimationTimeLineForm::on_PlayPausePushButton_clicked()
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();

    if(anim->timer!=NULL){
        if(anim->timer->isActive()){
            anim->timer->stop();
        }else{
            anim->timer->start();
        }
    }
}

void FGEAnimationTimeLineForm::on_ResetPushButton_clicked()
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();

    if(anim->timer!=NULL){
        anim->timer->stop();
        ui->graphicsView->initCursorLine(0);
        anim->timer->start();
    }
}

void FGEAnimationTimeLineForm::on_PrevPushButton_clicked()
{
    this->next_prev = !this->next_prev;
}

void FGEAnimationTimeLineForm::updatePulse()
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    if(anim!=NULL){
        if(!this->next_prev){
            if(anim->current_frame+1 > ui->EndFrameDoubleSpinBox->value()){
                anim->current_frame = ui->BeginFrameDoubleSpinBox->value();
            }else if(anim->current_frame+1 < ui->BeginFrameDoubleSpinBox->value()){
                anim->current_frame = ui->BeginFrameDoubleSpinBox->value();
            }else{
                anim->current_frame++;
            }
        }else{
            if(anim->current_frame-1 < ui->BeginFrameDoubleSpinBox->value()){
                anim->current_frame = ui->EndFrameDoubleSpinBox->value();
            }else if(anim->current_frame-1 > ui->EndFrameDoubleSpinBox->value()){
                anim->current_frame = ui->EndFrameDoubleSpinBox->value();
            }else{
                anim->current_frame--;
            }
        }
    }
}

int FGEAnimationTimeLineForm::timerPulse()
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    ui->graphicsView->drawCursorLine(anim->current_frame);
    int i = ui->graphicsView->getCursorLine();
    int w = ui->graphicsView->sceneRect().width();

    if(i>w){
        ui->graphicsView->initCursorLine(0);
    }else if(i<0){
        ui->graphicsView->initCursorLine(w);
    }

    ui->graphicsView->horizontalScrollBar()->setValue(i-(ui->graphicsView->width()/2));
    ui->graphicsView->scene()->update();
    ui->graphicsView->update();

    return anim->current_frame;
}

/*void FGEAnimationTimeLineForm::deleteSelected(bool st)
{
    int type;
    void *obj = this->edit_keyframe->getSelected(type);
    qDebug() << " q deleteSelected: "<<type;
    if(type==1){
        FGEItemTimeLine *channel = (FGEItemTimeLine*) obj;
        channel->deleteSelected();
    }
}*/

void FGEAnimationTimeLineForm::mekeSelectFromTo(bool st)
{
    this->edit_keyframe->setSelectionFromTo();
}

void FGEAnimationTimeLineForm::mekeSelectOne(bool st)
{
    this->edit_keyframe->setSelectionOne();
}

void FGEAnimationTimeLineForm::updateAppliedAnimation()
{
    //this->applied_animation->setAnimation(animation);
    qDebug() << "updateAppliedAnimation : ";
    //this->setData();
}

void FGEAnimationTimeLineForm::on_SelectAnimPushButton_clicked()
{
    FGEAnimationSelectionForm *select_anim = new FGEAnimationSelectionForm();
    qDebug() << "r 1 : ";
    select_anim->init(data_project, this->applied_animation);
    qDebug() << "r 2 : ";
    select_anim->show();
    qDebug() << "r 3 : ";
    connect(select_anim, SIGNAL(updateAppliedAnimation()), this, SLOT(updateAppliedAnimation()));
    qDebug() << "r 4 : ";
}

void FGEAnimationTimeLineForm::on_add_keyframe_PushButton_clicked()
{
    FGEDataAnimation * anim= this->applied_animation->getAnimation();
    FGEDataArmature * armature = NULL;//data_project->getSelectedArmature();
    if(armature!=NULL){
        for(int i=0;i<armature->selected.size(); i++){
            //FGEDataAnimation * animation = this->data_project->first_animation;
            //while(animation!=NULL){
            if(anim->armature==armature){
                FGEDataChannel *channel = anim->first_channel;
                while(channel!=NULL){
                    for(int j=0;j<armature->selected.size(); j++){
                        FGEDataBone* bone = armature->selected.at(j).second;
                        if(channel->source==(void*)bone){
                            channel->time_stamp.push_back(anim->current_frame);
                            channel->matrix.push_back(bone->transform->getLocalTransformation());
                            qDebug() << "this->current_frame : "<<anim->current_frame;
                            qDebug() << "key frame is added : "<<channel->name;
                            anim->prepareChannel(1, channel);
                            this->setDataChannel(channel);
                        }
                    }
                    channel = channel->next;
                }
            }

            //    animation = animation->next;
            //}
        }
    }
}

