#include "Bitmap2D.h"

#include <QDebug>

Bitmap2D::Bitmap2D(int width, int height)
{
    setCanvasSize(QSize(width, height));
}


QSize Bitmap2D::canvasSize() const
{
    return d.size;
}

void Bitmap2D::setCanvasSize(QSize size)
{
    d.size = size;

    if (!d.bitmap.isEmpty())
        d.bitmap.clear();

    while (d.bitmap.size() < size.height() * size.width())
        d.bitmap.append(Qt::transparent);
}


int Bitmap2D::width() const
{
    return d.size.width();
}

int Bitmap2D::height() const
{
    return d.size.height();
}


QColor Bitmap2D::pixel(QPoint point) const
{
    return d.bitmap.at(point.y() * d.size.width() + point.x());
}

void Bitmap2D::setPixel(QPoint point, QColor color)
{
    d.bitmap[point.y() * d.size.width() + point.x()] = color;
}


bool Bitmap2D::contains(QPoint point) const
{
    return point.x() >= 0
            && point.y() >= 0
            && point.x() < d.size.width()
            && point.y() < d.size.height();
}
