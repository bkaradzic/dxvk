#include "../wsi_window.h"

#include "wsi_platform_x11.h"

#include "../../util/util_string.h"
#include "../../util/log/log.h"

#include <windows.h>
#include <dlfcn.h> // dlopen, dlclose, dlsym

namespace dxvk::wsi {

  void getWindowSize(
        HWND      hWindow,
        uint32_t* pWidth,
        uint32_t* pHeight) {

    Display* display = XOpenDisplay(nullptr);
    Window   window  = (Window)hWindow;

    XWindowAttributes xwAttr;
    XGetWindowAttributes(display, window, &xwAttr);

    if (pWidth)
      *pWidth = uint32_t(xwAttr.width);

    if (pHeight)
      *pHeight = uint32_t(xwAttr.height);

    XCloseDisplay(display);
  }


  void resizeWindow(
          HWND             hWindow,
          DxvkWindowState* pState,
          uint32_t         Width,
          uint32_t         Height) {

    Display* display = XOpenDisplay(nullptr);
    Window   window  = (Window)hWindow;
    XResizeWindow(display, window, int32_t(Width), int32_t(Height) );
    XCloseDisplay(display);
  }


  bool setWindowMode(
          HMONITOR         hMonitor,
          HWND             hWindow,
    const WsiMode&         pMode) {
    return false;
  }



  bool enterFullscreenMode(
          HMONITOR         hMonitor,
          HWND             hWindow,
          DxvkWindowState* pState,
          bool             ModeSwitch) {
    return false;
  }


  bool leaveFullscreenMode(
          HWND             hWindow,
          DxvkWindowState* pState,
          bool             restoreCoordinates) {
    return false;
  }


  bool restoreDisplayMode() {
    // Don't need to do anything with X11 here.
    return true;
  }


  HMONITOR getWindowMonitor(HWND hWindow) {
    return nullptr;
  }


  bool isWindow(HWND hWindow) {
    return hWindow != nullptr;
  }


  void updateFullscreenWindow(
          HMONITOR hMonitor,
          HWND     hWindow,
          bool     forceTopmost) {
    // Don't need to do anything with X11 here.
  }


  VkResult createSurface(
          HWND                hWindow,
    const Rc<vk::InstanceFn>& vki,
          VkSurfaceKHR*       pSurface) {

    Display* display = XOpenDisplay(nullptr);
    Window   window  = (Window)hWindow;
    VkResult result  = VK_ERROR_INITIALIZATION_FAILED;

    if (nullptr != vki->vkCreateXlibSurfaceKHR) {
      VkXlibSurfaceCreateInfoKHR sci;
      sci.sType  = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
      sci.pNext  = nullptr;
      sci.flags  = 0;
      sci.dpy    = display;
      sci.window = window;
      result     = vki->vkCreateXlibSurfaceKHR(vki->instance(), &sci, nullptr, pSurface);
    }

    if (VK_SUCCESS != result
    &&  nullptr != vki->vkCreateXcbSurfaceKHR) {

      void* xcbdll = dlopen("libX11-xcb.so.1", RTLD_LOCAL|RTLD_LAZY);

      if (nullptr != xcbdll) {

        typedef xcb_connection_t* (*PFN_XGETXCBCONNECTION)(Display*);
        PFN_XGETXCBCONNECTION XGetXCBConnection = (PFN_XGETXCBCONNECTION)dlsym(xcbdll, "XGetXCBConnection");

        union { void* ptr; xcb_window_t window; } cast = { hWindow };

        VkXcbSurfaceCreateInfoKHR sci;
        sci.sType      = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        sci.pNext      = NULL;
        sci.flags      = 0;
        sci.connection = XGetXCBConnection(display);
        sci.window     = cast.window;
        result = vki->vkCreateXcbSurfaceKHR(vki->instance(), &sci, nullptr, pSurface);

        dlclose(xcbdll);
      }
    }

    return result;
  }

}
