#include "../context.hpp"

/* warping the function so we can alloc console as a mental */
void ctx::impl::g_alloc_console( ) {
	AllocConsole( ); /* retardness as i said */
}

/* resets the device using the given parameters */
HRESULT ctx::impl::g_reset_device( D3DPRESENT_PARAMETERS g_reset_parrameter ) {
	return g_device_handle->Reset( &g_reset_parrameter );
}

/* warper LPDIRECT3DDEVICE9->Release() */
void ctx::impl::g_release_device( LPDIRECT3DDEVICE9* g_device ) {
    /* this might work, its the first time im doing/trying to get properly warpers */
    if ( g_device && *g_device ) {
        ( *g_device )->Release( );
        *g_device = nullptr;
    }
}