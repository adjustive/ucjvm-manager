#include "Struct_CP_Dummy.h"

#include <QTextStream>

#include <limits>


QSharedPointer<Struct_CP> Struct_CP_Dummy::instance(new Struct_CP_Dummy);


Struct_CP_Dummy::Struct_CP_Dummy()
{
}

void Struct_CP_Dummy::resolveClassReferences(const ResolveContext &context)
{
}

void Struct_CP_Dummy::writeStruct(DataWriter &data) const
{
    Q_UNUSED(data);
}

void Struct_CP_Dummy::writeConstantData(DataWriter &data) const
{
    Q_UNUSED(data);
}

quint32 Struct_CP_Dummy::computeMemoryMap(quint32 baseAddress)
{
    setMemoryAddress(std::numeric_limits<quint32>::max());
    return baseAddress;
}

void Struct_CP_Dummy::printMemoryMap(QTextStream &ts) const
{
    ts << "Dummy\n";
}
