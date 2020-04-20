/* Proposed SG14 status_code
(C) 2018-2019 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_COM_CODE_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_COM_CODE_HPP

#if !defined(_WIN32) && !defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
#error This file should only be included on Windows
#endif

#include "nt_code.hpp"
#include "win32_code.hpp"

#ifndef BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE
#include <comdef.h>
#endif

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

class _com_code_domain;
/*! (Windows only) A COM error code. Note semantic equivalence testing is only implemented for `FACILITY_WIN32`
and `FACILITY_NT_BIT`. As you can see at [https://blogs.msdn.microsoft.com/eldar/2007/04/03/a-lot-of-hresult-codes/](https://blogs.msdn.microsoft.com/eldar/2007/04/03/a-lot-of-hresult-codes/),
there are an awful lot of COM error codes, and keeping mapping tables for all of them would be impractical
(for the Win32 and NT facilities, we actually reuse the mapping tables in `win32_code` and `nt_code`).
You can, of course, inherit your own COM code domain from this one and override the `_do_equivalent()` function
to add semantic equivalence testing for whichever extra COM codes that your application specifically needs.
*/
using com_code = status_code<_com_code_domain>;
//! (Windows only) A specialisation of `status_error` for the COM error code domain.
using com_error = status_error<_com_code_domain>;

/*! (Windows only) The implementation of the domain for COM error codes and/or `IErrorInfo`.
*/
class _com_code_domain : public status_code_domain
{
  template <class DomainType> friend class status_code;
  template <class StatusCode> friend class detail::indirecting_domain;
  using _base = status_code_domain;

  //! Construct from a `HRESULT` error code
  static _base::string_ref _make_string_ref(HRESULT c, IErrorInfo *perrinfo = nullptr) noexcept
  {
    _com_error ce(c, perrinfo);
#ifdef _UNICODE
    win32::DWORD wlen = (win32::DWORD) wcslen(ce.ErrorMessage());
    size_t allocation = wlen + (wlen >> 1);
    win32::DWORD bytes;
    if(wlen == 0)
    {
      return _base::string_ref("failed to get message from system");
    }
    for(;;)
    {
      auto *p = static_cast<char *>(malloc(allocation));  // NOLINT
      if(p == nullptr)
      {
        return _base::string_ref("failed to get message from system");
      }
      bytes = win32::WideCharToMultiByte(65001 /*CP_UTF8*/, 0, ce.ErrorMessage(), wlen + 1, p, allocation, nullptr, nullptr);
      if(bytes != 0)
      {
        char *end = strchr(p, 0);
        while(end[-1] == 10 || end[-1] == 13)
        {
          --end;
        }
        *end = 0;  // NOLINT
        return _base::atomic_refcounted_string_ref(p, end - p);
      }
      free(p);  // NOLINT
      if(win32::GetLastError() == 0x7a /*ERROR_INSUFFICIENT_BUFFER*/)
      {
        allocation += allocation >> 2;
        continue;
      }
      return _base::string_ref("failed to get message from system");
    }
#else
    auto wlen = static_cast<win32::DWORD>(strlen(ce.ErrorMessage()));
    auto *p = static_cast<char *>(malloc(wlen + 1));  // NOLINT
    if(p == nullptr)
    {
      return _base::string_ref("failed to get message from system");
    }
    memcpy(p, ce.ErrorMessage(), wlen + 1);
    char *end = strchr(p, 0);
    while(end[-1] == 10 || end[-1] == 13)
    {
      --end;
    }
    *end = 0;  // NOLINT
    return _base::atomic_refcounted_string_ref(p, end - p);
#endif
  }

public:
  //! The value type of the COM code, which is a `HRESULT`
  using value_type = HRESULT;
  using _base::string_ref;

public:
  //! Default constructor
  constexpr explicit _com_code_domain(typename _base::unique_id_type id = 0xdc8275428b4effac) noexcept : _base(id) {}
  _com_code_domain(const _com_code_domain &) = default;
  _com_code_domain(_com_code_domain &&) = default;
  _com_code_domain &operator=(const _com_code_domain &) = default;
  _com_code_domain &operator=(_com_code_domain &&) = default;
  ~_com_code_domain() = default;

  //! Constexpr singleton getter. Returns the constexpr com_code_domain variable.
  static inline constexpr const _com_code_domain &get();

  virtual string_ref name() const noexcept override { return string_ref("COM domain"); }  // NOLINT
protected:
  virtual bool _do_failure(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);
    return static_cast<const com_code &>(code).value() < 0;  // NOLINT
  }
  /*! Note semantic equivalence testing is only implemented for `FACILITY_WIN32` and `FACILITY_NT_BIT`.
  */
  virtual bool _do_equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept override  // NOLINT
  {
    assert(code1.domain() == *this);
    const auto &c1 = static_cast<const com_code &>(code1);  // NOLINT
    if(code2.domain() == *this)
    {
      const auto &c2 = static_cast<const com_code &>(code2);  // NOLINT
      return c1.value() == c2.value();
    }
    if((c1.value() & FACILITY_NT_BIT) != 0)
    {
      if(code2.domain() == nt_code_domain)
      {
        const auto &c2 = static_cast<const nt_code &>(code2);  // NOLINT
        if(c2.value() == (c1.value() & ~FACILITY_NT_BIT))
        {
          return true;
        }
      }
      else if(code2.domain() == generic_code_domain)
      {
        const auto &c2 = static_cast<const generic_code &>(code2);  // NOLINT
        if(static_cast<int>(c2.value()) == _nt_code_domain::_nt_code_to_errno(c1.value() & ~FACILITY_NT_BIT))
        {
          return true;
        }
      }
    }
    else if(HRESULT_FACILITY(c1.value()) == FACILITY_WIN32)
    {
      if(code2.domain() == win32_code_domain)
      {
        const auto &c2 = static_cast<const win32_code &>(code2);  // NOLINT
        if(c2.value() == HRESULT_CODE(c1.value()))
        {
          return true;
        }
      }
      else if(code2.domain() == generic_code_domain)
      {
        const auto &c2 = static_cast<const generic_code &>(code2);  // NOLINT
        if(static_cast<int>(c2.value()) == _win32_code_domain::_win32_code_to_errno(HRESULT_CODE(c1.value())))
        {
          return true;
        }
      }
    }
    return false;
  }
  virtual generic_code _generic_code(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);
    const auto &c1 = static_cast<const com_code &>(code);  // NOLINT
    if(c1.value() == S_OK)
    {
      return generic_code(errc::success);
    }
    if((c1.value() & FACILITY_NT_BIT) != 0)
    {
      return generic_code(static_cast<errc>(_nt_code_domain::_nt_code_to_errno(c1.value() & ~FACILITY_NT_BIT)));
    }
    if(HRESULT_FACILITY(c1.value()) == FACILITY_WIN32)
    {
      return generic_code(static_cast<errc>(_win32_code_domain::_win32_code_to_errno(HRESULT_CODE(c1.value()))));
    }
    return generic_code(errc::unknown);
  }
  virtual string_ref _do_message(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);
    const auto &c = static_cast<const com_code &>(code);  // NOLINT
    return _make_string_ref(c.value());
  }
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
  BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN virtual void _do_throw_exception(const status_code<void> &code) const override  // NOLINT
  {
    assert(code.domain() == *this);
    const auto &c = static_cast<const com_code &>(code);  // NOLINT
    throw status_error<_com_code_domain>(c);
  }
#endif
};
//! (Windows only) A constexpr source variable for the COM code domain. Returned by `_com_code_domain::get()`.
constexpr _com_code_domain com_code_domain;
inline constexpr const _com_code_domain &_com_code_domain::get()
{
  return com_code_domain;
}

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif
