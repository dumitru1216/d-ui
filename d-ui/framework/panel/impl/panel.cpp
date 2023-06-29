#include "../panel.hpp"
#include "../../warper/warper.hpp"
#include <algorithm>

void ui::panel::g_render( ) {
	g_area = sdk::rect_t( 0, 0, 1920, 1080 );
	warp::bindings::g_clip( g_area, [ & ]( ) {
		std::for_each( g_windows.begin( ), g_windows.end( ), [ ]( std::shared_ptr< window >& child ) {
			child->g_draw( );
		} );
	} );
}