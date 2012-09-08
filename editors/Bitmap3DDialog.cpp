#include "Bitmap3DDialog.h"
#include "ui_Bitmap3DDialog.h"

#include <QInputDialog>

static QString const fileSuffix = "b3d";
static QString const fileFilter = "3D Bitmap (*.b3d)";


Bitmap3DDialog::Bitmap3DDialog(QWidget *parent)
    : Base(parent)
    , ui(new Ui::Bitmap3DDialog)
{
    ui->setupUi(this);

    connect(ui->editor, SIGNAL(changed()), ui->rendering, SLOT(repaint()));
}

Bitmap3DDialog::~Bitmap3DDialog()
{
    delete ui;
}


QString const &Bitmap3DDialog::fileSuffix() const
{
    return ::fileSuffix;
}

QString const &Bitmap3DDialog::fileFilter() const
{
    return ::fileFilter;
}


Bitmap3D *Bitmap3DDialog::newResource()
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
        int depth  = splitSize.at(2).toInt();

        return new Bitmap3D(width, height, depth);
    }

    return NULL;
}


void Bitmap3DDialog::setResource(ResourceType *resource)
{
    ui->editor->setBitmap(resource);
    ui->rendering->setBitmap(resource);
}
