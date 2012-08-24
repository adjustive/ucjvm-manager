#include "FieldsView.h"
#include "ui_FieldsView.h"

#include "FieldsModel.h"

FieldsView::FieldsView(JVMClass classData, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FieldsView)
    , classData(classData)
{
    ui->setupUi(this);

    ui->fieldsView->setModel(new FieldsModel(classData, this));
}

FieldsView::~FieldsView()
{
    delete ui;
}
