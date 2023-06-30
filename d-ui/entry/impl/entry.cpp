#include "../entry.hpp"
#include "../../context/context.hpp"
#include "../../framework/fonts/fonts.hpp"
#include "../../framework/menu/menu.hpp"

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

	/* window updating */
	ctx::g_context.get( )->g_show_window( g_window_handle, SW_SHOWDEFAULT );
	ctx::g_context.get( )->g_update_window( g_window_handle );	

	/* warp imgui */
	entry::g_entry.get( )->g_warp_imgui( g_window_handle, g_device_handle );
	menu::g_init.get( )->g_run( );

	/* mem handler */
	MSG g_msg{};
	g_clean_memory( &g_msg, sizeof( g_msg ) );

	/* loop msg */
	while ( g_msg.message != WM_QUIT ) {
		if ( ctx::g_context.get( )->g_peek_message( &g_msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			ctx::g_context.get( )->g_translate_message( &g_msg );
			ctx::g_context.get( )->g_dispatch_message( &g_msg );
			continue;
		}

		/* frame */
		ctx::g_context.get( )->g_warp_frame( );
		ctx::g_context.get( )->g_begin_frame( ); {
			menu::g_init.get( )->g_init( );
		}	
		ctx::g_context.get( )->g_end_frame( );

		/* render states and clear device */
		ctx::g_context.get()->g_set_render_state( g_device_handle, D3DRS_ZENABLE, false );
		ctx::g_context.get()->g_set_render_state( g_device_handle, D3DRS_ALPHABLENDENABLE, false );
		ctx::g_context.get()->g_set_render_state( g_device_handle, D3DRS_SCISSORTESTENABLE, false );

		/* clear */
		ctx::g_context.get( )->g_clear(
			g_device_handle, 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA( 23, 23, 23, 0 ), 1.0f, 0
		);

		/* init scene */
		if ( ctx::g_context.get( )->g_begin_scene( g_device_handle ) >= 0 ) {
			entry::g_entry.get()->g_setup_rendering_state( [ = ]( ) {
				/* here we are going to render our stuff */
				ImGui::Render( );
				ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
			} );


			/* unload external window */
			if ( GetAsyncKeyState( VK_END ) ) {
				ExitProcess( -1 );
			}

			/* end scene */
			ctx::g_context.get( )->g_end_scene( g_device_handle );
		}

		/* handle packet loss - i will handle it tmr */
		HRESULT result{ g_device_handle->Present( NULL, NULL, NULL, NULL ) };
		if ( result == D3DERR_DEVICELOST && g_device_handle->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
			entry::g_entry->g_reset_device( );
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
	if ( ( g_d3d9_handle = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL ) {
		return FALSE;
	}

	/*
		zeros out the memory of g_d3d9pp by setting all its bytes to zero.
		the size of g_d3d9pp is determined by sizeof( g_d3d9pp ).
	*/
	g_clean_memory( &g_d3d9_pp_handle, sizeof( g_d3d9_pp_handle ) );

	/* warp dx */
	ctx::g_context->g_warp_dx( &g_d3d9_pp_handle );

	/* handle device */
	if ( g_init_device( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_window_handle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3d9_pp_handle, &g_device_handle ) < 0 )
		return FALSE;

	/* now lets return true */
	return TRUE;
}

void entry::impl::g_setup_rendering_state( std::function<void( )> g_function ) {
	/* backup dx state */
	IDirect3DStateBlock9* g_state_block{ NULL };

	/* create state block */
	if ( g_create_state_block( D3DSBT_ALL, &g_state_block ) < 0 ) {
		return;
	}

	/* get display size */
	RECT g_screen_rect{};
	ctx::g_context.get( )->g_take_client_rect( g_window_handle, &g_screen_rect );

	/* display size, we are going to directly initialize it */
	sdk::vec2_t display_size{ sdk::vec2_t(
		( float )( g_screen_rect.right - g_screen_rect.left ), ( float )( g_screen_rect.bottom - g_screen_rect.top )
	) };

	g_warp_render_state( g_device_handle ); /* entry::g_entry.get()-> / if you want to go in that side */

	/* setup viewport */
	g_warp_viewport( g_device_handle, display_size );

	/* run function */
	g_function( );

	/* restore dx state */
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
	if ( menu::g_init->g_handle_window( g_window, g_msg, g_wp, g_lp ) ) // crash
		return true;

	switch ( g_msg ) {
		case WM_SIZE:
		if ( g_device_handle != NULL && g_wp != SIZE_MINIMIZED ) {
			g_d3d9_pp_handle.BackBufferWidth = LOWORD( g_lp );
			g_d3d9_pp_handle.BackBufferHeight = HIWORD( g_lp );
			entry::g_entry.get()->g_reset_device( );
		}
		return 0;
		case WM_SYSCOMMAND:
		if ( ( g_wp & 0xfff0 ) == SC_KEYMENU ) /* Disable ALT application menu */
			return 0;
		break;
		case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProcA( g_window, g_msg, g_wp, g_lp );
}

void entry::impl::g_warp_imgui( HWND g_handle_window, IDirect3DDevice9* g_device ) {
	IMGUI_CHECKVERSION( );

	ImGui::CreateContext( );
	ImGuiIO& io = ImGui::GetIO( );
	ImGui::StyleColorsDark( );

	ImGui_ImplWin32_Init( g_handle_window );
	ImGui_ImplDX9_Init( g_device );

	fonts::g_init.get( )->g_initialize_fonts( );
}