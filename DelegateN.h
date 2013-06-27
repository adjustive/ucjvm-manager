#ifndef TPARAMS
#define TPARAMS
#define FPARAMS
#define MPARAMS
#define FARGS
#define MARGS
#endif

template<typename R TPARAMS>
struct Delegate<R(FPARAMS)> : DelegateBase
{
    Delegate()
        : DelegateBase(0)
    {
        u.ctor = 0;
    }

private:
    template<typename C, R(C::*M)(FPARAMS)>
    static R methodThunk(C *self MPARAMS)
    {
        return (self->*M)(FARGS);
    }

    template<typename C, R(C::*M)(FPARAMS) const>
    static R methodThunk(C const *self MPARAMS)
    {
        return (self->*M)(FARGS);
    }

    template<typename C>
    static R constructorThunk(FPARAMS)
    {
        return new C(FARGS);
    }

public:
    template<typename C, R(C::*M)(FPARAMS)>
    static Delegate create(C *self)
    {
        return Delegate(self, methodThunk<C, M>);
    }

    template<typename C, R(C::*M)(FPARAMS) const>
    static Delegate create(C const *self)
    {
        return Delegate(self, methodThunk<C, M>);
    }

    template<typename C>
    static Delegate constructor()
    {
        return Delegate(constructorThunk<C>);
    }

    static Delegate constructor()
    {
        return constructor<typename remove_pointer<R>::type>();
    }

    R operator()(FPARAMS) const
    {
        if (self != 0)
        {
            notNull(u.func);
            return u.func(self MARGS);
        }
        else
        {
            notNull(u.ctor);
            return u.ctor(FARGS);
        }
    }

private:
    template<typename C>
    Delegate(C *self, R(*func)(C *self MPARAMS))
        : DelegateBase(self)
    {
        notNull(func);
        u.func = reinterpret_cast<R(*)(void * MPARAMS)>(func);
    }

    template<typename C>
    Delegate(C const *self, R(*func)(C const *self MPARAMS))
        : DelegateBase(const_cast<C *>(self))
    {
        notNull(func);
        u.func = reinterpret_cast<R(*)(void * MPARAMS)>(func);
    }

    Delegate(R(*ctor)(FPARAMS))
        : DelegateBase(0)
    {
        u.ctor = ctor;
    }

private:
    union
    {
        R (*func)(void *self MPARAMS);
        R (*ctor)(FPARAMS);
    } u;
};


#undef TPARAMS
#undef FPARAMS
#undef MPARAMS
#undef FARGS
#undef MARGS
