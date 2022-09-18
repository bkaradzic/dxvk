#include "../dxvk_platform_exts.h"

namespace dxvk {

  DxvkPlatformExts DxvkPlatformExts::s_instance;

  std::string_view DxvkPlatformExts::getName() {
    return "X11 WSI";
  }


  DxvkNameSet DxvkPlatformExts::getInstanceExtensions() {
    DxvkNameSet names;
    names.add(VK_KHR_XCB_SURFACE_EXTENSION_NAME);

    return names;
  }


  DxvkNameSet DxvkPlatformExts::getDeviceExtensions(
          uint32_t      adapterId) {
    return DxvkNameSet();
  }


  void DxvkPlatformExts::initInstanceExtensions() {

  }


  void DxvkPlatformExts::initDeviceExtensions(
    const DxvkInstance* instance) {

  }

}
