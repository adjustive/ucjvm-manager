#ifndef STRUCT_CLASS_H
#define STRUCT_CLASS_H

#include "Struct.h"

#include "Struct_CP_Table.h"
#include "Struct_Field_Table.h"
#include "Struct_Method_Table.h"
class JVMClass;

class Struct_Class : public Struct
{
public:
    Struct_Class(JVMClass const &classData);

    void writeThis(DataWriter &data) const;
    void writeChildren(DataWriter &data) const;

public:
    Struct_CP_Table constantPoolTable;
    Struct_Field_Table fieldPoolTable;
    Struct_Method_Table methodPoolTable;

    quint16 staticDataSize;
    quint16 instanceDataSize;
    quint16 staticDataHandle;

public:
    QString name;
};

#endif // STRUCT_CLASS_H
