#pragma once
#include "../includes.hpp"

/* some defines */
static HWND g_window_handle;
static LPDIRECT3D9 g_d3d9_handle = NULL;
static LPDIRECT3DDEVICE9 g_device_handle = NULL;
static D3DPRESENT_PARAMETERS g_d3d9_pp_handle = {};

/* namespace and class */
namespace entry {
	class impl {
	public:
		void g_reset_device( );
	};
	inline const auto g_entry = std::make_unique< impl >( );
}