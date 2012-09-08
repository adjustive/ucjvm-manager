#include "Bitmap2DDialog.h"
#include "ui_Bitmap2DDialog.h"

#include <QDebug>
#include <QColorDialog>
#include <QInputDialog>

static QString const fileSuffix = "b2d";
static QString const fileFilter = "2D Bitmap (*.b2d)";


Bitmap2DDialog::Bitmap2DDialog(QWidget *parent)
    : Base(parent)
    , ui(new Ui::Bitmap2DDialog)
{
    ui->setupUi(this);
}

Bitmap2DDialog::~Bitmap2DDialog()
{
    delete ui;
}


QString const &Bitmap2DDialog::fileSuffix() const
{
    return ::fileSuffix;
}

QString const &Bitmap2DDialog::fileFilter() const
{
    return ::fileFilter;
}


Bitmap2D *Bitmap2DDialog::newResource()
{
    QStringList sizes = QStringList()
            << "32x16"
            << "64x64";

    bool ok;
    QString size = QInputDialog::getItem(this, tr("Bitmap size"), tr("Bitmap size"), sizes, 0, false, &ok);
    if (ok)
    {
        QStringList splitSize = size.split('x');
        Q_ASSERT(splitSize.size() == 2);
        int width  = splitSize.at(0).toInt();
        int height = splitSize.at(1).toInt();

        return new Bitmap2D(width, height);
    }

    return NULL;
}


void Bitmap2DDialog::setResource(ResourceType *resource)
{
    ui->editor->setBitmap(resource);
}


void Bitmap2DDialog::on_selectColor_clicked()
{
    QColorDialog chooser(ui->editor->color());
    chooser.exec();

    ui->editor->setColor(chooser.selectedColor());
}
