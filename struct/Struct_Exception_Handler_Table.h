#ifndef STRUCT_EXCEPTION_HANDLER_TABLE_H
#define STRUCT_EXCEPTION_HANDLER_TABLE_H

#include "Struct.h"

#include "Struct_Exception_Handler.h"

#include <QList>

class Struct_Exception_Handler_Table : public Struct
{
public:
    Struct_Exception_Handler_Table();

    void writeStruct(DataWriter &data) const;
    void writeData(DataWriter &data) const;
    quint32 computeMemoryMap(quint32 baseAddress);
    void printMemoryMap(QTextStream &ts) const;

private:
    QList<Struct_Exception_Handler> handlers;
};

#endif // STRUCT_EXCEPTION_HANDLER_TABLE_H
