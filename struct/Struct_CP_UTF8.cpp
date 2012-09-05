#include "Struct_CP_UTF8.h"

#include "ConstantPoolInfo_Utf8.h"
#include "DataWriter.h"

#include <QTextStream>

Struct_CP_UTF8::Struct_CP_UTF8(const ConstantPoolInfo_Utf8 &v)
    : data(v.string().toUtf8())
{
}

void Struct_CP_UTF8::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_UTF8::writeStruct(DataWriter &data) const
{
    Struct_CP::writeStruct(data);
    data.put16(this->data.size(), "size");
    data.putBytes(this->data, "data");
}

quint32 Struct_CP_UTF8::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);
    return baseAddress;
}

void Struct_CP_UTF8::printMemoryMap(QTextStream &ts) const
{
    ts << "UTF8 @0x" << structStart << " = " << data << "\n";
}

QString Struct_CP_UTF8::string() const
{
    return QString::fromUtf8(data);
}
