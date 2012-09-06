#include "Bitmap3DView.h"
#include "ui_Bitmap3DView.h"

#include "Bitmap3D.h"

#include <QColorDialog>

Bitmap3DView::Bitmap3DView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Bitmap3DView)
    , bitmap(NULL)
{
    ui->setupUi(this);

    connect(ui->viewer, SIGNAL(changed()), SIGNAL(changed()));
}

Bitmap3DView::~Bitmap3DView()
{
    delete ui;
}


void Bitmap3DView::setBitmap(Bitmap3D &bitmap)
{
    this->bitmap = &bitmap;

    ui->layer->setMaximum(bitmap.depth() - 1);
    ui->viewer->setBitmap(bitmap.layer(0));
}


void Bitmap3DView::on_layer_valueChanged(int layer)
{
    ui->viewer->setBitmap(bitmap->layer(layer));
}

void Bitmap3DView::on_selectColor_clicked()
{
    QColorDialog chooser(ui->viewer->color());
    chooser.exec();

    ui->viewer->setColor(chooser.selectedColor());
}
