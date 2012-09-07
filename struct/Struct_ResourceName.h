#ifndef STRUCT_RESOURCENAME_H
#define STRUCT_RESOURCENAME_H

#include "Struct.h"

class Struct_ResourceName : public Struct
{
public:
    Struct_ResourceName(QString name);

    quint8 alignment() const { return 1; }
    void writeStruct(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "ResourceName"; }

private:
    QString name;
};

#endif // STRUCT_RESOURCENAME_H
