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

/* main includes */