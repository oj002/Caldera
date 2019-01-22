#if !defined(CALDERA_LOG_H_INCLUDED)
#define CALDERA_LOG_H_INCLUDED 1

#include "Core.h"

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>

enum CaLogLevel
{
    CA_LOG_LEV_VERBOSE = 0,
    CA_LOG_LEV_DEBUG = 1,
    CA_LOG_LEV_INFO = 2,
    CA_LOG_LEV_WARN = 3,
    CA_LOG_LEV_ERR = 4,
    CA_LOG_LEV_FATAL = 5,
    CA_LOG_LEV_OFF = 6,
};
struct CaLogRecord
{
    char const *log_name;
    enum CaLogLevel level;

    struct tm t;
    unsigned long long usec; /* micro */
    pid_t tid, pid;
    size_t line;
    char const *func;
    char const *file;
};

struct CaLogLogger
{
    char const *name;
    enum CaLogLevel level;
    void (*print)(FILE *, struct CaLogRecord const, char const *, va_list);
};

extern struct CaLogLogger caLogCore;
extern FILE *caLogCoreSink;

extern struct CaLogLogger caLogApp;
extern FILE *caLogAppSink;

void caInitLogging(void);


struct CaLogRecord caCreateLogRecord(
        enum CaLogLevel level, size_t line,
        char const * func, char const * file);

void caLogLog(
        FILE *f, struct CaLogLogger const log,
        struct CaLogRecord rec, char const *fmt, ...);

void caLogFuncDefault(
        FILE *f, struct CaLogRecord const rec, char const *fmt, va_list args);


#define caLogRecord(f, log, level, ...) \
    caLogLog(f, log,\
            caCreateLogRecord(level, __LINE__, __FUNCTION__, __FILE__), \
            __VA_ARGS__)

#define caCoreVerbose(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_VERBOSE, __VA_ARGS__)
#define caCoreDebug(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_DEBUG, __VA_ARGS__)
#define caCoreInfo(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_INFO, __VA_ARGS__)
#define caCoreWarn(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_WARN, __VA_ARGS__)
#define caCoreErr(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_ERR, __VA_ARGS__)
#define caCoreFatal(...) caLogRecord( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_FATAL, __VA_ARGS__)

#define caVerbose(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_VERBOSE, __VA_ARGS__)
#define caDebug(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_DEBUG, __VA_ARGS__)
#define caInfo(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_INFO, __VA_ARGS__)
#define caWarn(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_WARN, __VA_ARGS__)
#define caErr(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_ERR, __VA_ARGS__)
#define caFatal(...) caLogRecord( \
        caLogAppSink, caLogApp, CA_LOG_LEV_FATAL, __VA_ARGS__)

#endif
