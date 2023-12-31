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
void ctx::impl::g_warp_dx( D3DPRESENT_PARAMETERS* g_destination ) {
    g_destination->Windowed = TRUE;
    g_destination->SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_destination->BackBufferFormat = D3DFMT_UNKNOWN;
    g_destination->EnableAutoDepthStencil = TRUE;
    g_destination->AutoDepthStencilFormat = D3DFMT_D16;
    g_destination->PresentationInterval = D3DPRESENT_INTERVAL_ONE;
}

/* warper create device */
HRESULT ctx::impl::g_create_device_window( LPDIRECT3D9* g_p_d3d, UINT g_adapter, D3DDEVTYPE g_device_type, HWND g_h_focus_window,
                       DWORD g_behavior_flags, D3DPRESENT_PARAMETERS* g_presentation_parameters, LPDIRECT3DDEVICE9 g_pp_device ) {
    if ( !g_p_d3d ) 
        return NULL;

    return ( *g_p_d3d )->CreateDevice( g_adapter, g_device_type, g_h_focus_window, g_behavior_flags, g_presentation_parameters, &g_pp_device );
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

/* warper GetWindowRect */
BOOL ctx::impl::g_take_window_rect( HWND g_window_handle, RECT* g_screen_rect ) {
    /*
        might be an issue the operator from g_screen_rect, we are going to see later
    */
    if ( g_window_handle && g_screen_rect ) { /* safety condition */
        return GetWindowRect( g_window_handle, g_screen_rect );
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

/* warper RegisterClassEX */
ATOM ctx::impl::g_register_class( const WNDCLASSEX& g_wcex ) {
    return RegisterClassEx( &g_wcex );
}

/* warper CreateWindowEx */
HWND ctx::impl::g_create_window_ex( DWORD g_dw_ex_style, LPCSTR g_lp_class_name, LPCSTR g_lp_window_name, DWORD g_dw_style, int g_x, int g_y,
                                    int g_width, int g_height, HWND g_hwnd_parent, HMENU g_h_menu, HINSTANCE g_h_instance, LPVOID g_lp_param ) {
    /* seems retarded? ... yeah, i know */
    return CreateWindowEx( g_dw_ex_style, g_lp_class_name, g_lp_window_name, g_dw_style, g_x, g_y, g_width, g_height, g_hwnd_parent,
                           g_h_menu, g_h_instance, g_lp_param );
}

/* warper DefWindowProcA */
LRESULT ctx::impl::g_def_window_proc( HWND g_hwnd, UINT g_u_msg, WPARAM g_w_param, LPARAM g_l_param ) {
    return DefWindowProcA( g_hwnd, g_u_msg, g_w_param, g_l_param );
}

/* warper UnregisterClass */
BOOL ctx::impl::g_unregister_class( LPCSTR g_lp_class_name, HINSTANCE g_instance ) {
    return UnregisterClass( g_lp_class_name, g_instance );
}

/* warper DestroyWindow */
BOOL ctx::impl::g_destroy_window( HWND g_hwnd ) {
    return DestroyWindow( g_hwnd ); 
}

/* warper ShowWindow */
BOOL ctx::impl::g_show_window( HWND g_hwnd, int g_n_cmd_show ) {
    return ShowWindow( g_hwnd, g_n_cmd_show );
}

/* warper UpdateWindow */
BOOL ctx::impl::g_update_window( HWND g_hwnd ) {
    return UpdateWindow( g_hwnd );
}

/* warper PeekMessage */
BOOL ctx::impl::g_peek_message( LPMSG g_lp_msg, HWND g_hwnd, UINT g_w_msg_filter_min, UINT g_w_msg_filter_max,
                     UINT g_w_remove_msg ) {
    return PeekMessage( g_lp_msg, g_hwnd, g_w_msg_filter_min, g_w_msg_filter_max, g_w_remove_msg );
}

/* warper message functions */ 
BOOL ctx::impl::g_translate_message( const MSG* g_lp_msg ) {
    return TranslateMessage( g_lp_msg );
}

LRESULT ctx::impl::g_dispatch_message( const MSG* g_lp_msg ) {
    return DispatchMessage( g_lp_msg );
}

/* imgui warpers */
void ctx::impl::g_warp_frame( ) {
    ImGui_ImplDX9_NewFrame( );
    ImGui_ImplWin32_NewFrame( );
}

void ctx::impl::g_begin_frame( ) {
    ImGui::NewFrame( );
}

void ctx::impl::g_end_frame( ) {
    ImGui::EndFrame( );
}

/* device clear warper */
HRESULT ctx::impl::g_clear( LPDIRECT3DDEVICE9 g_device, DWORD g_count, const D3DRECT* g_p_rects, DWORD g_flags, D3DCOLOR g_color,
                 float g_z, DWORD g_stencil ) {
    return g_device->Clear( g_count, g_p_rects, g_flags, g_color, g_z, g_stencil );
}

/* warp dx scene */
HRESULT ctx::impl::g_begin_scene( LPDIRECT3DDEVICE9 g_device ) {
    return g_device->BeginScene( );
}

HRESULT ctx::impl::g_end_scene( LPDIRECT3DDEVICE9 g_device ) {
    return g_device->EndScene( );
}