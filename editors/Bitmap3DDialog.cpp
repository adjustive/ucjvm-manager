#include "Bitmap3DDialog.h"
#include "ui_Bitmap3DDialog.h"

#include "Bitmap3D.h"
#include "ResourceFactory.h"

QString const Bitmap3DDialog::fileSuffix = "b3d";
QString const Bitmap3DDialog::fileFilter = "3D Bitmap (*.b3d)";
static ResourceFactory::Insert<Bitmap3DDialog> insert;


Bitmap3DDialog::Bitmap3DDialog(Bitmap3D &bitmap, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Bitmap3DDialog)
{
    ui->setupUi(this);

    ui->editor->setBitmap(bitmap);
    ui->rendering->setBitmap(bitmap);

    connect(ui->editor, SIGNAL(changed()), ui->rendering, SLOT(repaint()));
}

Bitmap3DDialog::~Bitmap3DDialog()
{
    delete ui;
}
