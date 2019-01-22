#if !defined(CALDERA_CORE_H_INCLUDED)
#define CALDERA_CORE_H_INCLUDED 1

#include "Log.h"

#if defined(CA_ENABLE_ASSERTS)
# define caAssert(cond, msg) { if (!(cond)) \
    caErr("\nAssertion Failed: "#cond" "#msg"\nin "__FILE__" at %s on %d", \
          __FUNCTION__,__LINE__); }
# define caCoreAssert(cond, msg) { if (!(cond)) \
    caCoreErr("\nAssertion Failed: "#cond" "#msg"\nin "__FILE__" at %s on %d", \
          __FUNCTION__,__LINE__); }
#else
# define caAssert(cond, msg)
# define caCoreAssert(cond, msg)
#endif

#endif
