#include "Application.h"

#include "Event.h"
#include "Log.h"

void caRunApplication(void)
{
    struct CaEvent e;
    e.type = CA_EVENT_WND_RESIZE;
    e.handled = 0;
    e.wndWidth = 1280;
    e.wndHeight = 720;
    switch (e.type)
    {
    case CA_EVENT_WND_RESIZE:
        caCoreInfo("WindowMoved {%d, %d}", e.wndWidth, e.wndHeight);
        break;
    default:
        break;
    }

}
