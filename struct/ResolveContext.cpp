#include "ResolveContext.h"

#include <QtGlobal>

ResolveContextPrivate const noRCP = { 0, 0, 0, 0 };

ResolveContext::ResolveContext()
    : d(noRCP)
{
}

ResolveContext::ResolveContext(ResolveContextPrivate d)
    : d(d)
{
}


Struct_ClassTable const &ResolveContext::classTable() const
{
    Q_ASSERT(d.classTable != NULL);
    return *d.classTable;
}

Struct_CP_Table const &ResolveContext::constantTable() const
{
    Q_ASSERT(d.constantTable != NULL);
    return *d.constantTable;
}

Struct_Field_Table const &ResolveContext::fieldTable() const
{
    Q_ASSERT(d.fieldTable != NULL);
    return *d.fieldTable;
}

Struct_Method_Table const &ResolveContext::methodTable() const
{
    Q_ASSERT(d.methodTable != NULL);
    return *d.methodTable;
}


ResolveContext ResolveContext::setClassTable(const Struct_ClassTable &classTable) const
{
    ResolveContextPrivate nd = {
        &classTable,
        d.constantTable,
        d.fieldTable,
        d.methodTable,
    };

    return ResolveContext(nd);
}

ResolveContext ResolveContext::setConstantTable(const Struct_CP_Table &constantTable) const
{
    ResolveContextPrivate nd = {
        d.classTable,
        &constantTable,
        d.fieldTable,
        d.methodTable,
    };

    return ResolveContext(nd);
}

ResolveContext ResolveContext::setFieldTable(const Struct_Field_Table &fieldTable) const
{
    ResolveContextPrivate nd = {
        d.classTable,
        d.constantTable,
        &fieldTable,
        d.methodTable,
    };

    return ResolveContext(nd);
}

ResolveContext ResolveContext::setMethodTable(const Struct_Method_Table &methodTable) const
{
    ResolveContextPrivate nd = {
        d.classTable,
        d.constantTable,
        d.fieldTable,
        &methodTable,
    };

    return ResolveContext(nd);
}
