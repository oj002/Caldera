#if !defined(CALDERA_LOG_H_INCLUDED)
#define CALDERA_LOG_H_INCLUDED 1

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>

typedef enum CaLogLevel_t
{
    CA_LOG_LEV_VERBOSE = 0,
    CA_LOG_LEV_DEBUG = 1,
    CA_LOG_LEV_INFO = 2,
    CA_LOG_LEV_WARN = 3,
    CA_LOG_LEV_ERR = 4,
    CA_LOG_LEV_FATAL = 5,
    CA_LOG_LEV_OFF = 6,
} CaLogLevel_t;
typedef struct CaLogRecord_t
{
    char const *log_name;
    CaLogLevel_t level;

    struct tm t;
    unsigned long long nsec;
    pid_t tid, pid;
    size_t line;
    char const *func;
    char const *file;
} CaLogRecord_t;

typedef void(*CaLogPrintCallback_t)
    (FILE *f, CaLogRecord_t const rec, char const *fmt, ...);

typedef struct CaLogLogger_t
{
    char const *name;
    CaLogLevel_t level;
    CaLogPrintCallback_t print;
} CaLogLogger_t;

CaLogRecord_t caLogRecord(CaLogLevel_t level, size_t line,
        char const * func, char const * file);

void caLogLog(FILE *f, CaLogLogger_t const log, CaLogRecord_t rec,
                char const *fmt, ...);

void caLogFuncDefault(FILE *f, CaLogRecord_t const rec, char const *fmt, ...);

void caLogInit(void);

extern CaLogLogger_t caLogCore;
extern FILE *caLogCoreSink;

extern CaLogLogger_t caLogApp;
extern FILE *caLogAppSink;

#define CA_LOG_RECORD(level) \
    caLogRecord(level, __LINE__, __FUNCTION__, __FILE__)

#define CA_LOG_LOG_(f, log, level, ...) \
    caLogLog(f, log, CA_LOG_RECORD(level), __VA_ARGS__)

#define CA_CORE_VERBOSE(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_VERBOSE, __VA_ARGS__)
#define CA_CORE_DEBUG(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_DEBUG, __VA_ARGS__)
#define CA_CORE_INFO(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_INFO, __VA_ARGS__)
#define CA_CORE_WARN(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_WARN, __VA_ARGS__)
#define CA_CORE_ERR(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_ERR, __VA_ARGS__)
#define CA_CORE_FATAL(...) CA_LOG_LOG_( \
        caLogCoreSink, caLogCore, CA_LOG_LEV_FATAL, __VA_ARGS__)

#define CA_VERBOSE(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_VERBOSE, __VA_ARGS__)
#define CA_DEBUG(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_DEBUG, __VA_ARGS__)
#define CA_INFO(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_INFO, __VA_ARGS__)
#define CA_WARN(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_WARN, __VA_ARGS__)
#define CA_ERR(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_ERR, __VA_ARGS__)
#define CA_FATAL(...) CA_LOG_LOG_( \
        caLogAppSink, caLogApp, CA_LOG_LEV_FATAL, __VA_ARGS__)

#endif
