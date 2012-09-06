#ifndef BITMAP2D_H
#define BITMAP2D_H

#include <QSize>
#include <QColor>
#include <QList>
#include <QPoint>

struct Bitmap2DPrivate
{
    QSize size;
    QList<QColor> bitmap;
};

class Bitmap2D
{
public:
    Bitmap2D(int width, int height);

    QSize canvasSize() const;
    void setCanvasSize(QSize size);

    int width() const;
    int height() const;

    QColor pixel(QPoint point) const;
    void setPixel(QPoint point, QColor color);

    bool contains(QPoint point) const;

private:
    Bitmap2DPrivate d;
};

#endif // BITMAP2D_H
