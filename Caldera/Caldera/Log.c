#include "Log.h"

CaLogRecord_t caLogRecord(CaLogLevel_t level, size_t line,
        char const * func, char const * file)
{
    struct timespec tsp;
    clock_gettime(CLOCK_MONOTONIC, &tsp);
    return (CaLogRecord_t){NULL, level, *localtime(&tsp.tv_sec), tsp.tv_nsec,
        syscall(__NR_gettid), getpid(), line, func, file};
}
void caLogLog(FILE *f, CaLogLogger_t const log, CaLogRecord_t rec,
                char const *fmt, ...)
{
    rec.log_name = log.name;
    if (log.level > rec.level)
        return;

    va_list args;
    va_start (args, fmt);
    log.print(f, rec, fmt, args);
    va_end (args);
}
void caLogFuncDefault(FILE *f, CaLogRecord_t const rec, char const *fmt, ...)
{
    const char *color;
    switch (rec.level)
    {
    case CA_LOG_LEV_VERBOSE: color = "\033[37m"; break;
    case CA_LOG_LEV_DEBUG:   color = "\033[36m"; break;
    case CA_LOG_LEV_INFO:    color = "\033[32m"; break;
    case CA_LOG_LEV_WARN:    color = "\033[33m\033[1m"; break;
    case CA_LOG_LEV_ERR:     color = "\033[31m\033[1m"; break;
    case CA_LOG_LEV_FATAL:   color = "\033[1m\033[41m"; break;
    case CA_LOG_LEV_OFF:     color = "\033[0;0m"; break;
    }
    fprintf(f, "%s[%02d:%02d:%02d.%u] %s: ",
            color,
            rec.t.tm_hour,
            rec.t.tm_min,
            rec.t.tm_sec,
            rec.nsec / 1000000,
            rec.log_name
            );
    va_list args;
    va_start (args, fmt);
    vfprintf(f, fmt, args);
    va_end (args);
    fputs("\n\033[0;0m", f);
    fflush(f);
}

CaLogLogger_t caLogCore;
FILE *caLogCoreSink;

CaLogLogger_t caLogApp;
FILE *caLogAppSink;

void caLogInit(void)
{
    caLogCore = (CaLogLogger_t){"CALDERA",CA_LOG_LEV_VERBOSE,caLogFuncDefault};
    caLogApp = (CaLogLogger_t){"APP",CA_LOG_LEV_VERBOSE,caLogFuncDefault};
    caLogCoreSink = stderr;
    caLogAppSink = stderr;
}
