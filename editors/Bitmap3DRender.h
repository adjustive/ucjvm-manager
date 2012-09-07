#ifndef BITMAP3DRENDER_H
#define BITMAP3DRENDER_H

#include <qglview.h>

class Bitmap3D;

class Bitmap3DRenderPrivate;

class Bitmap3DRender : public QGLView
{
    Q_OBJECT
private:
    QGLMaterial *material(QColor color);

public:
    explicit Bitmap3DRender(QWidget *parent = 0);
    ~Bitmap3DRender();

    void setBitmap(Bitmap3D &bitmap);

    void createScene();
    void paintGL(QGLPainter *painter);

signals:
    
public slots:

private:
    Q_DECLARE_PRIVATE(Bitmap3DRender)
    Bitmap3DRenderPrivate *d_ptr;
};

#endif // BITMAP3DRENDER_H
