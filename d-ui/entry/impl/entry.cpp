#include "../entry.hpp"
#include "../../context/context.hpp"

void entry::impl::g_reset_device( ) {
	HRESULT result{};

	/* store out in result */
	result = ctx::g_context.get( )->g_reset_device( g_d3d9_pp_handle );
	if ( result != D3DERR_INVALIDCALL ) { }
}

void entry::impl::g_clean_device( ) {
	/*
		if g_device_handle is not NULL, releases the device and sets it to NULL.
		if g_d3d9_handle is not NULL, releases g_d3d9_handle and sets it to NULL.
	*/
	if ( g_device_handle ) {
		ctx::g_context.get( )->g_release_device( &g_device_handle );
	}
	if ( g_d3d9_handle ) { 
		ctx::g_context.get( )->g_release_device_pointer( &g_d3d9_handle );
	}
}

BOOL entry::impl::g_create_device( HWND handle_window ) {
	if ( ( g_d3d9_handle = ctx::g_context.get( )->g_create_device( D3D_SDK_VERSION ) ) == 0 ) {
		return false;
	}

	/*
		zeros out the memory of g_d3d9pp by setting all its bytes to zero.
		the size of g_d3d9pp is determined by sizeof( g_d3d9pp ).
	*/
	ctx::g_context.get( )->g_clean_memory( &g_d3d9_handle, sizeof( g_d3d9_handle ) );

	/* warp dx */
	ctx::g_context.get( )->g_warp_dx( g_d3d9_pp_handle );

	/* handle device */
	ctx::g_context.get( )->g_handle_device( g_window_handle, &g_d3d9_handle, g_d3d9_pp_handle, g_device_handle );

	/* return now */
	return TRUE;
}

void entry::impl::g_setup_rendering_state( std::function<void( )> g_function ) {
	IDirect3DStateBlock9* g_state_block{ NULL }; /* im going to initialize it directly */

	/*
		if the context's g_create_state_block function returns a value less than 0 when called with g_device_handle, D3DSBT_ALL,
		and directx_state_block as arguments, then return from the current function.
	*/
	if ( ctx::g_context.get( )->g_create_state_block( &g_device_handle, D3DSBT_ALL, g_state_block ) < 0 ) {
		return;
	}

	/* screen base */
	RECT g_screen_rect{};
	ctx::g_context.get( )->g_take_client_rect( g_window_handle, &g_screen_rect );

	/* display size, we are going to directly initialize it */
	sdk::vec2_t display_size{ sdk::vec2_t(
		( float )( g_screen_rect.right - g_screen_rect.left ), ( float )( g_screen_rect.bottom - g_screen_rect.top )
	) };

	/* warp render states */
	g_warp_render_state( g_device_handle ); /* entry::g_entry.get()-> / if you want to go in that side */

	/* viewport */
	g_warp_viewport( g_device_handle, display_size );
}

/* warp render state */
void entry::impl::g_warp_render_state( IDirect3DDevice9* g_device ) {
	ctx::g_context.get( )->g_set_pixel_shader( g_device, NULL );
	ctx::g_context.get( )->g_set_vertex_shader( g_device, NULL );

	/* render states */ {
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_CULLMODE, D3DCULL_NONE );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_LIGHTING, false );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_ZENABLE, false );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_ALPHABLENDENABLE, true );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_ALPHATESTENABLE, false );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_BLENDOP, D3DBLENDOP_ADD );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		ctx::g_context.get()->g_set_render_state( g_device, D3DRS_SCISSORTESTENABLE, true );
	}

	/* texture stages */ {
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		ctx::g_context.get()->g_set_texture_stage_state( g_device, 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	}

	/* sampler state */ {
		ctx::g_context.get()->g_set_sampler_state( g_device, 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		ctx::g_context.get()->g_set_sampler_state( g_device, 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	}
}

void entry::impl::g_warp_viewport( IDirect3DDevice9* g_device, sdk::vec2_t g_size ) {
	/* init */
	D3DVIEWPORT9 g_viewport{};
	g_viewport.X = g_viewport.Y = 0;
	g_viewport.Width = ( DWORD )g_size.x;
	g_viewport.Height = ( DWORD )g_size.y;
	g_viewport.MinZ = 0.0f;
	g_viewport.MaxZ = 1.0f;

	/* set this motherfucker */
	ctx::g_context.get( )->g_set_viewport( g_device, &g_viewport );
}