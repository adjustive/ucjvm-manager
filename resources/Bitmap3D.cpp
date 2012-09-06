#include "Bitmap3D.h"

Bitmap3D::Bitmap3D(int width, int height, int depth)
{
    Q_ASSERT(width > 0);
    Q_ASSERT(height > 0);
    Q_ASSERT(depth > 0);

    while (d.array.size() != depth)
        d.array.append(Bitmap2D(width, height));
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
