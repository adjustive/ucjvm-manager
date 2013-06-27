#include "ConfigView.h"
#include "ui_ConfigView.h"

#include "NativeInterfaceModel.h"

ConfigView::ConfigView(Config config, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigView)
    , config(config)
{
    ui->setupUi(this);

    ui->nativeInterfaceView->setModel(new NativeInterfaceModel(config.nativeInterface(), this));

    ui->name->setText(config.configName());
    ui->description->setText(config.description());
    ui->baseAddress->setText(QString("0x%0").arg(config.baseAddress(), 0, 16));
}

ConfigView::~ConfigView()
{
    delete ui;
}
