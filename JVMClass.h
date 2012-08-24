#ifndef JVMCLASS_H
#define JVMCLASS_H

#include <QString>
#include <QVariant>

#include "ConstantPool.h"
#include "Interfaces.h"
#include "Fields.h"
#include "Methods.h"
#include "Attributes.h"

struct JVMClassPrivate;

class JVMClass
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
    JVMClass();
    ~JVMClass();
    JVMClass(const JVMClass &rhs);
    JVMClass &operator =(const JVMClass &rhs);

    explicit JVMClass(QDataStream &data);
    explicit JVMClass(ConstantPool const &constantPool);

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

private:
    Q_DECLARE_PRIVATE(JVMClass)
    QSharedPointer<JVMClassPrivate> d_ptr;
};

Q_DECLARE_METATYPE(JVMClass)

#endif // JVMCLASS_H
