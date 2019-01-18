#include <Caldera.h>
#include <stdlib.h>

void caInitApplication(void)
{
    CA_INFO(__FUNCTION__);
}
void caShutdownApplication(void)
{
    CA_INFO("test = %d", 12);
}

