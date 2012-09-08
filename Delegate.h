#ifndef DELEGATE_H
#define DELEGATE_H

#include <cassert>

template<typename T>
struct remove_pointer
{
    typedef T type;
};

template<typename T>
struct remove_pointer<T *>
{
    typedef T type;
};


struct DelegateBase
{
protected:
    DelegateBase(void *self)
        : self(self)
    {
    }

    template<typename T>
    static void notNull(T *ptr)
    {
        assert(ptr != 0);
    }

protected:
    void *self;
};


template<typename Signature>
struct Delegate;


#define TPARAMS
#define FPARAMS
#define MPARAMS
#define FARGS
#define MARGS
#include "DelegateN.h"

#define TPARAMS , typename T1
#define FPARAMS T1 v1
#define MPARAMS , FPARAMS
#define FARGS v1
#define MARGS , FARGS
#include "DelegateN.h"


#endif // DELEGATE_H
