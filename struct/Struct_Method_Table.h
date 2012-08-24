#ifndef STRUCT_METHOD_TABLE_H
#define STRUCT_METHOD_TABLE_H

#include "Struct_Method.h"
class Methods;

#include <QList>

class Struct_Method_Table : public Struct
{
public:
    Struct_Method_Table(Methods const &methods);

    void writeThis(DataWriter &data) const;

private:
    QList<Struct_Method> methods;
};

#endif // STRUCT_METHOD_TABLE_H
