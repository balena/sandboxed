/** @file rpc_client_call.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 08/03/2010 21.41.08
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
    template<typename R>
    struct ClientCallTrait {
        static R invoke(Client *c, IPC::Message *m) {
            c->sendMessage(m);
            scoped_ptr<IPC::Message> msg(c->getMessage());
            if (!msg.get()) {
                Value *value = Value::CreateNullValue();
                R retval = sandboxed::ValueTrait<R>::fromValue(*value);
                return retval;
            }
            void *iter = 0;
            ListValue result;
            IPC::ParamTraits<ListValue>::Read(msg.get(), &iter, &result);
            Value *value;
            result.Get(0, &value);
            return sandboxed::ValueTrait<R>::fromValue(*value);
        }
    };

    template<>
    struct ClientCallTrait<void> {
        static void invoke(Client *c, IPC::Message *m) {
            c->sendMessage(m);
            scoped_ptr<IPC::Message> msg(c->getMessage());
            // throw away the returning message
        }
    };

    class ClientCallBase
    {
    public:
        ClientCallBase(const std::string& fn)
            : _fn(fn) {}
        virtual ~ClientCallBase() {}

    protected:
        std::string _fn;
        IPC::Message *newMessage() {
            IPC::Message *msg = new IPC::Message(1, 2,
                IPC::Message::PRIORITY_NORMAL);
            WriteParam(msg, _fn);
            return msg;
        }
    };


} // empty namespace

template<typename FnType>
class ClientCall;

template<typename R>
class ClientCall<R()>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c)
    {
        IPC::Message *msg = newMessage();
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

template<typename R, typename P1>
class ClientCall<R(P1)>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c, typename sandboxed::TypeTrait<P1>::take p1)
    {
        ListValue params;
        IPC::Message *msg = newMessage();
        params.Append(sandboxed::ValueTrait<P1>::toValue(p1));
        WriteParam(msg, params);
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

template<typename R, typename P1, typename P2>
class ClientCall<R(P1, P2)>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c, typename sandboxed::TypeTrait<P1>::take p1,
        typename sandboxed::TypeTrait<P2>::take p2)
    {
        ListValue params;
        IPC::Message *msg = newMessage();
        params.Append(sandboxed::ValueTrait<P1>::toValue(p1));
        params.Append(sandboxed::ValueTrait<P2>::toValue(p2));
        WriteParam(msg, params);
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

template<typename R, typename P1, typename P2, typename P3>
class ClientCall<R(P1, P2, P3)>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c, typename sandboxed::TypeTrait<P1>::take p1,
        typename sandboxed::TypeTrait<P2>::take p2, typename sandboxed::TypeTrait<P3>::take p3)
    {
        ListValue params;
        IPC::Message *msg = newMessage();
        params.Append(sandboxed::ValueTrait<P1>::toValue(p1));
        params.Append(sandboxed::ValueTrait<P2>::toValue(p2));
        params.Append(sandboxed::ValueTrait<P3>::toValue(p3));
        WriteParam(msg, params);
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

template<typename R, typename P1, typename P2, typename P3, typename P4>
class ClientCall<R(P1, P2, P3, P4)>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c, typename sandboxed::TypeTrait<P1>::take p1,
        typename sandboxed::TypeTrait<P2>::take p2, typename sandboxed::TypeTrait<P3>::take p3,
        typename sandboxed::TypeTrait<P4>::take p4)
    {
        ListValue params;
        IPC::Message *msg = newMessage();
        params.Append(sandboxed::ValueTrait<P1>::toValue(p1));
        params.Append(sandboxed::ValueTrait<P2>::toValue(p2));
        params.Append(sandboxed::ValueTrait<P3>::toValue(p3));
        params.Append(sandboxed::ValueTrait<P4>::toValue(p4));
        WriteParam(msg, params);
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

template<typename R, typename P1, typename P2, typename P3, typename P4,
    typename P5>
class ClientCall<R(P1, P2, P3, P4, P5)>
    : public ClientCallBase
{
public:
    ClientCall(const std::string& fn) : ClientCallBase(fn) {}
    R operator()(Client *c, typename sandboxed::TypeTrait<P1>::take p1,
        typename sandboxed::TypeTrait<P2>::take p2, typename sandboxed::TypeTrait<P3>::take p3,
        typename sandboxed::TypeTrait<P4>::take p4, typename sandboxed::TypeTrait<P5>::take p5)
    {
        ListValue params;
        IPC::Message *msg = newMessage();
        params.Append(sandboxed::ValueTrait<P1>::toValue(p1));
        params.Append(sandboxed::ValueTrait<P2>::toValue(p2));
        params.Append(sandboxed::ValueTrait<P3>::toValue(p3));
        params.Append(sandboxed::ValueTrait<P4>::toValue(p4));
        params.Append(sandboxed::ValueTrait<P5>::toValue(p5));
        WriteParam(msg, params);
        return ClientCallTrait<R>::invoke(c, msg);
    }
};

} // namespace RPC

/* Modeline for vim: set tw=79 et ts=4: */

