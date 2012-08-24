#ifndef STRUCT_CP_UTF8_H
#define STRUCT_CP_UTF8_H

#include "Struct_CP.h"
class ConstantPoolInfo_Utf8;

#include <QByteArray>

class Struct_CP_UTF8 : public Struct_CP
{
public:
    Struct_CP_UTF8(ConstantPoolInfo_Utf8 const &v);

    void writeThis(DataWriter &data) const;

    Type type() const { return CONSTANT_TYPE_UTF8; }

public:
    QByteArray data;
};

#endif // STRUCT_CP_UTF8_H
