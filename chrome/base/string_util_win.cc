// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/string_util.h"

#include <string.h>
#include <vector>

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/singleton.h"

namespace {

template <class char_type>
inline char_type* WriteInto(
    std::basic_string<char_type, std::char_traits<char_type>,
                      std::allocator<char_type> >* str,
    size_t length_including_null) {
  str->reserve(length_including_null);
  str->resize(length_including_null - 1);
  return &((*str)[0]);
}

std::string WideToMultiByte(const std::wstring& wide, UINT code_page) {
  if (wide.length() == 0)
    return std::string();

  // compute the length of the buffer we'll need
  int charcount = WideCharToMultiByte(code_page, 0, wide.c_str(), -1,
                                      NULL, 0, NULL, NULL);
  if (charcount == 0)
    return std::string();

  // convert
  std::string mb;
  WideCharToMultiByte(code_page, 0, wide.c_str(), -1,
                      WriteInto(&mb, charcount), charcount, NULL, NULL);

  return mb;
}

std::wstring MultiByteToWide(const std::string& src, UINT code_page) {
  if (src.length() == 0)
    return std::wstring();

  // compute the length of the buffer we'll need
  int charcount = MultiByteToWideChar(code_page, 0, src.c_str(), -1,
                                      NULL, 0);
  if (charcount == 0)
    return std::wstring();

  // convert
  std::wstring mb;
  MultiByteToWideChar(code_page, 0, src.c_str(), -1,
                      WriteInto(&mb, charcount), charcount);

  return mb;
}

}

std::string WideToUTF8(const std::wstring& wide) {
  return WideToMultiByte(wide, CP_UTF8);
}

std::wstring UTF8ToWide(const StringPiece& utf8) {
  return MultiByteToWide(utf8.as_string(), CP_UTF8);
}

bool UTF8ToWide(const char* src, size_t src_len, std::wstring* output) {
  *output = UTF8ToWide(StringPiece(src, src_len));
  return true;
}

string16 UTF8ToUTF16(const std::string& utf8)
{
  return UTF8ToWide(StringPiece(utf8.data(), utf8.length()));
}
