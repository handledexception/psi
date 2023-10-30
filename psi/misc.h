/*
    Psi - The Micro Testing Framework for C/C++
    Language: C
    https://github.com/handledexception/psi

    Forked from the original project, Tau: https://github.com/jasmcaus/tau
    Licensed under the MIT License <http://opensource.org/licenses/MIT>
    SPDX-License-Identifier: MIT
    Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#ifndef PSI_MISCELLANEOUS_H
#define PSI_MISCELLANEOUS_H

// Casts
#ifdef __cplusplus
    #define PSI_CAST(type, x)       static_cast<type>(x)
    #define PSI_PTRCAST(type, x)    reinterpret_cast<type>(x)
#else
    #define PSI_CAST(type, x)       ((type)x)
    #define PSI_PTRCAST(type, x)    ((type)x)
#endif // __cplusplus

// printf format-string specifiers for psi_i64 and psi_u64 respectively
#if defined(_MSC_VER) && (_MSC_VER < 1920)
    #define PSI_PRId64 "I64d"
    #define PSI_PRIu64 "I64u"
#else
    // Avoid spurious trailing ‘%’ in format error
	// See: https://stackoverflow.com/questions/8132399/how-to-printf-uint64-t-fails-with-spurious-trailing-in-format
	#define __STDC_FORMAT_MACROS
    #include <inttypes.h>

    #define PSI_PRId64 PRId64
    #define PSI_PRIu64 PRIu64
#endif

#ifndef PSI_IS_SIGNED
    #define PSI_IS_SIGNED(x) (((x)-1) < 0)
#endif // PSI_IS_SIGNED

// A signed sizeof is more useful
#ifndef PSI_SIZEOF
    #define PSI_SIZEOF(x)    (psi_ll)(sizeof(x))
#endif


// Compare `SOME` and `NONE` values
#ifndef PSI_SOME
    #define PSI_SOME(x) ((x) != PSI_NULL)
#endif // PSI_SOME

#ifndef PSI_NONE
    #define PSI_NONE(x) ((x) == PSI_NULL)
#endif // PSI_NONE


// Get the type of `val`
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    #define PSI_TYPEOF(val)                                     \
        printf("%s\n",                                          \
            _Generic((val),                                     \
                    signed char : "signed char",                \
                    unsigned char : "unsigned char",            \
                    signed short : "signed short",              \
                    unsigned short : "unsigned short",          \
                    signed int : "signed int",                  \
                    unsigned int : "unsigned int",              \
                    signed long long : "signed long long",      \
                    unsigned long long : "unsigned long long",  \
                    float : "float",                            \
                    double : "double",                          \
                    default: "unknown type"                     \
                ))
#else
    #define PSI_TYPEOF(val)
#endif

#endif // PSI_MISCELLANEOUS_H
