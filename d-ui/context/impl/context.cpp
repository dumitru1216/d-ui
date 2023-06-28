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

/* warper LPDIRECT3D9->Release() */
void ctx::impl::g_release_device_pointer( LPDIRECT3D9* g_device_pointer ) {
    /* this might work, its the first time im doing/trying to get properly warpers */
    if ( g_device_pointer && *g_device_pointer ) {
        ( *g_device_pointer )->Release( );
        *g_device_pointer = nullptr;
    }
}

/* warper Direct3DCreate9 */
LPDIRECT3D9 ctx::impl::g_create_device( std::uint32_t g_sdk_version ) {
    return Direct3DCreate9( g_sdk_version );
}

/* warper ZeroMemory */
template<typename warp_memory> /* i guess this works fine */
void ctx::impl::g_clean_memory( warp_memory* g_destination, std::size_t g_size ) {
    ZeroMemory( g_destination, g_size );
}

/* warper directx */
void ctx::impl::g_warp_dx( D3DPRESENT_PARAMETERS g_destination ) {
    g_destination.Windowed = TRUE;
    g_destination.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_destination.BackBufferFormat = D3DFMT_UNKNOWN;
    g_destination.EnableAutoDepthStencil = TRUE;
    g_destination.AutoDepthStencilFormat = D3DFMT_D16;
    g_destination.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
}

/* warper create device */
BOOL ctx::impl::g_handle_device( HWND g_window_handle, LPDIRECT3D9* g_destination,
                                 D3DPRESENT_PARAMETERS g_destination_p, LPDIRECT3DDEVICE9 g_destination_dev ) {
    if ( ( *g_destination )->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_window_handle,
         D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_destination_p, &g_destination_dev ) < 0 ) {
        return FALSE;
    }
}