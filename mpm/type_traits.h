/** @file type_traits.h
    @author Guilherme Versiani <guibv@comunip.com.br>
    @date 8/3/2010 17:15:54
 */

// Copyright (c) 2010 ComunIP S/A. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MPM_TYPETRAITS_H
#define MPM_TYPETRAITS_H

namespace mpm {

template<typename T_type>
struct TypeTrait
{
    typedef T_type  type;
    typedef T_type& pass;
    typedef const T_type& take;
    typedef T_type* pointer;
};

template<class T_type>
struct TypeTrait<T_type&>
{
    typedef T_type  type;
    typedef T_type& pass;
    typedef T_type& take;
    typedef T_type* pointer;
};

template<class T_type>
struct TypeTrait<const T_type&>
{
    typedef const T_type  type;
    typedef const T_type& pass;
    typedef const T_type& take;
    typedef const T_type* pointer;
};

template<>
struct TypeTrait<void>
{
    typedef void  type;
    typedef void  pass;
    typedef void  take;
    typedef void* pointer;
};

} // namespace mpm

#endif // MPM_TYPETRAITS_H

/* Modeline for vim: set tw=79 et ts=4: */

