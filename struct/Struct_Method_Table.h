#ifndef STRUCT_METHOD_TABLE_H
#define STRUCT_METHOD_TABLE_H

#include "Struct_Method.h"
class Methods;

#include <QList>

class Struct_Method_Table : public Struct
{
public:
    Struct_Method_Table(Methods const &methods);

    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    void collectExceptions(Struct_Exception_Handler_Table &ehTable, Struct_Exceptions &eTable);
    void loadNativeInterface(const QList<NativeFunction> &nativeInterface, QString className, const Struct_CP_Table &constantPoolTable);

private:
    QList<Struct_Method> methods;
};

#endif // STRUCT_METHOD_TABLE_H
