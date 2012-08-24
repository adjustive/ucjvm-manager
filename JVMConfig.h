#ifndef JVMCONFIG_H
#define JVMCONFIG_H

#include "NativeFunction.h"

#include <QVariant>
#include <QList>

struct JVMConfigPrivate
{
    QString configName;
    QString description;
    quint32 baseAddress;
    quint32 memorySize;

    QList<NativeFunction> nativeInterface;
};


class JVMConfig
{
public:
    JVMConfig();
    explicit JVMConfig(QString path);

    QString configName() const;
    QString description() const;
    quint32 baseAddress() const;
    quint32 memorySize() const;

    QList<NativeFunction> nativeInterface() const;

private:
    JVMConfigPrivate d;
};

Q_DECLARE_METATYPE(JVMConfig)

#endif // JVMCONFIG_H
