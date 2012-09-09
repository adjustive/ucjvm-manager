#ifndef STRUCT_CLASS_H
#define STRUCT_CLASS_H

#include "Struct.h"

#include "Struct_CP_Table.h"
#include "Struct_Field_Table.h"
#include "Struct_Method_Table.h"
#include "Struct_Exception_Handler_Table.h"
class Class;
class Struct_ClassTable;

class Struct_Class : public Struct
{
public:
    Struct_Class(Class const &classData);

    QString javaTypeName() const;
    Struct_Class const *superClass() const;

    void collectExceptions();
    void setStaticDataHandle(quint16 staticDataHandle);
    void loadNativeInterface(QList<NativeFunction> const &nativeInterface);

    ResolveContext resolveContext(const ResolveContext &context) const;
    void resolveClassReferences(const ResolveContext &context);
    void resolveFieldReferences(const ResolveContext &context);
    void resolveMethodReferences(const ResolveContext &context);

    void computeDataSize();
    void computeFieldOffsets();

    MemoryModel::Align alignment() const { return MemoryModel::ADDRESS_ALIGN; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Class"; }

public:
    Struct_CP_Table constantPoolTable;
    Struct_Field_Table fieldPoolTable;
    Struct_Method_Table methodPoolTable;

    Struct_Exception_Handler_Table exceptionHandlerTable;
    Struct_Exceptions exceptionsTable;

    quint16 inheritedStaticDataSize;
    quint16 inheritedInstanceDataSize;
    quint16 staticDataHandle;

private:
    quint16 ownStaticDataSize;
    quint16 ownInstanceDataSize;
    QString className;
};

#endif // STRUCT_CLASS_H
