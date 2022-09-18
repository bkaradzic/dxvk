#include "../wsi_monitor.h"

#include "wsi_platform_x11.h"

#include "../../util/util_string.h"
#include "../../util/log/log.h"

#include <X11/Xlib.h>

namespace dxvk::wsi {

  HMONITOR getDefaultMonitor() {
    return enumMonitors(0);
  }


  HMONITOR enumMonitors(uint32_t index) {
    return int32_t(index) >= 0 ? ((HMONITOR)1) : nullptr;
  }

  bool getDisplayName(
          HMONITOR         hMonitor,
          WCHAR            (&Name)[32]) {

    const int32_t displayId = 0;

    std::wstringstream nameStream;
    nameStream << LR"(\\.\DISPLAY)" << (displayId + 1);

    std::wstring name = nameStream.str();

    std::memset(Name, 0, sizeof(Name));
    name.copy(Name, name.length(), 0);

    return true;
  }


  bool getDesktopCoordinates(
          HMONITOR         hMonitor,
          RECT*            pRect) {

    Logger::info(str::format("getDesktopCoordinates: ", hMonitor));

    return false;
  }


  bool getDisplayMode(
          HMONITOR         hMonitor,
          uint32_t         ModeNumber,
          WsiMode*         pMode) {

    Logger::info(str::format("getDisplayMode: ", hMonitor));

    return false;
  }


  bool getCurrentDisplayMode(
          HMONITOR         hMonitor,
          WsiMode*         pMode) {

    if (nullptr != pMode) {

      Display* display = XOpenDisplay(nullptr);
      Screen* screen = XScreenOfDisplay(display, XDefaultScreen(display));

      pMode->width  = XWidthOfScreen(screen);
      pMode->height = XHeightOfScreen(screen);
      pMode->refreshRate.numerator   = 60;
      pMode->refreshRate.denominator = 1;
      pMode->bitsPerPixel = 32;
      pMode->interlaced   = false;

      XCloseDisplay(display);

      return true;
    }

    return false;
  }


  bool getDesktopDisplayMode(
          HMONITOR         hMonitor,
          WsiMode*         pMode) {

    if (nullptr != pMode) {

      Display* display = XOpenDisplay(nullptr);
      Screen* screen = XScreenOfDisplay(display, XDefaultScreen(display));

      pMode->width  = XWidthOfScreen(screen);
      pMode->height = XHeightOfScreen(screen);
      pMode->refreshRate.numerator   = 60;
      pMode->refreshRate.denominator = 1;
      pMode->bitsPerPixel = 32;
      pMode->interlaced   = false;

      XCloseDisplay(display);

      return true;
    }

    return false;
  }

}
