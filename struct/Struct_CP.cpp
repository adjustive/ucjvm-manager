#include "Struct_CP.h"

#include "DataWriter.h"

Struct_CP::Struct_CP()
{
}

Struct_CP::~Struct_CP()
{
}

void Struct_CP::writeStruct(DataWriter &data) const
{
    data.put8((quint8)type(), "type");
    writeConstantData(data);
}
