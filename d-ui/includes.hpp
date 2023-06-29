#pragma once
#pragma warning ( disable : 4005 )
#pragma warning ( disable : 26495 )
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4715 )

#define WINDOWS_IGNORE_PACKING_MISMATCH
#define WIN32_LEAN_AND_MEAN

/* includes vc++ */
#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <sstream>
#include <iostream>
#include <functional>
#include <WinUser.h>

/* directx includes */
#include <d3d9.h>
#include <d3dx9.h>

/* libs for directx */
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "freetype.lib")

/* main includes */
#include "math/math.hpp"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_win32.h"
#include "thirdparty/imgui/imgui_impl_dx9.h"

/* resources */
#define IDS_APP_TITLE 103
#define IDR_MAINFRAME 128
#define IDD_GUITEST_DIALOG 102
#define IDD_ABOUTBOX 103
#define IDM_ABOUT 104
#define IDM_EXIT 105
#define IDI_GUITEST 107
#define IDI_SMALL 108
#define IDC_GUITEST 109
#define IDC_MYICON 2
#ifndef IDC_STATIC
#define IDC_STATIC -1
#endif

/* pre_defines */
#define g_clean_memory ZeroMemory