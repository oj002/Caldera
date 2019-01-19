#if !defined(CALDERA_ENTRY_POINT_H_INCLUDED)
#define CALDERA_ENTRY_POINT_H_INCLUDED 1

#include "Log.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
    /* Not used for now */
    (void)argc;
    (void)argv;

    caLogInit();
    caCoreVerbose("Starting up");
    caInitApplication();

    caRunApplication();

    caCoreVerbose("Shuting down");
    caShutdownApplication();
    return EXIT_SUCCESS;
}

#endif
