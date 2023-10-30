/*
    Psi - The Micro Testing Framework for C/C++
    Language: C
    https://github.com/handledexception/psi

    Forked from the original project, Tau: https://github.com/jasmcaus/tau
    Licensed under the MIT License <http://opensource.org/licenses/MIT>
    SPDX-License-Identifier: MIT
    Copyright (c) 2021 Jason Dsouza <@jasmcaus>
*/

#ifndef PSI_COMPILERS_H
#define PSI_COMPILERS_H

// Compilers
// Why is Clang here? See https://stackoverflow.com/a/66722270
#if defined(_MSC_VER) && !defined(__clang__)
    #define PSI_COMPILER_MSVC 1
#elif defined(__clang__)
    #define PSI_COMPILER_CLANG 1
#elif defined(__GNUC__) && !defined(INTEL_COMPILER) && !defined(llvm)
    #define PSI_COMPILER_GCC 1
#else
    #error Unknown Compiler (Psi currently supports only MSVC, GCC and Clang)
#endif

// Disable Compiler Warnings
// These are a big nuisance when compiling with external code
#if defined(PSI_COMPILER_MSVC)
    #define PSI_MSVC_SUPPRESS_WARNING_PUSH     __pragma(warning(push))
    #define PSI_MSVC_SUPPRESS_WARNING(w)       __pragma(warning(disable : w))
    #define PSI_MSVC_SUPPRESS_WARNING_POP      __pragma(warning(pop))
#else
    #define PSI_MSVC_SUPPRESS_WARNING_PUSH
    #define PSI_MSVC_SUPPRESS_WARNING(w)
    #define PSI_MSVC_SUPPRESS_WARNING_POP
#endif // PSI_COMPILER_MSVC

#if defined(PSI_COMPILER_CLANG)
    #define PRAGMA_TO_STR(x)                    _Pragma(#x)
    #define PSI_CLANG_SUPPRESS_WARNING_PUSH    _Pragma("clang diagnostic push")
    #define PSI_CLANG_SUPPRESS_WARNING_POP     _Pragma("clang diagnostic pop")
    #define PSI_CLANG_SUPPRESS_WARNING(w)      PRAGMA_TO_STR(clang diagnostic ignored w)
#else
    #define PSI_CLANG_SUPPRESS_WARNING_PUSH
    #define PSI_CLANG_SUPPRESS_WARNING(w)
    #define PSI_CLANG_SUPPRESS_WARNING_POP
#endif // PSI_COMPILER_CLANG

#if defined(PSI_COMPILER_GCC)
    #define PRAGMA_TO_STR(x)                    _Pragma(#x)
    #define PSI_GCC_SUPPRESS_WARNING_PUSH      _Pragma("GCC diagnostic push")
    #define PSI_GCC_SUPPRESS_WARNING_POP       _Pragma("GCC diagnostic pop")
    #define PSI_GCC_SUPPRESS_WARNING(w)        PRAGMA_TO_STR(GCC diagnostic ignored w)
#else
    #define PSI_GCC_SUPPRESS_WARNING_PUSH
    #define PSI_GCC_SUPPRESS_WARNING(w)
    #define PSI_GCC_SUPPRESS_WARNING_POP
#endif // PSI_COMPILER_GCC

#ifndef PSI_DISABLE_DEBUG_WARNINGS
#define PSI_DISABLE_DEBUG_WARNINGS                                                                    \
    /* MSVC Warnings */                                                                               \
    PSI_MSVC_SUPPRESS_WARNING_PUSH                                                                    \
    /* Conditional expression is constant */                                                          \
    PSI_MSVC_SUPPRESS_WARNING(4127)                                                                   \
    /* Assignment within conditional expression */                                                    \
    PSI_MSVC_SUPPRESS_WARNING(4706)                                                                   \
    /* Unreferenced inline function has been removed */                                               \
    PSI_MSVC_SUPPRESS_WARNING(4514)                                                                   \
    /* Function not inlined*/                                                                         \
    PSI_MSVC_SUPPRESS_WARNING(4710)                                                                   \
    /* function 'x' selected for automatic inline expansion */                                        \
    PSI_MSVC_SUPPRESS_WARNING(4711)                                                                   \
    /* No function prototype given: converting '()' to '(void)' */                                    \
    PSI_MSVC_SUPPRESS_WARNING(4255)                                                                   \
    /* '__cplusplus' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif' */    \
    PSI_MSVC_SUPPRESS_WARNING(4668)                                                                   \
    /* 'fprintf' : format string '' requires an argument of type 'unsigned __int64', but variadic */  \
    /* argument 1 has type 'size_t' */                                                                \
    PSI_MSVC_SUPPRESS_WARNING(4777)                                                                   \
    /* https://stackoverflow.com/questions/39479163 - what's the difference between 4018 and 4389 */  \
    /* signed/unsigned mismatch */                                                                    \
    PSI_MSVC_SUPPRESS_WARNING(4388)                                                                   \
    /* expression' : signed/unsigned mismatch */                                                      \
    PSI_MSVC_SUPPRESS_WARNING(4018)                                                                   \
    /* Conversion from 'int' to 'unsigned long', signed/unsigned mismatch */                          \
    PSI_MSVC_SUPPRESS_WARNING(4365)                                                                   \
    /* format string expected in argument 'x' is not a string literal */                              \
    PSI_MSVC_SUPPRESS_WARNING(4774)                                                                   \
    /* 'var' : conversion from 'x' to 'y', possible loss of data */                                   \
    PSI_MSVC_SUPPRESS_WARNING(4267)                                                                   \
    /* In multi-platform code, we cannot use the non-standard "safe" functions from */                \
    /* Microsoft's C lib like e.g. sprintf_s() instead of standard sprintf(). */                      \
    PSI_MSVC_SUPPRESS_WARNING(4996)                                                                   \
    /* warning C4090: '=': different 'const' qualifiers */                                            \
    PSI_MSVC_SUPPRESS_WARNING(4090)                                                                   \
    /* io.h contains definitions for some structures with natural padding. This is uninteresting, */  \
    /* but for some reason, MSVC's behaviour is to warn about including this system header. That  */  \
    /* *is* interesting */                                                                            \
    PSI_MSVC_SUPPRESS_WARNING(4820)                                                                   \
    /* Miscellaneous */                                                                               \
    PSI_MSVC_SUPPRESS_WARNING(4061)                                                                   \
    PSI_MSVC_SUPPRESS_WARNING(4100)                                                                   \
    PSI_MSVC_SUPPRESS_WARNING(4201)                                                                   \
    PSI_MSVC_SUPPRESS_WARNING(5045)                                                                   \
    PSI_MSVC_SUPPRESS_WARNING(5105)                                                                   \
                                                                                                      \
    /* Clang */                                                                                       \
    PSI_CLANG_SUPPRESS_WARNING_PUSH                                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wdisabled-macro-expansion")                                          \
    PSI_CLANG_SUPPRESS_WARNING("-Wlanguage-extension-token")                                          \
    PSI_CLANG_SUPPRESS_WARNING("-Wc++98-compat")                                                      \
    PSI_CLANG_SUPPRESS_WARNING("-Wc++98-compat-pedantic")                                             \
    PSI_CLANG_SUPPRESS_WARNING("-Wfloat-equal")                                                       \
    PSI_CLANG_SUPPRESS_WARNING("-Wmissing-variable-declarations")                                     \
    PSI_CLANG_SUPPRESS_WARNING("-Wreserved-id-macro")                                                 \
    PSI_CLANG_SUPPRESS_WARNING("-Wunknown-pragmas")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wstrict-overflow")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wstrict-aliasing")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wsign-compare")                                                      \
    PSI_CLANG_SUPPRESS_WARNING("-Wsign-conversion")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-macros")                                                     \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-function")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-variable")                                                   \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-result")                                                     \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-parameter")                                                  \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-local-typedefs")                                             \
    PSI_CLANG_SUPPRESS_WARNING("-Wswitch")                                                            \
    PSI_CLANG_SUPPRESS_WARNING("-Wswitch-enum")                                                       \
    PSI_CLANG_SUPPRESS_WARNING("-Wswitch-default")                                                    \
    PSI_CLANG_SUPPRESS_WARNING("-Wformat")                                                            \
    PSI_CLANG_SUPPRESS_WARNING("-Wformat-extra-args")                                                 \
    PSI_CLANG_SUPPRESS_WARNING("-Wignored-qualifiers")                                                \
    PSI_CLANG_SUPPRESS_WARNING("-Wuninitialized")                                                     \
    PSI_CLANG_SUPPRESS_WARNING("-Wunused-const-variable")                                             \
    PSI_CLANG_SUPPRESS_WARNING("-Wnewline-eof")                                                       \
    PSI_CLANG_SUPPRESS_WARNING("-Wdeprecated-declarations")                                           \
                                                                                                      \
    /* GCC */                                                                                         \
    PSI_GCC_SUPPRESS_WARNING_PUSH                                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wunknown-pragmas")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wpragmas")                                                             \
    PSI_GCC_SUPPRESS_WARNING("-Wmaybe-uninitialized")                                                 \
    PSI_GCC_SUPPRESS_WARNING("-Wmultistatement-macros")                                               \
    PSI_GCC_SUPPRESS_WARNING("-Wdiscarded-qualifiers")                                                \
    PSI_GCC_SUPPRESS_WARNING("-Wdisabled-macro-expansion")                                            \
    PSI_GCC_SUPPRESS_WARNING("-Wlanguage-extension-token")                                            \
    PSI_GCC_SUPPRESS_WARNING("-Wc++98-compat")                                                        \
    PSI_GCC_SUPPRESS_WARNING("-Wc++98-compat-pedantic")                                               \
    PSI_GCC_SUPPRESS_WARNING("-Wfloat-equal")                                                         \
    PSI_GCC_SUPPRESS_WARNING("-Wmissing-variable-declarations")                                       \
    PSI_GCC_SUPPRESS_WARNING("-Wreserved-id-macro")                                                   \
    PSI_GCC_SUPPRESS_WARNING("-Wunknown-pragmas")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wstrict-overflow")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wstrict-aliasing")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wsign-compare")                                                        \
    PSI_GCC_SUPPRESS_WARNING("-Wsign-conversion")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-macros")                                                       \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-function")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-variable")                                                     \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-result")                                                       \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-parameter")                                                    \
    PSI_GCC_SUPPRESS_WARNING("-Wunused-local-typedefs")                                               \
    PSI_GCC_SUPPRESS_WARNING("-Wswitch")                                                              \
    PSI_GCC_SUPPRESS_WARNING("-Wswitch-enum")                                                         \
    PSI_GCC_SUPPRESS_WARNING("-Wswitch-default")                                                      \
    PSI_GCC_SUPPRESS_WARNING("-Wformat")                                                              \
    PSI_GCC_SUPPRESS_WARNING("-Wformat-extra-args")                                                   \
    PSI_GCC_SUPPRESS_WARNING("-Wsuggest-attribute=format")                                            \
    PSI_GCC_SUPPRESS_WARNING("-Wdeprecated-declarations")
#endif // PSI_DISABLE_DEBUG_WARNINGS

#ifndef PSI_DISABLE_DEBUG_WARNINGS_POP
#define PSI_DISABLE_DEBUG_WARNINGS_POP     \
    PSI_MSVC_SUPPRESS_WARNING_POP          \
    PSI_CLANG_SUPPRESS_WARNING_POP         \
    PSI_GCC_SUPPRESS_WARNING_POP
#endif // PSI_DISABLE_DEBUG_WARNINGS_POP

#endif // PSI_COMPILERS_H
