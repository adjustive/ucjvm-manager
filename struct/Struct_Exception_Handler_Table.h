#ifndef STRUCT_EXCEPTION_HANDLER_TABLE_H
#define STRUCT_EXCEPTION_HANDLER_TABLE_H

#include "Struct.h"

#include "Struct_Exception_Handler.h"
class ExceptionHandler;

#include <QList>

class Struct_Exception_Handler_Table : public Struct
{
public:
    Struct_Exception_Handler_Table();

    MemoryModel::Align alignment() const { return MemoryModel::INT16_ALIGN; }
    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(MemoryModel const &memoryModel, quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

    char const *typeName() const { return "Exception_Handler_Table"; }

    void add(QList<ExceptionHandler> exceptionHandlers);
    quint16 size() const;

private:
    QList<Struct_Exception_Handler> handlers;
};

#endif // STRUCT_EXCEPTION_HANDLER_TABLE_H
