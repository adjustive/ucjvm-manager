#include "Bitmap2DDialog.h"
#include "ui_Bitmap2DDialog.h"

#include <QDebug>
#include <QColorDialog>

Bitmap2DDialog::Bitmap2DDialog(Bitmap2D &bitmap, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Bitmap2DDialog)
{
    ui->setupUi(this);

    ui->editor->setBitmap(bitmap);
}

Bitmap2DDialog::~Bitmap2DDialog()
{
    delete ui;
}

void Bitmap2DDialog::on_selectColor_clicked()
{
    QColorDialog chooser(ui->editor->color());
    chooser.exec();

    ui->editor->setColor(chooser.selectedColor());
}
