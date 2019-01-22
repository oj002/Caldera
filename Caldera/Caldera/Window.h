#if !defined(CALDERA_WINDOW_H_INCLUDED)
#define CALDERA_WINDOW_H_INCLUDED 1

#include "Core.h"
#include "Event.h"

#include <GLFW/glfw3.h>

static void CaGLFWErrorCallback(int error, const char* description)
{
    caCoreErr("GLFW Error (%d): %s", error, description);
}
void caInitWindowing(void)
{
    int success = glfwInit();
    caCoreAssert(success, "Could not intialize GLFW!");
    glfwSetErrorCallback(CaGLFWErrorCallback);
}
void caShutdownWindowing(void)
{
    glfwTerminate();
}

struct CaWindowCreateInfo
{
    char const *title;
    unsigned int width, height;
    int (*eventCallback)(const struct CaEvent *);
};
struct CaWindow
{
    struct CaWindowCreateInfo data;
    GLFWwindow *window;
};

void caCreateWindow(struct CaWindowCreateInfo *info,
                    struct CaWindow * const wnd)
{
    caCoreInfo("Creating Window %s (%u, %u)",
               info->title, info->width, info->height);
    wnd->data = *info;
    wnd->window = glfwCreateWindow((int)info->width, info->height, info->title,
                                   NULL, NULL);
    glfwMakeContextCurrent(wnd->window);
    glfwSetWindowUserPointer(wnd->window, &wnd->data);
}
void caDestroyWindow(struct CaWindow *wnd)
{
    glfwDestroyWindow(wnd->window);
}

void caWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	struct CaWindowCreateInfo *data =
        (struct CaWindowCreateInfo*)glfwGetWindowUserPointer(window);
	data->width = width;
	data->height = height;

	struct CaEvent event;
    event.type = CA_EVENT_WND_RESIZE;
    event.wndWidth = width;
    event.wndHeight = height;

	data->eventCallback(&event);
}
/*
glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
	WindowCloseEvent event;
	data.EventCallback(event);
});

glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

	switch (action)
	{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
	}
});

glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

	switch (action)
	{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
	}
});

glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

	MouseScrolledEvent event((float)xOffset, (float)yOffset);
	data.EventCallback(event);
});

glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
{
	WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

	MouseMovedEvent event((float)xPos, (float)yPos);
	data.EventCallback(event);
});
*/
#endif
