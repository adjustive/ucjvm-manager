#ifndef STRUCT_RESOURCE_BITMAP2D_H
#define STRUCT_RESOURCE_BITMAP2D_H

#include "Struct_Resource.h"

class Bitmap2D;

class Struct_Resource_Bitmap2D : public Struct_Resource
{
public:
    Struct_Resource_Bitmap2D(QString name, Bitmap2D const &bitmap);

    char const *typeName() const { return "Resource_Bitmap2D"; }
};

#endif // STRUCT_RESOURCE_BITMAP2D_H
