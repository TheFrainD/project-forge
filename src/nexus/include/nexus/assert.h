#pragma once

#include <nexus/sys/log.h>

#ifdef ASSERTIONS_ENABLED

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#if defined(__i386__) || defined(__x86_64__)
#define DEBUG_BREAK() __asm__ __volatile__("int $0x03")
#elif defined(__aarch64__) || defined(__arm__)
#define DEBUG_BREAK() __builtin_trap()
#else
#include <signal.h>
#define DEBUG_BREAK() raise(SIGTRAP)
#endif
#else
#include <signal.h>
#define DEBUG_BREAK() raise(SIGTRAP)
#endif

#define NX_ASSERT(expr)                                                      \
    if (expr) {                                                              \
    } else {                                                                 \
        NX_LOG_CRITICAL("[{}:{}] Assertion failed: {}.", __FILE__, __LINE__, \
                        #expr);                                              \
        DEBUG_BREAK();                                                       \
    }

#define NX_ASSERT_MSG(expr, msg)                                      \
    if (expr) {                                                       \
    } else {                                                          \
        NX_LOG_CRITICAL("[{}:{}] Assertion failed: {}. {}", __FILE__, \
                        __LINE__, #expr, msg);                        \
        DEBUG_BREAK();                                                \
    }

#else

#define ASSERT(expr)

#endif
