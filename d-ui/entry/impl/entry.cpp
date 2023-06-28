#include "../entry.hpp"
#include "../../context/context.hpp"

/* main function, something that will let me build i will modify it later */
int main( HINSTANCE g_instance, HINSTANCE g_prev_instance,
		  LPWSTR g_cmd_line, int g_cmd_show ) { 
	ctx::g_context.get( )->g_alloc_console( ); /* we will need this */

	/* lpz_class as a pointer */
	LPCTSTR g_lpz_class{ "d-ui framework" };
	LPCTSTR g_name{ "d-ui framework" };

	/*
		if g_register_window function with arguments g_instance and g_lpz_class returns false, returns 0
		if g_init_window function with arguments g_instance, g_lpz_class, and g_name returns false, returns 0
	*/
	if ( !entry::g_entry.get()->g_register_window( g_instance, g_lpz_class ) || 
		 !entry::g_entry.get( )->g_init_window( g_instance, g_lpz_class, g_name ) ) {
		return 0;
	}

	if ( !entry::g_entry.get( )->g_create_device( g_window_handle ) ) {
		entry::g_entry.get( )->g_clean_device( );

		/* unregister class */
		ctx::g_context.get( )->g_unregister_class( g_lpz_class, g_instance );

		/* stop it */
		return 0;
	}

	/* clean again */
	entry::g_entry.get( )->g_clean_device( );

	/* destroy it */
	ctx::g_context.get( )->g_destroy_window( g_window_handle );

	/* unregister class */
	ctx::g_context.get( )->g_unregister_class( g_lpz_class, g_instance );

	/* stop it */
	return 0;
}

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
	if ( ( g_d3d9_handle = ctx::g_context.get( )->g_create_device( D3D_SDK_VERSION ) ) == NULL ) {
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
	//ctx::g_context.get( )->create_device( g_d3d9_handle,  );

	if ( ctx::g_context.get( )->create_device( g_d3d9_handle, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_window_handle, 
		 D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3d9_pp_handle, &g_device_handle ) < 0 )
		return FALSE;


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

	/* run inside function */
	g_function( );

	/* release & apply stateblock */
	g_state_block->Apply( );
	g_state_block->Release( );
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

LRESULT CALLBACK g_window_handler( HWND g_window, UINT g_msg, WPARAM g_wp, LPARAM g_lp ); /* we are going to init this a little bit down */
ATOM entry::impl::g_register_window( HINSTANCE g_instance, LPCTSTR g_name ) {
	/*
		registers a window class by initializing a wndclassex structure with the following properties:

		cbsize is set to the size of wndclassex structure
		style is set to cs_hredraw | cs_vredraw
		lpfnwndproc is set to g_window_handler, which represents the window procedure
		cbclsextra and cbwndextra are both set to 0
		hinstance is set to g_instance, representing the application instance handle
		hicon is set by loading the icon with resource id idi_guitest from the g_instance
		hcursor is set to the arrow cursor
		hbrbackground is set to the color of the window background
		lpszmenuname is set to the resource id idc_guitest, representing the menu for the window
		lpszclassname is set to g_name, representing the window class name
		hiconsm is set by loading the small icon with resource id idi_small from the hinstance
	*/
	WNDCLASSEX g_wcex{};

	g_wcex.cbSize = sizeof( WNDCLASSEX );
	g_wcex.style = CS_HREDRAW | CS_VREDRAW;
	g_wcex.lpfnWndProc = g_window_handler;
	g_wcex.cbClsExtra = 0;
	g_wcex.cbWndExtra = 0;
	g_wcex.hInstance = g_instance;
	g_wcex.hIcon = LoadIcon( g_instance, MAKEINTRESOURCE( IDI_GUITEST ) );
	g_wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
	g_wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	g_wcex.lpszMenuName = MAKEINTRESOURCE( IDC_GUITEST );
	g_wcex.lpszClassName = g_name;
	g_wcex.hIconSm = LoadIcon( g_wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

	/* register this motherfucker */
	return ctx::g_context.get( )->g_register_class( g_wcex );
}

ATOM entry::impl::g_init_window( HINSTANCE g_instance, LPCTSTR g_class_name, LPCTSTR g_title ) {
	/*
		initializes g_screen_rect as an empty rect structure
		calls the g_take_window_rect function of g_context to get the rectangle of the desktop window and stores it in g_screen_rect

		creates a window with the following parameters:

		ws_ex_appwindow style extended window style
		g_class_name as the window class name
		g_title as the window title
		ws_popup style for the window
		g_screen_rect.left, g_screen_rect.top, g_screen_rect.right, g_screen_rect.bottom as the window position and size
		null as the parent window
		null as the menu
		g_instance as the application instance handle
		null as the window creation data
		if g_window_handle is not valid (null), returns false
		otherwise, returns true
	*/
	RECT g_screen_rect{};
	ctx::g_context.get( )->g_take_window_rect( GetDesktopWindow( ), &g_screen_rect );

	/* finnaly we initialize our window */
	g_window_handle = ctx::g_context.get( )->g_create_window_ex( WS_EX_APPWINDOW, g_class_name, g_title, WS_POPUP, g_screen_rect.left, g_screen_rect.top,
																 g_screen_rect.right, g_screen_rect.bottom, NULL, NULL, g_instance, NULL );

	if ( !g_window_handle ) { return FALSE; }
	return TRUE;
}

/* as i said that we are going to initialize it */
LRESULT CALLBACK g_window_handler( HWND g_window, UINT g_msg, WPARAM g_wp, LPARAM g_lp ) {
	return ctx::g_context.get( )->g_def_window_proc( g_window, g_msg, g_wp, g_lp );
}