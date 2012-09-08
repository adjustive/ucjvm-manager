#ifndef JVMCONFIG_H
#define JVMCONFIG_H

#include "NativeFunction.h"

#include <QVariant>
#include <QList>

struct ConfigPrivate
{
    QString configName;
    QString description;
    quint32 baseAddress;
    quint32 memorySize;

    QList<NativeFunction> nativeInterface;
};


class Config
{
public:
    Config();
    explicit Config(QString path);

    QString configName() const;
    QString description() const;
    quint32 baseAddress() const;
    quint32 memorySize() const;

    QList<NativeFunction> const &nativeInterface() const;

private:
    ConfigPrivate d;
};

Q_DECLARE_METATYPE(Config)

#endif // JVMCONFIG_H
