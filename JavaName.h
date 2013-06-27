#ifndef JAVANAME_H
#define JAVANAME_H

#include <QString>

class JavaName
{
public:
    static QString demangle(QString mangled, QString functionName = QString(), QString className = QString());

    JavaName();
};

#endif // JAVANAME_H
