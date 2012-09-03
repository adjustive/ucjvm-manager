#include "Struct_Exception_Handler_Table.h"

#include "ExceptionHandler.h"
#include "DataWriter.h"

Struct_Exception_Handler_Table::Struct_Exception_Handler_Table()
{
}

void Struct_Exception_Handler_Table::writeStruct(DataWriter &data) const
{
    data.put16(handlers.size());
}

void Struct_Exception_Handler_Table::writeData(DataWriter &data) const
{
    foreach (Struct_Exception_Handler const &handler, handlers)
        handler.write(data);
}

quint32 Struct_Exception_Handler_Table::computeMemoryMap(quint32 baseAddress)
{
    baseAddress = setMemoryAddress(baseAddress);

    for (int i = 0; i < handlers.size(); i++)
        baseAddress = handlers[i].computeMemoryMap(baseAddress);

    return baseAddress;
}

void Struct_Exception_Handler_Table::printMemoryMap(QTextStream &ts) const
{
}


void Struct_Exception_Handler_Table::add(QList<ExceptionHandler> exceptionHandlers)
{
    foreach (ExceptionHandler const &handler, exceptionHandlers)
        handlers.append(Struct_Exception_Handler(handler));
}

quint16 Struct_Exception_Handler_Table::size() const
{
    return handlers.size();
}
