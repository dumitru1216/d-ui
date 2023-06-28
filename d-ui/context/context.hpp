#pragma once
#include "../includes.hpp"
#include "../entry/entry.hpp"

/* we are going to use this to define snake_case function so the code will look premium and clean */
/* retardness upcoming */
namespace ctx {
	class impl {
	public:
		void g_alloc_console( );
		BOOL g_handle_device( HWND g_window_handle, LPDIRECT3D9* g_destination, 
							  D3DPRESENT_PARAMETERS g_destination_p, LPDIRECT3DDEVICE9 g_destination_dev );
		
		/* state block */
		HRESULT g_create_state_block( LPDIRECT3DDEVICE9* g_device, D3DSTATEBLOCKTYPE g_block_tipe, IDirect3DStateBlock9* g_dx_block );

		/* warper */
		template<typename warp_memory>
		void g_clean_memory( warp_memory* g_destination, std::size_t g_size );

		/* warp directx */
		void g_warp_dx( D3DPRESENT_PARAMETERS g_destination );

		/* functions warper */
		HRESULT g_reset_device( D3DPRESENT_PARAMETERS g_reset_parrameter );
		void g_release_device( LPDIRECT3DDEVICE9* g_device );
		void g_release_device_pointer( LPDIRECT3D9* g_device_pointer );
		LPDIRECT3D9 g_create_device( std::uint32_t g_sdk_version );
		BOOL g_take_client_rect( HWND g_window_handle, RECT* g_screen_rect );

		/* directx_sdk warpers */
		void g_set_vertex_shader( IDirect3DDevice9* g_device, IDirect3DVertexShader9* g_shader );
		void g_set_pixel_shader( IDirect3DDevice9* g_device, IDirect3DPixelShader9* g_shader );
		void g_set_render_state( IDirect3DDevice9* g_device, D3DRENDERSTATETYPE g_state, DWORD g_value );
		void g_set_texture_stage_state( IDirect3DDevice9* g_device, DWORD g_stage, D3DTEXTURESTAGESTATETYPE g_type, DWORD g_value );
		void g_set_sampler_state( IDirect3DDevice9* g_device, DWORD g_sampler, D3DSAMPLERSTATETYPE g_type, DWORD g_value );
		void g_set_transform( IDirect3DDevice9* g_device, D3DTRANSFORMSTATETYPE g_state, const D3DMATRIX* g_matrix );
		void g_set_viewport( IDirect3DDevice9* g_device, const D3DVIEWPORT9* g_viewport );
	};
	inline const auto g_context = std::make_unique< impl >( );
}