#ifndef BITMAP3DDIALOG_H
#define BITMAP3DDIALOG_H

#include "ResourceEditor.h"
#include "Bitmap3D.h"

namespace Ui {
class Bitmap3DDialog;
}

class Bitmap3D;

class Bitmap3DDialog : public ResourceEditorT<Bitmap3DDialog, Bitmap3D>
{
    Q_OBJECT

private:
    const QString &fileSuffix() const;
    const QString &fileFilter() const;

    Bitmap3D *newResource();
    void setResource(ResourceType *resource);

public:
    explicit Bitmap3DDialog(QWidget *parent);
    ~Bitmap3DDialog();
    
private:
    Ui::Bitmap3DDialog *ui;
};

#endif // BITMAP3DDIALOG_H
