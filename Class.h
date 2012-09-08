#ifndef JVMCLASS_H
#define JVMCLASS_H

#include <QString>
#include <QVariant>

#include "ConstantPool.h"
#include "Interfaces.h"
#include "Fields.h"
#include "Methods.h"
#include "Attributes.h"

struct ClassPrivate;

class Class
{
public:
    enum Access
    {
        ACC_PUBLIC   	= 0x0001,
        ACC_FINAL  		= 0x0010,
        ACC_SUPER  		= 0x0020,
        ACC_INTERFACE  	= 0x0200,
        ACC_ABSTRACT    = 0x0400
    };

public:    
    Class();
    ~Class();
    Class(const Class &rhs);
    Class &operator =(const Class &rhs);

    explicit Class(QDataStream &data);
    explicit Class(ConstantPool const &constantPool);

    void setSuperClass(const Class &classData);

    QString name() const;
    QString superName() const;

    quint16 minorVersion() const;
    quint16 majorVersion() const;

    bool isPublic() const;
    bool isFinal() const;
    bool isSuper() const;
    bool isInterface() const;
    bool isAbstract() const;

    QString flagsString() const;

    quint16 interfaceCount() const;
    quint16 fieldCount() const;
    quint16 methodCount() const;

    ConstantPool const &constantPool() const;
    Interfaces const &interfaces() const;
    Fields const &fields() const;
    Methods const &methods() const;
    Attributes const &attributes() const;

    Field const &field(int index) const;
    Method const &method(int index) const;

    quint16 staticDataSize() const;
    quint16 instanceDataSize() const;
    quint16 inheritedStaticDataSize() const;
    quint16 inheritedInstanceDataSize() const;

private:
    Q_DECLARE_PRIVATE(Class)
    QSharedPointer<ClassPrivate> d_ptr;
};

Q_DECLARE_METATYPE(Class)

#endif // JVMCLASS_H
