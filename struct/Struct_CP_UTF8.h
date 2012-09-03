#ifndef STRUCT_CP_UTF8_H
#define STRUCT_CP_UTF8_H

#include "Struct_CP.h"
class ConstantPoolInfo_Utf8;

#include <QByteArray>

class Struct_CP_UTF8 : public Struct_CP
{
public:
    Struct_CP_UTF8(ConstantPoolInfo_Utf8 const &v);

    void resolveClassReferences(const ResolveContext &context);

    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    Type type() const { return CONSTANT_TYPE_UTF8; }

    char const *typeName() const { return "CP_UTF8"; }

    QString string() const;

private:
    QByteArray data;
};

#endif // STRUCT_CP_UTF8_H
