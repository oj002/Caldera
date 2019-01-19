#if !defined(CALDERA_EVENTS_EVENT_H_INCLUDED)
#define CALDERA_EVENTS_EVENT_H_INCLUDED 1

#include "Caldera/Core.h"

enum CaEventType
{
    CA_EVENT_NONE = 0,

    CA_EVENT_WND_CLOSE, CA_EVENT_WND_RESIZE,
    CA_EVENT_WND_FOCUS, CA_EVENT_WND_LOST_FOCUS,
    CA_EVENT_WND_MOVED,

    CA_EVENT_APP_TICK, CA_EVENT_APP_UPDATE,
    CA_EVENT_APP_RENDER,

    CA_EVENT_KEY_PRESSED, CA_EVENT_KEY_RELEASED,

    CA_EVENT_MOUSE_MOVED, CA_EVENT_MOUSE_SCROLLED,
    CA_EVENT_MOUSE_BUTTON_PRESSED, CA_EVENT_MOUSE_BUTTON_RELEASED,
};
enum CaEventCategory
{
	None = 0,
	CA_EVENT_CATEGORY_APPLICATION   = 1 << 0,
	CA_EVENT_CATEGORY_INPUT         = 1 << 1,
	CA_EVENT_CATEGORY_KEYBOARD      = 1 << 2,
	CA_EVENT_CATEGORY_MOUSE         = 1 << 3,
	CA_EVENT_CATEGORY_MOUSE_BUTTON  = 1 << 4
};
struct CaEvent
{
    enum CaEventType type;
    enum CaEventCategory category;
    int handled;
    union
    {
        struct { unsigned int wndWidth, wndHeight; };/* WindowResize */
        struct { int keyCode, repeatCount; };        /* Key{Press/Release} */
        struct { float mouseX, mouseY; };            /* MouseMoved */
        struct { float xOffset, yOffset; };          /* MouseScroll */
        struct { int button; };                      /* Mouse{Press/Relese} */
    };
};

#endif
