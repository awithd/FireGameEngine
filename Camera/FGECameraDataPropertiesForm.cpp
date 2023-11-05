#include "FGECameraDataPropertiesForm.h"
#include "ui_FGECameraDataPropertiesForm.h"

FGECameraDataPropertiesForm::FGECameraDataPropertiesForm(FGEDataProject *data_project, FGEOpenGLWidget *glwidget_world, FGEDataCamera *camera,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FGECameraDataPropertiesForm)
{
    ui->setupUi(this);
    this->data_project = data_project;
    this->glwidget_world = glwidget_world;
    this->camera  = camera;

    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listWidget->setFocusPolicy(Qt::NoFocus); // Disabling the focus for items in the list

    this->form = new FGECameraDataLensPropertyForm(data_project, camera);
    this->item = new FGEListWidgetStyleAItem(this->form->getWidgetB());
    this->item->setTitle("Lens Property");
    this->item->setIcon(":Icons/camera.png");
    this->form->item = this->item->item;

    ui->listWidget->addItem(this->item->item);
    ui->listWidget->setItemWidget(this->item->item, this->item);


    this->form1 = new FGECameraDataCompositionGuidesForm(data_project, camera);
    this->item1 = new FGEListWidgetStyleAItem(this->form1->getWidgetB());
    this->item1->setTitle("Lens Property");
    this->item1->setIcon(":Icons/camera.png");
    //this->form1->item = this->item1->item;

    ui->listWidget->addItem(this->item1->item);
    ui->listWidget->setItemWidget(this->item1->item, this->item1);

}

FGECameraDataPropertiesForm::~FGECameraDataPropertiesForm()
{
    delete ui;
}
