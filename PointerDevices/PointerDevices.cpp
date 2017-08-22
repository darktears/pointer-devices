// PointerDevices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>

int main()
{
  UINT32 device_count = 0;
  if (!GetPointerDevices(&device_count, NULL)) {
    DWORD error_code = ::GetLastError();
    std::cout << "Error calling GetPointerDevices, error code : " << error_code << std::endl;
  }

  std::cout << "GetPointerDevices found " << device_count << " devices." <<std::endl;
  if (device_count == 0) {
    system("pause");
    return 0;
  }

  POINTER_DEVICE_INFO* devices = (POINTER_DEVICE_INFO*) malloc (sizeof(POINTER_DEVICE_INFO) * device_count);
  if (devices == NULL)
    std::cout << "Couldn't allocated devices pointers";

  if (!GetPointerDevices(&device_count, devices)) {
    DWORD error_code = ::GetLastError();
    std::cout << "Error getting devices with GetPointerDevices, error code : " << error_code << std::endl;
  }

  std::cout << "Found devices :" << std::endl;

  for (unsigned i = 0; i < device_count; ++i) {
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << " Product String : " << devices[i].productString << std::endl;
    std::cout << " Pointer device type : ";
    POINTER_DEVICE_TYPE type = devices[i].pointerDeviceType;
    if (type == POINTER_DEVICE_TYPE_EXTERNAL_PEN)
      std::cout << "Indirect pen digitizer (not integrated into display)." << std::endl;
    if (type == POINTER_DEVICE_TYPE_INTEGRATED_PEN)
      std::cout << "Direct pen digitizer (integrated into display)." << std::endl;
    if (type == POINTER_DEVICE_TYPE_TOUCH)
      std::cout << "Touch Digitizer" << std::endl;
    if (type == POINTER_DEVICE_TYPE_TOUCH_PAD)
      std::cout << "Touchpad digitizer (Windows 8.1 and later)." << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
  }

  system("pause");
  return 0;
}

