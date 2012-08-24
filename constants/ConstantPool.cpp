#include "ConstantPool.h"

#include "ConstantPoolInfo_Class.h"
#include "ConstantPoolInfo_Double.h"
#include "ConstantPoolInfo_Dummy.h"
#include "ConstantPoolInfo_Fieldref.h"
#include "ConstantPoolInfo_Float.h"
#include "ConstantPoolInfo_Integer.h"
#include "ConstantPoolInfo_InterfaceMethodref.h"
#include "ConstantPoolInfo_Long.h"
#include "ConstantPoolInfo_Methodref.h"
#include "ConstantPoolInfo_NameAndType.h"
#include "ConstantPoolInfo_String.h"
#include "ConstantPoolInfo_Utf8.h"

#include <QDebug>

#include <stdexcept>

ConstantPool::ConstantPool()
{
}

void ConstantPool::parse(QDataStream &data)
{
    quint16 constantPoolSize;
    data >> constantPoolSize;

    for (int i = 1; i < constantPoolSize; i++)
    {
//        qDebug() << i << "/" << constantPoolSize;

        quint8 type;
        data >> type;

        switch ((ConstantPoolInfo::Type)type)
        {
        case ConstantPoolInfo::CONSTANT_Fieldref:
            add(new ConstantPoolInfo_Fieldref(data));
            break;
        case ConstantPoolInfo::CONSTANT_Class:
            add(new ConstantPoolInfo_Class(data));
            break;
        case ConstantPoolInfo::CONSTANT_Methodref:
            add(new ConstantPoolInfo_Methodref(data));
            break;
        case ConstantPoolInfo::CONSTANT_InterfaceMethodref:
            add(new ConstantPoolInfo_InterfaceMethodref(data));
            break;
        case ConstantPoolInfo::CONSTANT_String:
            add(new ConstantPoolInfo_String(data));
            break;
        case ConstantPoolInfo::CONSTANT_Integer:
            add(new ConstantPoolInfo_Integer(data));
            break;
        case ConstantPoolInfo::CONSTANT_Float:
            add(new ConstantPoolInfo_Float(data));
            break;
        case ConstantPoolInfo::CONSTANT_Long:
            add(new ConstantPoolInfo_Long(data));
            i++;
            add(new ConstantPoolInfo_Dummy());
            break;
        case ConstantPoolInfo::CONSTANT_Double:
            add(new ConstantPoolInfo_Double(data));
            i++;
            add(new ConstantPoolInfo_Dummy());
            break;
        case ConstantPoolInfo::CONSTANT_NameAndType:
            add(new ConstantPoolInfo_NameAndType(data));
            break;
        case ConstantPoolInfo::CONSTANT_Utf8:
            add(new ConstantPoolInfo_Utf8(data));
            break;

        default:
            qDebug() << ConstantPoolInfo::nameOfType((ConstantPoolInfo::Type)type) << "at" << data.device()->pos();
            throw std::runtime_error("invalid type");
        }
    }
}

void ConstantPool::add(ConstantPoolInfo *constant)
{
//    constant->print();
    constants.append(QSharedPointer<ConstantPoolInfo>(constant));
}
