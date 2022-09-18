#pragma once

#if defined(DXVK_WSI_WIN32) || defined(DXVK_WSI_X11)
#error You shouldnt be using this code path.
#elif DXVK_WSI_SDL2
#include "wsi/native_sdl2.h"
#else
#error Unknown wsi!
#endif
