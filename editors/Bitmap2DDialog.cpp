#include "Bitmap2DDialog.h"
#include "ui_Bitmap2DDialog.h"

#include "Bitmap2D.h"
#include "ResourceFactory.h"

#include <QDebug>
#include <QColorDialog>

QString const Bitmap2DDialog::fileSuffix = "b2d";
QString const Bitmap2DDialog::fileFilter = "2D Bitmap (*.b2d)";
static ResourceFactory::Insert<Bitmap2DDialog> insert;


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
