#pragma once
#include "../includes.hpp"
#include "../entry/entry.hpp"

/* we are going to use this to define snake_case function so the code will look premium and clean */
/* retardness upcoming */
namespace ctx {
	class impl {
	public:
		void g_alloc_console( );
		
		/* functions warper */
		HRESULT g_reset_device( D3DPRESENT_PARAMETERS g_reset_parrameter );
		void g_release_device( LPDIRECT3DDEVICE9* g_device );
		void g_release_device_pointer( LPDIRECT3D9* g_device_pointer );
	};
	inline const auto g_context = std::make_unique< impl >( );
}