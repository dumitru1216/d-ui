#include "../panel.hpp"
#include "../../warper/warper.hpp"
#include <algorithm>

void ui::panel::g_render( double g_t ) {
	g_area = sdk::rect_t( 0, 0, 1920, 1080 );
	g_time = g_t; /* animation responsable */

	warp::bindings::g_clip( g_area, [ & ]( ) {
		std::for_each( g_windows.begin( ), g_windows.end( ), [ ]( std::shared_ptr< window >& child ) {
			child->g_draw( );
		} );
	} );
}