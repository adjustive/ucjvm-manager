#ifndef BITMAP2DVIEW_H
#define BITMAP2DVIEW_H

#include <QWidget>

class Bitmap2D;
class Bitmap2DViewPrivate;

class Bitmap2DView : public QWidget
{
    Q_OBJECT
public:
    explicit Bitmap2DView(QWidget *parent = 0);
    ~Bitmap2DView();
    
    void setBitmap(Bitmap2D &bitmap);

    QColor color() const;
    void setColor(QColor color);

    void paintEvent(QPaintEvent *event);
    void drawBitmap(QPainter &painter);
    void drawGrid(QPainter &painter);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

signals:
    void changed();

public slots:

private:
    Q_DECLARE_PRIVATE(Bitmap2DView)
    Bitmap2DViewPrivate *d_ptr;
};

#endif // BITMAP2DVIEW_H
