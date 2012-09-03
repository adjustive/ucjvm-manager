#ifndef RESOLVECONTEXT_H
#define RESOLVECONTEXT_H

class Struct_ClassTable;
class Struct_CP_Table;
class Struct_Field_Table;
class Struct_Method_Table;

struct ResolveContextPrivate
{
    Struct_ClassTable const *const classTable;
    Struct_CP_Table const *const constantTable;
    Struct_Field_Table const *const fieldTable;
    Struct_Method_Table const *const methodTable;
};

class ResolveContext
{
public:
    ResolveContext();

    Struct_ClassTable const &classTable() const;
    Struct_CP_Table const &constantTable() const;
    Struct_Field_Table const &fieldTable() const;
    Struct_Method_Table const &methodTable() const;

    ResolveContext setClassTable(Struct_ClassTable const &classTable) const;
    ResolveContext setConstantTable(Struct_CP_Table const &constantTable) const;
    ResolveContext setFieldTable(Struct_Field_Table const &fieldTable) const;
    ResolveContext setMethodTable(Struct_Method_Table const &methodTable) const;

private:
    ResolveContextPrivate d;

    ResolveContext(ResolveContextPrivate d);
};

#endif // RESOLVECONTEXT_H
