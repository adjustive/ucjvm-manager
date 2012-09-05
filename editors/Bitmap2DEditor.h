#ifndef BITMAP2DEDITOR_H
#define BITMAP2DEDITOR_H

#include <QDialog>

namespace Ui {
class Bitmap2DEditor;
}

class Bitmap2DEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit Bitmap2DEditor(QWidget *parent = 0);
    ~Bitmap2DEditor();
    
private:
    Ui::Bitmap2DEditor *ui;
};

#endif // BITMAP2DEDITOR_H
