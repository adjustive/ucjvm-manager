#ifndef CONSTANTPOOLVISITOR_H
#define CONSTANTPOOLVISITOR_H

class ConstantPoolInfo_Class;
class ConstantPoolInfo_Double;
class ConstantPoolInfo_Fieldref;
class ConstantPoolInfo_Float;
class ConstantPoolInfo_Integer;
class ConstantPoolInfo_InterfaceMethodref;
class ConstantPoolInfo_Long;
class ConstantPoolInfo_Methodref;
class ConstantPoolInfo_NameAndType;
class ConstantPoolInfo_String;
class ConstantPoolInfo_Utf8;

class ConstantPoolVisitor
{
public:
    ConstantPoolVisitor();

    virtual void visit(ConstantPoolInfo_Class const &v) = 0;
    virtual void visit(ConstantPoolInfo_Double const &v) = 0;
    virtual void visit(ConstantPoolInfo_Fieldref const &v) = 0;
    virtual void visit(ConstantPoolInfo_Float const &v) = 0;
    virtual void visit(ConstantPoolInfo_Integer const &v) = 0;
    virtual void visit(ConstantPoolInfo_InterfaceMethodref const &v) = 0;
    virtual void visit(ConstantPoolInfo_Long const &v) = 0;
    virtual void visit(ConstantPoolInfo_Methodref const &v) = 0;
    virtual void visit(ConstantPoolInfo_NameAndType const &v) = 0;
    virtual void visit(ConstantPoolInfo_String const &v) = 0;
    virtual void visit(ConstantPoolInfo_Utf8 const &v) = 0;
};

#endif // CONSTANTPOOLVISITOR_H
