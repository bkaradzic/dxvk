#pragma once

#if defined(DXVK_WSI_WIN32)
#include "win32/wsi_platform_win32.h"
#elif defined(DXVK_WSI_SDL2)
#include "sdl2/wsi_platform_sdl2.h"
#elif defined(DXVK_WSI_X11)
#include "x11/wsi_platform_x11.h"
#endif
