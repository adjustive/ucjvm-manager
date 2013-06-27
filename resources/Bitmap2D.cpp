#include "Bitmap2D.h"
#include "ResourceVisitor.h"

#include <QDebug>
#include <QFile>
#include <QPoint>


Bitmap2D::Bitmap2D(int width, int height)
{
    d.size = QSize(width, height);

    while (d.bitmap.size() < height * width)
        d.bitmap.append(Qt::transparent);

    d.changed = false;
}


Bitmap2D::Bitmap2D(QDataStream &stream)
{
    stream >> d.size;

    while (d.bitmap.size() < d.size.height() * d.size.width())
    {
        QColor pixel;
        stream >> pixel;
        d.bitmap.append(pixel);
    }
}



QSize Bitmap2D::canvasSize() const
{
    return d.size;
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
    d.changed = true;
}


bool Bitmap2D::contains(QPoint point) const
{
    return point.x() >= 0
        && point.y() >= 0
        && point.x() < d.size.width()
        && point.y() < d.size.height();
}


bool Bitmap2D::changed() const
{
    return d.changed;
}

void Bitmap2D::resetChanged()
{
    d.changed = false;
}


void Bitmap2D::save(QDataStream &stream) const
{
    stream << d.size;
    foreach (QColor pixel, d.bitmap)
        stream << pixel;
}


void Bitmap2D::accept(ResourceVisitor &v)
{
    v.visit(*this);
}
