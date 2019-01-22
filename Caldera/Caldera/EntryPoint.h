#if !defined(CALDERA_ENTRY_POINT_H_INCLUDED)
#define CALDERA_ENTRY_POINT_H_INCLUDED 1

#include "Log.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    /* Not used for now */
    (void)argc;
    (void)argv;

    caInitLogging();
    caCoreVerbose("Starting up");
    caInitWindowing();
    caInitApplication();

    caRunApplication();
    caShutdownWindowing();
    caCoreVerbose("Shuting down");
    caShutdownApplication();
    return EXIT_SUCCESS;
}

#endif
