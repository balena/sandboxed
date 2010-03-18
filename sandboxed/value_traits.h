/** @file value_traits.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 10/3/2010 10:05:09
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOXED_VALUE_TRAITS_H
#define SANDBOXED_VALUE_TRAITS_H

#include <string>
#include <limits>
#include <base/values.h>

#include <vector>

namespace sandboxed {

template<typename T_type>
struct ValueTrait;

template<>
struct ValueTrait<bool> {
    static bool fromValue(const Value &value) {
        bool retval = false;
        value.GetAsBoolean(&retval); // TODO errors!
        return retval;
    }
    static Value *toValue(TypeTrait<bool>::take value) {
        return new FundamentalValue(value);
    }
};

template<>
struct ValueTrait<int> {
    static int fromValue(const Value &value) {
        int retval = std::numeric_limits<int>::infinity();
        value.GetAsInteger(&retval); // TODO errors!
        return retval;
    }
    static Value *toValue(TypeTrait<int>::take value) {
        return new FundamentalValue(value);
    }
};

template<>
struct ValueTrait<double> {
    static double fromValue(const Value &value) {
        double retval = std::numeric_limits<double>::infinity();;
        value.GetAsReal(&retval); // TODO errors!
        return retval;
    }
    static Value *toValue(TypeTrait<double>::take value) {
        return new FundamentalValue(value);
    }
};

template<>
struct ValueTrait<std::string> {
    static std::string fromValue(const Value &value) {
        std::string retval = "NaN";
        value.GetAsString(&retval); // TODO errors!
        return retval;
    }
    static Value *toValue(TypeTrait<std::string>::take value) {
        return new StringValue(value);
    }
};

template<>
struct ValueTrait<std::wstring> {
    static std::wstring fromValue(const Value &value) {
        std::wstring retval = L"NaN";
        value.GetAsString(&retval); // TODO errors!
        return retval;
    }
    static Value *toValue(TypeTrait<std::wstring>::take value) {
        return new StringValue(value);
    }
};

template<typename T>
struct ValueTrait<std::vector<T>> {
    static std::vector<T> fromValue(const Value &value) {
        const ListValue &list = static_cast<const ListValue&>(value);
        std::vector<T> retval;
        for (size_t i=0; i<list.GetSize(); i++) {
            Value *elem = 0;
            list.Get(i, &elem);
            retval.push_back(ValueTrait<T>::fromValue(*elem));
        }
        return retval;
    }
    static ListValue *toValue(std::vector<T> value) {
        std::vector<T>::iterator it;
        ListValue *retval = new ListValue;
        for (it = value.begin(); it != value.end(); it++)
            retval->Append(ValueTrait<T>::toValue(*it));
        return retval;
    }
};

} // namespace sandboxed

#endif // SANDBOXED_VALUE_TRAITS_H

/* Modeline for vim: set tw=79 et ts=4: */

