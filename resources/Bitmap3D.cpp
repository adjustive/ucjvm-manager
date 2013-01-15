#include "Bitmap3D.h"
#include "ResourceVisitor.h"

#include <QPoint>


Bitmap3D::Bitmap3D(int width, int height, int depth)
{
    Q_ASSERT(width > 0);
    Q_ASSERT(height > 0);
    Q_ASSERT(depth > 0);

    while (d.array.size() != depth)
        d.array.append(Bitmap2D(width, height));
}

Bitmap3D::Bitmap3D(QDataStream &stream)
{
    int depth;
    stream >> depth;

    while (d.array.size() != depth)
        d.array.append(Bitmap2D(stream));
}


int Bitmap3D::width() const
{
    return d.array.front().width();
}

int Bitmap3D::height() const
{
    return d.array.front().height();
}

int Bitmap3D::depth() const
{
    return d.array.size();
}


Bitmap2D &Bitmap3D::layer(int layer)
{
    Q_ASSERT(layer < depth());
    Q_ASSERT(layer >= 0);
    return d.array[layer];
}


QColor Bitmap3D::pixel(int x, int y, int z) const
{
    return d.array[z].pixel(QPoint(x, y));
}


bool Bitmap3D::changed() const
{
    foreach (Bitmap2D const &bitmap, d.array)
        if (bitmap.changed())
            return true;
    return false;
}

void Bitmap3D::resetChanged()
{
    foreach (Bitmap2D const &bitmap, d.array)
        const_cast<Bitmap2D &>(bitmap).resetChanged();
}


void Bitmap3D::save(QDataStream &stream) const
{
    stream << d.array.size();
    foreach (Bitmap2D const &bitmap, d.array)
        bitmap.save(stream);
}


void Bitmap3D::accept(ResourceVisitor &v)
{
    v.visit(*this);
}
