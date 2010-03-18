/** @file rpc_server_call.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 9/3/2010 11:26:03
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <sandboxed/type_traits.h>
#include <sandboxed/value_traits.h>

#include <base/scoped_ptr.h>
#include <chrome/common/ipc_message_utils.h>

namespace RPC {

namespace {

    template<class PtrObj, typename MemFun, typename MemFunProto>
    class MemFunCall;
 
    template<class PtrObj, typename MemFun, typename R>
    struct MemFunCall<PtrObj, MemFun, R()> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            R retval = (p->*memFn)();
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun>
    struct MemFunCall<PtrObj, MemFun, void()> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            (p->*memFn)();
            return Value::CreateNullValue();
        }
    };
 
    template<class PtrObj, typename MemFun, typename R, typename P1>
    struct MemFunCall<PtrObj, MemFun, R(P1)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1;
            params.Get(0, &p1);
            R retval = (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1));
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun, typename P1>
    struct MemFunCall<PtrObj, MemFun, void(P1)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1;
            params.Get(0, &p1);
            (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1));
            return Value::CreateNullValue();
        }
    };
 
    template<class PtrObj, typename MemFun, typename R, typename P1,
        typename P2>
    struct MemFunCall<PtrObj, MemFun, R(P1, P2)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2;
            params.Get(0, &p1);
            params.Get(1, &p2);
            R retval = (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2));
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun, typename P1, typename P2>
    struct MemFunCall<PtrObj, MemFun, void(P1, P2)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2;
            params.Get(0, &p1);
            params.Get(1, &p2);
            (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2));
            return Value::CreateNullValue();
        }
    };
 
    template<class PtrObj, typename MemFun, typename R, typename P1,
        typename P2, typename P3>
    struct MemFunCall<PtrObj, MemFun, R(P1, P2, P3)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            R retval = (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3));
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun, typename P1, typename P2,
        typename P3>
    struct MemFunCall<PtrObj, MemFun, void(P1, P2, P3)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3));
            return Value::CreateNullValue();
        }
    };
 
    template<class PtrObj, typename MemFun, typename R, typename P1,
        typename P2, typename P3, typename P4>
    struct MemFunCall<PtrObj, MemFun, R(P1, P2, P3, P4)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3, *p4;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            params.Get(3, &p4);
            R retval = (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3),
                sandboxed::ValueTrait<P4>::fromValue(*p4));
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun, typename P1, typename P2,
        typename P3, typename P4>
    struct MemFunCall<PtrObj, MemFun, void(P1, P2, P3, P4)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3, *p4;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            params.Get(3, &p4);
            (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3),
                sandboxed::ValueTrait<P4>::fromValue(*p4));
            return Value::CreateNullValue();
        }
    };
 
    template<class PtrObj, typename MemFun, typename R, typename P1,
        typename P2, typename P3, typename P4, typename P5>
    struct MemFunCall<PtrObj, MemFun, R(P1, P2, P3, P4, P5)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3, *p4, *p5;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            params.Get(3, &p4);
            params.Get(4, &p5);
            R retval = (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3),
                sandboxed::ValueTrait<P4>::fromValue(*p4),
                sandboxed::ValueTrait<P5>::fromValue(*p5));
            return sandboxed::ValueTrait<R>::toValue(retval);
        }
    };
 
    template<class PtrObj, typename MemFun, typename P1, typename P2,
        typename P3, typename P4, typename P5>
    struct MemFunCall<PtrObj, MemFun, void(P1, P2, P3, P4, P5)> {
        static Value *invoke(PtrObj *p, MemFun memFn,
            const ListValue &params)
        {
            Value *p1, *p2, *p3, *p4, *p5;
            params.Get(0, &p1);
            params.Get(1, &p2);
            params.Get(2, &p3);
            params.Get(3, &p4);
            params.Get(4, &p5);
            (p->*memFn)(
                sandboxed::ValueTrait<P1>::fromValue(*p1),
                sandboxed::ValueTrait<P2>::fromValue(*p2),
                sandboxed::ValueTrait<P3>::fromValue(*p3),
                sandboxed::ValueTrait<P4>::fromValue(*p4),
                sandboxed::ValueTrait<P5>::fromValue(*p5));
            return Value::CreateNullValue();
        }
    };
 
 
    class TargetCallImpl
    {
    public:
        virtual Value *operator ()(const ListValue &params)=0;
        virtual TargetCallImpl* clone() const=0;
 
        template<class U>
        static U* _clone(U* pObj)
        {
            if (!pObj) return 0;
            U* pClone = static_cast<U*>(pObj->clone());
            return pClone;
        }
    };
 
    template<class PtrObj, typename MemFun>
    class TargetCallImplBase : public TargetCallImpl
    {
    public:
        TargetCallImplBase(PtrObj *p, MemFun memFn)
            : _p(p), _memFn(memFn)
        {}
 
    protected:
        PtrObj *_p;
        MemFun _memFn;
    };

} // empty namespace

template<class PtrObj, typename MemFun, typename MemFunProto>
class MemFunHandler;

template<class PtrObj, typename MemFun, typename R>
class MemFunHandler<PtrObj, MemFun, R()>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R()>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};

template<class PtrObj, typename MemFun, typename R, typename P1>
class MemFunHandler<PtrObj, MemFun, R(P1)>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R(P1)>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};

template<class PtrObj, typename MemFun, typename R, typename P1, typename P2>
class MemFunHandler<PtrObj, MemFun, R(P1, P2)>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R(P1, P2)>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};

template<class PtrObj, typename MemFun, typename R, typename P1, typename P2,
    typename P3>
class MemFunHandler<PtrObj, MemFun, R(P1, P2, P3)>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R(P1, P2, P3)>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};

template<class PtrObj, typename MemFun, typename R, typename P1, typename P2,
    typename P3, typename P4>
class MemFunHandler<PtrObj, MemFun, R(P1, P2, P3, P4)>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R(P1, P2, P3, P4)>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};

template<class PtrObj, typename MemFun, typename R, typename P1, typename P2,
    typename P3, typename P4, typename P5>
class MemFunHandler<PtrObj, MemFun, R(P1, P2, P3, P4, P5)>
    : public TargetCallImplBase<PtrObj, MemFun>
{
public:
    MemFunHandler(PtrObj *p, MemFun memFn)
        : TargetCallImplBase<PtrObj, MemFun>(p, memFn) {}
    virtual Value *operator()(const ListValue &params) {
        return MemFunCall<PtrObj, MemFun, R(P1, P2, P3, P4, P5)>::invoke(_p, _memFn, params);
    }
    virtual TargetCallImpl* clone() const
    { return new MemFunHandler(*this); }
};


class TargetCallBase
    : public RPC::Server::Listener
{
public:
    TargetCallBase(TargetCallImpl *impl) : _impl(impl) {}
    virtual Value *invoke(const ListValue &params) {
        return (*_impl)(params);
    }

protected:
    std::auto_ptr<TargetCallImpl> _impl;
};

template<typename FnType>
class ServerCall;

template<typename R>
class ServerCall<R()>
     : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R()>(p, memFn))
    {}
};

template<typename R, typename P1>
class ServerCall<R(P1)>
     : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R(P1)>(p, memFn))
    {}
};

template<typename R, typename P1, typename P2>
class ServerCall<R(P1, P2)>
    : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R(P1, P2)>(p, memFn))
    {}
};

template<typename R, typename P1, typename P2, typename P3>
class ServerCall<R(P1, P2, P3)>
    : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R(P1, P2, P3)>(p, memFn))
    {}
};

template<typename R, typename P1, typename P2, typename P3,
    typename P4>
class ServerCall<R(P1, P2, P3, P4)>
    : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R(P1, P2, P3, P4)>(p, memFn))
    {}
};

template<typename R, typename P1, typename P2, typename P3,
    typename P4, typename P5>
class ServerCall<R(P1, P2, P3, P4, P5)>
    : public TargetCallBase
{
public:
    template<class PtrObj, typename MemFun>
    ServerCall(PtrObj *p, MemFun memFn)
        : TargetCallBase(new MemFunHandler<PtrObj, MemFun, R(P1, P2, P3, P4, P5)>(p, memFn))
    {}
};

} // namespace RPC

/* Modeline for vim: set tw=79 et ts=4: */

