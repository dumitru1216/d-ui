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
}