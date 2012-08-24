#ifndef JAVANAME_H
#define JAVANAME_H

#include <QString>

class JavaName
{
public:
    static QString demangle(QString mangled);

    JavaName();
};

#endif // JAVANAME_H
