#include "fgematerialbrowserform.h"
#include "ui_fgematerialbrowserform.h"

FGEMaterialBrowserForm::FGEMaterialBrowserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEMaterialBrowserForm)
{
    ui->setupUi(this);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    contextMenu = new QMenu(ui->listWidget);
    contextMenuFolder = new QMenu(ui->listWidget);
    contextMenuMaterial = new QMenu(ui->listWidget);
    //ui->treeobject->setContextMenuPolicy(Qt::ActionsContextMenu);

    action_new_folder   = new QAction("New Folder");
    action_new_material       = new QAction("New Material");
    contextMenu->addAction(action_new_folder);
    contextMenu->addAction(action_new_material);


    action_delete_folder   = new QAction("delete folder");
    contextMenuFolder->addAction(action_delete_folder);
    action_rename_folder   = new QAction("rename folder");
    contextMenuFolder->addAction(action_rename_folder);


    action_delete_material   = new QAction("delete material");
    contextMenuMaterial->addAction(action_delete_material);
    action_rename_material   = new QAction("rename material");
    contextMenuMaterial->addAction(action_rename_material);
    action_edit_material   = new QAction("Edit material");
    contextMenuMaterial->addAction(action_edit_material);



    //contextMenuItem->addAction(action_delete_material);
    /*contextMenu->addAction(action_delete_folder);
    contextMenu->addAction(action_delete_material);*/

    //connect(uninstallAction, SIGNAL(triggered()), this, SLOT(uninstallAppletClickedSlot()));
    connect(action_new_folder, SIGNAL(triggered()), this, SLOT(selectNewFolderSlot()));
    connect(action_new_material, SIGNAL(triggered()), this, SLOT(selectNewMaterialSlot()));
    connect(action_rename_material, SIGNAL(triggered()), this, SLOT(selectRenameMaterialSlot()));
    connect(action_rename_folder, SIGNAL(triggered()), this, SLOT(selectRenameMaterialSlot()));
    connect(action_edit_material, SIGNAL(triggered()), this, SLOT(selectEditMaterialSlot()));

    FGEMaterialViewWidgetItem *item = new FGEMaterialViewWidgetItem;
    item->item = NULL;
    item->material = NULL;
    item->count_items = 0;
    item->next = NULL;
    item->prev = NULL;
    item->last_child = NULL;
    item->first_child = NULL;
    item->parent = NULL;

    parent_item = item;
    current_item = item;
}

void FGEMaterialBrowserForm::deleteMaterialViewWidgetItem(FGEMaterialViewWidgetItem *parent)
{
    FGEMaterialViewWidgetItem *p = parent, *k;
    while(p!=NULL){
        if(p->first_child!=NULL){
            deleteMaterialViewWidgetItem(p->first_child);
        }

        k = p;
        p=p->next;
        delete k;
    }
}


FGEMaterialBrowserForm::~FGEMaterialBrowserForm()
{
    // REMOVE ALL MaterialViewWidgetItem
    deleteMaterialViewWidgetItem(parent_item);

    // REMOVE ALL QAction
    delete action_new_folder;
    delete action_new_material;
    delete contextMenu;

    delete action_delete_folder;
    delete action_rename_folder;
    delete contextMenuFolder;

    delete action_delete_material;
    delete action_rename_material;
    delete contextMenuMaterial;

    // REMOVE ui
    delete ui;
}



void FGEMaterialBrowserForm::pushHistory(FGEMaterialViewWidgetItem *item)
{
    FGEMVWIHistoryItem *m_item = new FGEMVWIHistoryItem;
    m_item->item = item;
    if(first_history==NULL){
        first_history = m_item;
        last_history = m_item;
        m_item->prev = NULL;
        m_item->next = NULL;
    }else{
        m_item->next = NULL;
        last_history->next = m_item;
        m_item->prev = last_history;
        last_history = m_item;
    }
}
bool FGEMaterialBrowserForm::popHistory()
{
    if(first_history!=NULL){
        if(first_history==last_history->prev){
            delete last_history;
            first_history->next = NULL;
            last_history = first_history;
        }else{
            FGEMVWIHistoryItem *p = last_history->prev;
            delete last_history;
            p->next = NULL;
            last_history = p;
        }
        return true;
    }
    return false;
}

void FGEMaterialBrowserForm::updateForm()
{
    if(current_item==parent_item){
        ui->pushButton_browsing_left->setEnabled(false);
    }else{
        ui->pushButton_browsing_left->setEnabled(true);
    }


}

void FGEMaterialBrowserForm::appendNewFolder(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item, QString name)
{
    FGEMaterialViewWidgetItem *m_item = new FGEMaterialViewWidgetItem;
    m_item->item = item;
    m_item->material = NULL;
    m_item->name = name;
    m_item->count_items = 0;
    m_item->parent = parent;
    m_item->first_child = NULL;
    m_item->last_child = NULL;
    if(parent->first_child==NULL){
        parent->first_child = m_item;
        parent->last_child = m_item;
        m_item->prev = NULL;
        m_item->next = NULL;
    }else{
        m_item->next = NULL;
        parent->last_child->next = m_item;
        m_item->prev = parent->last_child;
        parent->last_child = m_item;
    }

    ui->listWidget->updateGeometry();
}

void FGEMaterialBrowserForm::appendNewMaterial(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item, QString name)
{
    FGEMaterialViewWidgetItem *m_item = new FGEMaterialViewWidgetItem;
    m_item->item = item;
    m_item->count_items = 0;
    m_item->name = name;
    m_item->parent = parent;
    m_item->first_child = NULL;
    m_item->last_child = NULL;
    if(parent->first_child==NULL){
        parent->first_child = m_item;
        parent->last_child = m_item;
        m_item->prev = NULL;
        m_item->next = NULL;
    }else{
        m_item->next = NULL;
        parent->last_child->next = m_item;
        m_item->prev = parent->last_child;
        parent->last_child = m_item;
    }

    FGEDataMaterial *mat = new FGEDataMaterial;
    mat->next = NULL;
    mat->prev = NULL;
    mat->effect = NULL;
    m_item->material = mat;

    ui->listWidget->updateGeometry();

}

FGEMaterialViewWidgetItem * FGEMaterialBrowserForm::searchItemIterattor(FGEMaterialViewWidgetItem *parent, QListWidgetItem *item)
{
    FGEMaterialViewWidgetItem *p = parent, *k;
    while(p!=NULL){
        if(p->item == item){
            return p;
        }
        if(p->first_child!=NULL){
            k = searchItemIterattor(p->first_child, item);
            if(k!=NULL){
                return k;
            }
        }

        p=p->next;
    }
    return NULL;
}


void FGEMaterialBrowserForm::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt(pos);
    if(item!=NULL){
        FGEMaterialViewWidgetItem *s = current_item->first_child, *p=NULL;
        while(s!=NULL){
            if(s->item==item){
                p = s;
            }
            s=s->next;
        }
        if(p!=NULL){
            if(p->material==NULL){
                contextMenuFolder->exec(mapToGlobal(pos));
            }else{
                contextMenuMaterial->exec(mapToGlobal(pos));
            }
        }
    }else{
        contextMenu->exec(mapToGlobal(pos));
    }
}

void FGEMaterialBrowserForm::selectNewFolderSlot()
{
    QString name="new folder";
    QListWidgetItem *item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/fainza.png"), name);
    item->setFlags (item->flags () | Qt::ItemIsEditable);
    item->setSelected(true);
    ui->listWidget->addItem(item);
    //ui->listWidget->editItem(item);
    appendNewFolder(current_item, item, name);
}

void FGEMaterialBrowserForm::selectNewMaterialSlot()
{
    QString name="new material";
    QListWidgetItem *item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/svg/empty_material.svg"), name);
    item->setFlags (item->flags () | Qt::ItemIsEditable);
    item->setSelected(true);
    ui->listWidget->addItem(item);
    //ui->listWidget->editItem(item);
    appendNewMaterial(current_item, item, name);
}
void FGEMaterialBrowserForm::selectEditMaterialSlot()
{
    FGEWindowShaderEditor *item = new FGEWindowShaderEditor(NULL);
    item->show();
}
void FGEMaterialBrowserForm::selectRenameMaterialSlot()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setFlags (item->flags () | Qt::ItemIsEditable);
    ui->listWidget->editItem(item);
}

void FGEMaterialBrowserForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "++ Double Clicked";
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    FGEMaterialViewWidgetItem *s = current_item->first_child, *p=NULL;
    while(s!=NULL){
        if(s->item==item){
            p = s;
        }
        s=s->next;
    }
    if(p!=NULL){
        qDebug() << "++ name Clicked " <<p->name;
        if(p->material==NULL){
            //pushHistory(p);
            qDebug() << "++ Double Clicked 21";
            ui->listWidget->clear();
            qDebug() << "++ Double Clicked 22";
            current_item = p;
            qDebug() << "++ Double Clicked 23";
            FGEMaterialViewWidgetItem *k = p->first_child;
            qDebug() << "++ Double Clicked 24";

            while(k!=NULL){
                if(k->material==NULL){
                    QListWidgetItem *_item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/fainza.png"),k->name);
                    _item->setFlags (_item->flags () | Qt::ItemIsEditable);
                    ui->listWidget->addItem(_item);
                    k->item = _item;
                }else{
                    QListWidgetItem *_item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/svg/empty_material.svg"),k->name);
                    _item->setFlags (_item->flags () | Qt::ItemIsEditable);
                    ui->listWidget->addItem(_item);
                    k->item = _item;
                }
                k=k->next;
            }
        }else{

        }
    }else{
        qDebug() << "++ Clicked is NULL ";
    }

    updateForm();
}

void FGEMaterialBrowserForm::on_pushButton_browsing_left_clicked()
{

    qDebug() << "on_pushButton_browsing_left_clicked";
    if(current_item->parent!=NULL){

        current_item = current_item->parent;
        ui->listWidget->clear();
        FGEMaterialViewWidgetItem *k = current_item->first_child;
        while(k!=NULL){
            if(k->material==NULL){
                QListWidgetItem *_item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/fainza.png"),k->name);
                _item->setFlags (_item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(_item);
                k->item = _item;

            }else{
                QListWidgetItem *_item = new QListWidgetItem(QIcon("/home/corolo/Qt/FireGameEngine/Icons/svg/empty_material.svg"),k->name);
                _item->setFlags (_item->flags () | Qt::ItemIsEditable);
                ui->listWidget->addItem(_item);
                k->item = _item;
            }
            k=k->next;
        }

    }
    updateForm();
}

void FGEMaterialBrowserForm::on_listWidget_currentTextChanged(const QString &currentText)
{

    /*qDebug() << "vo : "<<currentText;
    QListWidgetItem *item = ui->listWidget->currentItem();

    qDebug() << "Text Changed me : "<<item->text();

    FGEMaterialViewWidgetItem *p = searchItemIterattor(parent_item, item);
    p->name = currentText;
    qDebug() << "Text Changed : "<<p->name;*/
}


void FGEMaterialBrowserForm::on_listWidget_itemChanged(QListWidgetItem *item)
{
    FGEMaterialViewWidgetItem *p = searchItemIterattor(parent_item, item);
    p->name = item->text();

}
