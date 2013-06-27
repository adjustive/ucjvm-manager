#include "Struct_Resource_Bitmap3D.h"

#include "Bitmap3D.h"

Struct_Resource_Bitmap3D::Struct_Resource_Bitmap3D(QString name, const Bitmap3D &bitmap)
    : Struct_Resource(name)
{
    QDataStream stream(&data, QIODevice::WriteOnly);
    bitmap.save(stream);
}
