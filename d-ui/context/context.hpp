#pragma once
#include "../includes.hpp"
#include "../entry/entry.hpp"

/* we are going to use this to define snake_case function so the code will look premium and clean */
/* retardness upcoming */
namespace ctx {
	class impl {
	public:
		void g_alloc_console( );
		
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
	};
	inline const auto g_context = std::make_unique< impl >( );
}