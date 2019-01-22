#include "Log.h"

struct CaLogLogger caLogCore;
FILE *caLogCoreSink;

struct CaLogLogger caLogApp;
FILE *caLogAppSink;

void caInitLogging(void)
{
    caLogCore = (struct CaLogLogger){"CALDERA",CA_LOG_LEV_VERBOSE,caLogFuncDefault};
    caLogApp = (struct CaLogLogger){"APP",CA_LOG_LEV_VERBOSE,caLogFuncDefault};
    caLogCoreSink = stderr;
    caLogAppSink = stderr;
}

struct CaLogRecord caCreateLogRecord(
        enum CaLogLevel level, size_t line,
        char const * func, char const * file)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (struct CaLogRecord){
        NULL, level, *localtime(&tv.tv_sec), tv.tv_usec,
        syscall(__NR_gettid), getpid(), line, func, file};
}
void caLogLog(
        FILE *f, struct CaLogLogger const log,
        struct CaLogRecord rec, char const *fmt, ...)
{
    rec.log_name = log.name;
    if (log.level > rec.level)
        return;

    va_list args;
    va_start (args, fmt);
    log.print(f, rec, fmt, args);
    va_end (args);
}
void caLogFuncDefault(
        FILE *f, struct CaLogRecord const rec, char const *fmt, va_list args)
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
    fprintf(f, "%s[%02d:%02d:%02d.%llu] %s: ",
            color,
            rec.t.tm_hour,
            rec.t.tm_min,
            rec.t.tm_sec,
            rec.usec,
            rec.log_name
            );
    vfprintf(f, fmt, args);
    fputs("\n\033[0;0m", f);
    fflush(f);
}

