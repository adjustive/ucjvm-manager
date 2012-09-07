#ifndef BITMAP2D_H
#define BITMAP2D_H

#include "Resource.h"

#include <QSize>
#include <QColor>
#include <QList>
class QFile;
class QPoint;

struct Bitmap2DPrivate
{
    QSize size;
    QList<QColor> bitmap;
};

class Bitmap2D : public Resource
{
public:
    Bitmap2D(int width, int height);
    Bitmap2D(QDataStream &stream);

    QSize canvasSize() const;

    int width() const;
    int height() const;

    QColor pixel(QPoint point) const;
    void setPixel(QPoint point, QColor color);

    bool contains(QPoint point) const;

    void save(QDataStream &stream) const;

    void accept(ResourceVisitor &v);

private:
    Bitmap2DPrivate d;
};

#endif // BITMAP2D_H
