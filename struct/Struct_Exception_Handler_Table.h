#ifndef STRUCT_EXCEPTION_HANDLER_TABLE_H
#define STRUCT_EXCEPTION_HANDLER_TABLE_H

#include "Struct.h"

class Struct_Exception_Handler_Table : public Struct
{
public:
    Struct_Exception_Handler_Table();

    void writeThis(DataWriter &data) const;
};

#endif // STRUCT_EXCEPTION_HANDLER_TABLE_H
