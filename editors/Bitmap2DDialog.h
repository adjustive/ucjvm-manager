#ifndef BITMAP2DEDITOR_H
#define BITMAP2DEDITOR_H

#include <QDialog>

namespace Ui {
class Bitmap2DDialog;
}

class Bitmap2D;

class Bitmap2DDialog : public QDialog
{
    Q_OBJECT

public:
    typedef Bitmap2D ResourceType;
    
public:
    static QString const fileSuffix;
    static QString const fileFilter;

public:
    explicit Bitmap2DDialog(Bitmap2D &bitmap, QWidget *parent = 0);
    ~Bitmap2DDialog();
    
private slots:
    void on_selectColor_clicked();

private:
    Ui::Bitmap2DDialog *ui;
};

#endif // BITMAP2DEDITOR_H
