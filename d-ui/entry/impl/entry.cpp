#include "../entry.hpp"
#include "../../context/context.hpp"

void entry::impl::g_reset_device( ) {
	HRESULT result{};

	/* store out in result */
	result = ctx::g_context.get( )->g_reset_device( g_d3d9_pp_handle );
	if ( result != D3DERR_INVALIDCALL ) { }
}