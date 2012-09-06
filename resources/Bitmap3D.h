#ifndef BITMAP3D_H
#define BITMAP3D_H

#include "Bitmap2D.h"

struct Bitmap3DPrivate
{
    QList<Bitmap2D> array;
};

class Bitmap3D
{
public:
    Bitmap3D(int width, int height, int depth);

    int width() const;
    int height() const;
    int depth() const;

    Bitmap2D &layer(int layer);

    QColor pixel(int x, int y, int z) const;

private:
    Bitmap3DPrivate d;
};

#endif // BITMAP3D_H
