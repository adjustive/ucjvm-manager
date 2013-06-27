#ifndef STRUCT_RESOURCE_BITMAP3D_H
#define STRUCT_RESOURCE_BITMAP3D_H

#include "Struct_Resource.h"

class Bitmap3D;

class Struct_Resource_Bitmap3D : public Struct_Resource
{
public:
    Struct_Resource_Bitmap3D(QString name, Bitmap3D const &bitmap);

    char const *typeName() const { return "Resource_Bitmap3D"; }
};

#endif // STRUCT_RESOURCE_BITMAP3D_H
