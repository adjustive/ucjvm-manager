#ifndef BITMAP2DEDITOR_H
#define BITMAP2DEDITOR_H

#include "ResourceEditor.h"
#include "Bitmap2D.h"

namespace Ui {
class Bitmap2DDialog;
}

class Bitmap2D;

class Bitmap2DDialog : public ResourceEditorT<Bitmap2DDialog, Bitmap2D>
{
    Q_OBJECT

private:
    const QString &fileSuffix() const;
    const QString &fileFilter() const;

    Bitmap2D *newResource();
    void setResource(ResourceType *resource);

public:
    explicit Bitmap2DDialog(QWidget *parent = 0);
    ~Bitmap2DDialog();
    
private slots:
    void on_selectColor_clicked();

private:
    Ui::Bitmap2DDialog *ui;
};

#endif // BITMAP2DEDITOR_H
