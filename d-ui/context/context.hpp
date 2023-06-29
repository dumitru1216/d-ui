#pragma once
#include "../includes.hpp"
#include "../entry/entry.hpp"

/* we are going to use this to define snake_case function so the code will look premium and clean */
/* retardness upcoming */
namespace ctx {
	class impl {
	public:
		void g_alloc_console( );
		HRESULT g_create_device_window( IDirect3D9* g_p_d3d, UINT g_adapter, D3DDEVTYPE g_device_type, HWND g_h_focus_window, 
							   DWORD g_behavior_flags, D3DPRESENT_PARAMETERS* g_presentation_parameters, IDirect3DDevice9** g_pp_device );

		/* state block */
		HRESULT g_create_state_block( LPDIRECT3DDEVICE9* g_device, D3DSTATEBLOCKTYPE g_block_tipe, IDirect3DStateBlock9* g_dx_block );

		/* warper */
		template<typename warp_memory>
		__forceinline void g_clean_memory( warp_memory* g_destination, std::size_t g_size ) {
			ZeroMemory( g_destination, g_size );
		}

		/* warp directx */
		void g_warp_dx( D3DPRESENT_PARAMETERS g_destination );
		
		/* warp imgui */
		void g_warp_frame( );
		void g_begin_frame( );
		void g_end_frame( );

		/* functions warper */
		HRESULT g_reset_device( D3DPRESENT_PARAMETERS g_reset_parrameter );
		void g_release_device( LPDIRECT3DDEVICE9* g_device );
		void g_release_device_pointer( LPDIRECT3D9* g_device_pointer );
		LPDIRECT3D9 g_create_device( std::uint32_t g_sdk_version );
		BOOL g_take_client_rect( HWND g_window_handle, RECT* g_screen_rect );
		BOOL g_take_window_rect( HWND g_window_handle, RECT* g_screen_rect );
		BOOL g_unregister_class( LPCSTR g_lp_class_name, HINSTANCE g_instance );
		BOOL g_destroy_window( HWND g_hwnd );
		BOOL g_show_window( HWND g_hwnd, int g_n_cmd_show );
		BOOL g_update_window( HWND g_hwnd );
		BOOL g_peek_message( LPMSG g_lp_msg, HWND g_hwnd, UINT g_w_msg_filter_min, UINT g_w_msg_filter_max, 
							 UINT g_w_remove_msg );
		BOOL g_translate_message( const MSG* g_lp_msg );
		LRESULT g_dispatch_message( const MSG* g_lp_msg );
		ATOM g_register_class( const WNDCLASSEX& g_wcex );

		/* directx_sdk warpers */
		void g_set_vertex_shader( IDirect3DDevice9* g_device, IDirect3DVertexShader9* g_shader );
		void g_set_pixel_shader( IDirect3DDevice9* g_device, IDirect3DPixelShader9* g_shader );
		void g_set_render_state( IDirect3DDevice9* g_device, D3DRENDERSTATETYPE g_state, DWORD g_value );
		void g_set_texture_stage_state( IDirect3DDevice9* g_device, DWORD g_stage, D3DTEXTURESTAGESTATETYPE g_type, DWORD g_value );
		void g_set_sampler_state( IDirect3DDevice9* g_device, DWORD g_sampler, D3DSAMPLERSTATETYPE g_type, DWORD g_value );
		void g_set_transform( IDirect3DDevice9* g_device, D3DTRANSFORMSTATETYPE g_state, const D3DMATRIX* g_matrix );
		void g_set_viewport( IDirect3DDevice9* g_device, const D3DVIEWPORT9* g_viewport );

		/* create window warper */
		HWND g_create_window_ex( DWORD g_dw_ex_style, LPCSTR g_lp_class_name, LPCSTR g_lp_window_name, DWORD g_dw_style, 
								 int g_x, int g_y, int g_width, int g_height, HWND g_hwnd_parent, HMENU g_h_menu, HINSTANCE g_h_instance, 
								 LPVOID g_lp_param );

		/* window handling */
		LRESULT g_def_window_proc( HWND g_hwnd, UINT g_u_msg, WPARAM g_w_param, LPARAM g_l_param );
	};
	inline const auto g_context = std::make_unique< impl >( );
}