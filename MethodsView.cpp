#include "MethodsView.h"
#include "ui_MethodsView.h"

#include "MethodsModel.h"

MethodsView::MethodsView(JVMClass classData, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MethodsView)
    , classData(classData)
{
    ui->setupUi(this);

    ui->methodsView->setModel(new MethodsModel(classData, this));
}

MethodsView::~MethodsView()
{
    delete ui;
}
