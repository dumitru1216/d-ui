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
		void g_clean_device( );
		void g_setup_rendering_state( std::function<void( )> g_function );
		void g_warp_render_state( IDirect3DDevice9* g_device );
		void g_warp_viewport( IDirect3DDevice9* g_device, sdk::vec2_t g_size );
		int g_warp_imgui( HWND g_handle_window, IDirect3DDevice9* g_device );

		BOOL g_create_device( HWND g_handle_window );
		ATOM g_register_window( HINSTANCE g_instance, LPCTSTR g_name );
		ATOM g_init_window( HINSTANCE g_instance, LPCTSTR g_class_name, LPCTSTR g_title );
	};
	inline const auto g_entry = std::make_unique< impl >( );
}