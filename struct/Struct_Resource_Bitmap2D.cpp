#include "Struct_Resource_Bitmap2D.h"

#include "Bitmap2D.h"

Struct_Resource_Bitmap2D::Struct_Resource_Bitmap2D(QString name, const Bitmap2D &bitmap)
    : Struct_Resource(name)
{
    QDataStream stream(&data, QIODevice::WriteOnly);
    bitmap.save(stream);
}
