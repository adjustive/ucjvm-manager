#include "ConstantPoolInfo.h"


char const *ConstantPoolInfo::nameOfType(Type type)
{
    switch (type)
    {
    case CONSTANT_Fieldref 			: return "Fieldref";
    case CONSTANT_Class  			: return "Class";
    case CONSTANT_Methodref			: return "Methodref";
    case CONSTANT_InterfaceMethodref: return "InterfaceMethodref";
    case CONSTANT_String			: return "String";
    case CONSTANT_Integer 			: return "Integer";
    case CONSTANT_Float				: return "Float";
    case CONSTANT_Long				: return "Long";
    case CONSTANT_Double			: return "Double";
    case CONSTANT_NameAndType		: return "NameAndType";
    case CONSTANT_Utf8				: return "Utf8";
    default                         : return "<invalid>";
    }
}

ConstantPoolInfo::ConstantPoolInfo()
{
}

ConstantPoolInfo::~ConstantPoolInfo()
{
}
