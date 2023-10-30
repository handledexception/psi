/*
    Psi - The Micro Testing Framework for C/C++
    Language: C
    https://github.com/handledexception/psi

    Forked from the original project, Tau: https://github.com/jasmcaus/tau
    Licensed under the MIT License <http://opensource.org/licenses/MIT>
    SPDX-License-Identifier: MIT
    Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#ifndef PSI_TYPES_H
#define PSI_TYPES_H

#include <psi/compilers.h>

// Simple assertion checks (that don't require a message to STDOUT).
// Condition failure raises a compilation error (negative index) --> 0*2 == 0 + (-1) == -1!
// This macro is intended only for this file (psi/types.h)
#define PSI_STAT_ASSERT1__(cond, line)      typedef char static_assertion_at_line_##line[(!!(cond))*2-1]
#define PSI_STATIC_ASSERT(cond)             PSI_STAT_ASSERT1__(cond, __LINE__)

// Base types
#if defined(PSI_COMPILER_MSVC)
    #if _MSVC_VER < 1300
        typedef unsigned char     psi_u8;
        typedef signed char       psi_i8;
        typedef unsigned short    psi_u16;
        typedef signed short      psi_i16;
        typedef unsigned int      psi_u32;
        typedef signed int        psi_i32;
    #else
        typedef unsigned __int8   psi_u8;
        typedef signed __int8     psi_i8;
        typedef unsigned __int16  psi_u16;
        typedef signed __int16    psi_i16;
        typedef unsigned __int32  psi_u32;
        typedef signed __int32    psi_i32;
    #endif

    typedef unsigned __int64  psi_u64;
    typedef signed __int64    psi_i64;

#else
    #ifdef __cplusplus
        #include <cstdint>
    #else
        #include <stdint.h>
    #endif // __cplusplus

    typedef uint8_t   psi_u8;
    typedef int8_t    psi_i8;
    typedef uint16_t  psi_u16;
    typedef int16_t   psi_i16;
    typedef uint32_t  psi_u32;
    typedef int32_t   psi_i32;
    typedef uint64_t  psi_u64;
    typedef int64_t   psi_i64;
#endif // Psi Basic types/

typedef float  psi_f32;
typedef double psi_f64;

// Bool-sy
typedef psi_i8  psi_bool8;
typedef psi_i16 psi_bool16;
typedef psi_i32 psi_bool32; // Prefer this!

// The same thing as size_t
// psi_ull --> size_t
// psi_ll  --> ptrdiff_t
#if defined(_MSC_VER)
    #if !defined(_WIN64)
        typedef unsigned int psi_ull;
        typedef int          psi_ll;
    #else
        typedef psi_u64  psi_ull;
        typedef psi_i64   psi_ll;
    #endif // _WIN64
#else
    typedef psi_u64  psi_ull;
    typedef psi_i64   psi_ll;
#endif // _MSC_VER

// (U)Intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
// Are there any modern OSes (not 16 bit) where psi_iptr != ptrdiff_t/psi_ll ?
#if defined(_WIN64)
    typedef signed    __int64    psi_iptr;
    typedef unsigned  __int64    psi_uptr;
#elif defined(_WIN32)
    // To mark types changing their size, e.g. psi_iptr
    #ifndef PSI__W64
        #if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
            #define PSI__W64 __w64
        #else
            #define PSI__W64
        #endif
    #endif

    typedef PSI__W64 signed int     psi_iptr;
    typedef PSI__W64 unsigned int   psi_uptr;
#else
    typedef  uintptr_t   psi_uptr;
    typedef  intptr_t    psi_iptr;
#endif

// More Useful types/
#define PSI_NULLCHAR '\0'

#ifndef PSI_NULL
    #ifdef __cplusplus
        #if __cplusplus >= 201103L
            #define PSI_NULL    nullptr
        #else
            #define PSI_NULL    0
        #endif
    #else
        #define PSI_NULL    ((void*)0)
    #endif // __cplusplus
#endif

// bool is a basic type in C++ and not C
#ifndef PSI_BOOL_TYPES_DEFINED
#define PSI_BOOL_TYPES_DEFINED
    #ifdef __cplusplus
        #define psi_bool   bool
        #define psi_false  false
        #define psi_true   true
    #else
        typedef psi_bool32 psi_bool;
        static const psi_bool psi_false = 0;
        static const psi_bool psi_true = 1;
    #endif // __cplusplus
#endif // PSI_BOOL_TYPES_DEFINED

PSI_STATIC_ASSERT(sizeof(psi_u8) == 1);                 // integers
PSI_STATIC_ASSERT(sizeof(psi_i8) == 1);
PSI_STATIC_ASSERT(sizeof(psi_u16) == 2);
PSI_STATIC_ASSERT(sizeof(psi_i16) == 2);
PSI_STATIC_ASSERT(sizeof(psi_u32) == 4);
PSI_STATIC_ASSERT(sizeof(psi_i32) == 4);
PSI_STATIC_ASSERT(sizeof(psi_u64) == 8);
PSI_STATIC_ASSERT(sizeof(psi_i64) == 8);
PSI_STATIC_ASSERT(sizeof(psi_f32) == 4);                // floats
PSI_STATIC_ASSERT(sizeof(psi_f64) == 8);
PSI_STATIC_ASSERT(sizeof(psi_bool8) == 1);              // bools
PSI_STATIC_ASSERT(sizeof(psi_bool16) == 2);
PSI_STATIC_ASSERT(sizeof(psi_bool32)  == 4);
// pointer sizes (differs on architectures like CHERI)
PSI_STATIC_ASSERT(sizeof(psi_iptr) == sizeof(psi_ll));  // psi_ull --> size_t
PSI_STATIC_ASSERT(sizeof(psi_uptr) == sizeof(psi_ull)); // psi_ll  --> ptrdiff_t

#endif // PSI_TYPES_H
