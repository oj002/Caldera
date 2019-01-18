#if !defined(CALDERA_ENTRY_POINT_H_INCLUDED)
#define CALDERA_ENTRY_POINT_H_INCLUDED 1

#include "Log.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    caLogInit();
    CA_CORE_INFO("Starting up");
    caInitApplication();
    CA_CORE_INFO("Shuting down");
    caShutdownApplication();
    return EXIT_SUCCESS;
}

#endif
