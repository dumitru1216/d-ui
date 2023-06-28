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

/* warper CreateStateBlock(this_ state_block_type, IDirect3DStateBlock9) */
HRESULT ctx::impl::g_create_state_block( LPDIRECT3DDEVICE9* g_device, D3DSTATEBLOCKTYPE g_block_type, IDirect3DStateBlock9* g_dx_block ) {
    return ( *g_device )->CreateStateBlock( g_block_type, &g_dx_block );
}

/* warper GetClientRect */
BOOL ctx::impl::g_take_client_rect( HWND g_window_handle, RECT* g_screen_rect ) { /*
        might be an issue the operator from g_screen_rect, we are going to see later
    */
    if ( g_window_handle && g_screen_rect ) { /* safety condition */
        return GetClientRect( g_window_handle, g_screen_rect );
    }

    /* for any other values we are going to return false */
    return FALSE;
}

/* directx_sdk warpers */
void ctx::impl::g_set_vertex_shader( IDirect3DDevice9* g_device, IDirect3DVertexShader9* g_shader ) {
    g_device->SetVertexShader( g_shader );
}

void ctx::impl::g_set_pixel_shader( IDirect3DDevice9* g_device, IDirect3DPixelShader9* g_shader ) {
    g_device->SetPixelShader( g_shader );
}

void ctx::impl::g_set_render_state( IDirect3DDevice9* g_device, D3DRENDERSTATETYPE g_state, DWORD g_value ) {
    g_device->SetRenderState( g_state, g_value );
}

void ctx::impl::g_set_texture_stage_state( IDirect3DDevice9* g_device, DWORD g_stage, D3DTEXTURESTAGESTATETYPE g_type, DWORD g_value ) {
    g_device->SetTextureStageState( g_stage, g_type, g_value );
}

void ctx::impl::g_set_sampler_state( IDirect3DDevice9* g_device, DWORD g_sampler, D3DSAMPLERSTATETYPE g_type, DWORD g_value ) {
    g_device->SetSamplerState( g_sampler, g_type, g_value );
}

void ctx::impl::g_set_transform( IDirect3DDevice9* g_device, D3DTRANSFORMSTATETYPE g_state, const D3DMATRIX* g_matrix ) {
    g_device->SetTransform( g_state, g_matrix );
}

void ctx::impl::g_set_viewport( IDirect3DDevice9* g_device, const D3DVIEWPORT9* g_viewport ) {
    g_device->SetViewport( g_viewport );
}
