#ifndef STRUCT_EXCEPTIONS_H
#define STRUCT_EXCEPTIONS_H

#include "Struct.h"

#include <QList>

class Struct_Exceptions : public Struct
{
public:
    Struct_Exceptions();

    void writeThis(DataWriter &data) const;

private:
    QList<quint16> exceptions; // index into constant pool
};

#endif // STRUCT_EXCEPTIONS_H
