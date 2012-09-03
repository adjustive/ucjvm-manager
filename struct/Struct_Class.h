#ifndef STRUCT_CLASS_H
#define STRUCT_CLASS_H

#include "Struct.h"

#include "Struct_CP_Table.h"
#include "Struct_Field_Table.h"
#include "Struct_Method_Table.h"
#include "Struct_Exception_Handler_Table.h"
class JVMClass;
class Struct_ClassTable;

class Struct_Class : public Struct
{
public:
    Struct_Class(JVMClass const &classData);

    QString javaTypeName() const;
    Struct_Class const *superClass() const;

    void collectExceptions();
    void loadNativeInterface(QList<NativeFunction> const &nativeInterface);

    ResolveContext resolveContext(const ResolveContext &context) const;
    void resolveClassReferences(const ResolveContext &context);
    void resolveFieldReferences(const ResolveContext &context);
    void resolveMethodReferences(const ResolveContext &context);

    quint8 alignment() const { return 4; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Class"; }

public:
    Struct_CP_Table constantPoolTable;
    Struct_Field_Table fieldPoolTable;
    Struct_Method_Table methodPoolTable;

    Struct_Exception_Handler_Table exceptionHandlerTable;
    Struct_Exceptions exceptionsTable;

    quint16 staticDataSize;
    quint16 instanceDataSize;
    quint16 staticDataHandle;

private:
    QString className;
};

#endif // STRUCT_CLASS_H
