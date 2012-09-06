#ifndef BITMAP3DVIEW_H
#define BITMAP3DVIEW_H

#include <QWidget>

namespace Ui {
class Bitmap3DView;
}

class Bitmap3D;

class Bitmap3DView : public QWidget
{
    Q_OBJECT
    
public:
    explicit Bitmap3DView(QWidget *parent = 0);
    ~Bitmap3DView();

    void setBitmap(Bitmap3D &bitmap);

signals:
    void changed();

private slots:
    void on_layer_valueChanged(int layer);

    void on_selectColor_clicked();

private:
    Ui::Bitmap3DView *ui;
    Bitmap3D *bitmap;
};

#endif // BITMAP3DVIEW_H
