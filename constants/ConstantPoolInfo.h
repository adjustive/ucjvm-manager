#ifndef CONSTANTPOOLINFO_H
#define CONSTANTPOOLINFO_H

class QDebug;

class ConstantPoolInfo
{
public:
    enum Type
    {
        CONSTANT_Fieldref 			= 9,
        CONSTANT_Class  			= 7,
        CONSTANT_Methodref			= 10,
        CONSTANT_InterfaceMethodref = 11,
        CONSTANT_String				= 8,
        CONSTANT_Integer 			= 3,
        CONSTANT_Float				= 4,
        CONSTANT_Long				= 5,
        CONSTANT_Double				= 6,
        CONSTANT_NameAndType		= 12,
        CONSTANT_Utf8				= 1
    };

    static char const *nameOfType(Type type);

    ConstantPoolInfo();
    virtual ~ConstantPoolInfo();

    virtual void print() const = 0;
};

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

#endif // CONSTANTPOOLINFO_H
