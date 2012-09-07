#ifndef BITMAP3DDIALOG_H
#define BITMAP3DDIALOG_H

#include <QDialog>

namespace Ui {
class Bitmap3DDialog;
}

class Bitmap3D;

class Bitmap3DDialog : public QDialog
{
    Q_OBJECT
    
public:
    typedef Bitmap3D ResourceType;

public:
    static QString const fileSuffix;
    static QString const fileFilter;

public:
    explicit Bitmap3DDialog(Bitmap3D &bitmap, QWidget *parent = 0);
    ~Bitmap3DDialog();
    
private:
    Ui::Bitmap3DDialog *ui;
};

#endif // BITMAP3DDIALOG_H
