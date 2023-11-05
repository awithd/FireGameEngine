#include "FGEFillSelectedVEFForm.h"
#include "ui_FGEFillSelectedVEFForm.h"

FGEFillSelectedVEFForm::FGEFillSelectedVEFForm(FGETriggerFunction *trigger, QString name_parent, FGEOpenGLWidget *glwidget_world, FGEDataSelectedNodes *sn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGEFillSelectedVEFForm)
{
    ui->setupUi(this);
    this->sn = sn;
    this->trigger = trigger;
    this->name_parent = name_parent;
    this->glwidget_world = glwidget_world;

}

FGEFillSelectedVEFForm::~FGEFillSelectedVEFForm()
{
    delete ui;
}

void FGEFillSelectedVEFForm::showDialog(QString &msg){

    // إنشاء نافذة QDialog
    QDialog dialog;
    dialog.setWindowTitle("رسالة خطأ");

    // إنشاء تخطيط رأسي للمحتوى
    QVBoxLayout layout;

    // إنشاء نص خطأ
    QLabel errorMessage;
    errorMessage.setText(msg);

    // إضافة نص الخطأ إلى التخطيط
    layout.addWidget(&errorMessage);

    // إنشاء زر للخروج
    QPushButton closeButton("موافق");
    QObject::connect(&closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // إضافة الزر إلى التخطيط
    layout.addWidget(&closeButton);

    // تعيين التخطيط كمحتوى للنافذة
    dialog.setLayout(&layout);

    // عرض النافذة
    dialog.exec();
}
void FGEFillSelectedVEFForm::on_ds_apply_fill_pushButton_clicked()
{
    if(this->glwidget_world!=NULL && this->trigger!=NULL && this->sn!=NULL){

        FGEFill fill;

        this->glwidget_world->makeCurrent();

        if(ui->radioButton_1->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                QString msg = "";
                bool error = false;
                fill.fillFace2(this->glwidget_world->openGLFunctions(), node, msg, error);
                if(error){
                    this->showDialog(msg);
                }
            }
        }else if(ui->radioButton_2->isChecked()){
            for (int i = 0; i < sn->selected_nodes.size(); i++){
                FGEDataNode* node = sn->selected_nodes.at(i);
                fill.fillEdge(this->glwidget_world->openGLFunctions(), node);
            }
        }


        this->glwidget_world->doneCurrent();
        emit this->trigger->updateScene();
    }
}

